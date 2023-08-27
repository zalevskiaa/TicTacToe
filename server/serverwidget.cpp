#include "serverwidget.h"
#include "ui_widget.h"

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress("127.0.0.1"), 6666);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
}

ServerWidget::~ServerWidget()
{
    delete ui;
}

void ServerWidget::onNewConnection() {
    QTcpSocket* socket = tcpServer->nextPendingConnection();

    if (tcpSockets.size() >= 2) {
        qDebug() << "New connection failed. Too much conenctions.";
        socket->disconnectFromHost();
        return;
    }

    qDebug() << "Connected" << socket->peerAddress() << socket->peerPort();

    connect(socket, SIGNAL(readyRead()), this, SLOT(onTcpReadyRead()));
    connect(socket, SIGNAL(aboutToClose()), this, SLOT(onAboutToClose()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));

    tcpSockets.push_back(socket);

    if (tcpSockets.size() == 2) {
        qDebug() << "Starting game";

        gameModel.NewGame();
        SendGameModelToBothPlayers();
    }
}

void ServerWidget::onAboutToClose() {
    qDebug() << "onAboutToClose";
    throw "lol onAboutToClose";
}

void ServerWidget::onDisconnected() {
    QTcpSocket* socket = (QTcpSocket*) sender();

    qDebug() << "Disconnected" << socket->peerAddress() << socket->peerPort();
    qDebug() << "removing socket from list:" << tcpSockets.removeOne(socket);

    // send another socket message: game stopped
    // ...
}

void ServerWidget::onTcpReadyRead() {
    QTcpSocket* socket = (QTcpSocket*) sender();

    while (socket->size() > 0) {
        char op = Message2::readOp(socket);

        if (op == Message2::PLAYER_MOVE) {
            QByteArray array = socket->read(Message2::PLAYER_MOVE_LENGTH);
            QPoint point = Message2::PlayerMoveFromBytes(array);

            // first coord is row, second is col
            int row = point.x();
            int col = point.y();

            // Assume that tcpSockets[0] is P1 is X, tcpSockets[1] is P2 is O
            GameModel::Piece piece = socket == tcpSockets[0] ? GameModel::Piece::X : GameModel::Piece::O;
            qDebug() << "player" << GameModel::cellToString(piece) << "moving to" << row << col;

            if (tcpSockets.size() < 2) {
                qDebug() << "move failed. Not enough players";
                continue;
            }

            bool move_success = gameModel.MakeMove(piece, row, col);
            if (!move_success) {
                qDebug() << "move failed. maybe incorrect move";
                continue;
            }

            SendGameModelToBothPlayers();
            continue;
        }

        if (op == Message2::REQUEST_NEW_GAME) {
            QByteArray array = socket->read(Message2::REQUEST_NEW_GAME_LENGTH);
            qDebug() << "received REQUEST_NEW_GAME from one of players";

            gameModel.NewGame();
            SendGameModelToBothPlayers();
            qDebug() << "new game started";
        }

        qDebug() << "Unknown OP. Clearing socket message input";
        socket->readAll();
        break;
    }
}

void ServerWidget::SendGameModelToBothPlayers() {
    // send actual game state

    QByteArray message = Message2::GameModelToBytes(gameModel);
    tcpSockets[0]->write(message);
    tcpSockets[1]->write(message);

    // tell players their roles (X or O)

    message = Message2::PlayerRoleToBytes(GameModel::Piece::X);
    tcpSockets[0]->write(message);
    message = Message2::PlayerRoleToBytes(GameModel::Piece::O);
    tcpSockets[1]->write(message);
}
