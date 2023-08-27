#include "clientwidget.h"
#include "ui_clientwidget.h"

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);

    fieldWidget = new FieldWidget(this);
    fieldWidget->hide();

    connect(fieldWidget, &FieldWidget::mousePressed, this, &ClientWidget::onFieldMousePressed);

    connectWidget = new ConnectWidget(this);
    connectWidget->show();

    connect(connectWidget, SIGNAL(connectClicked()), this, SLOT(onConnectClicked()));

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(onTcpReadyRead()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
}

ClientWidget::~ClientWidget()
{
    delete ui;
}

void ClientWidget::onConnectClicked() {
    qDebug() << "onConnectClicked";

    tcpSocket->connectToHost("127.0.0.1", 6666);
}

void ClientWidget::onConnected() {
    qDebug() << "Connected to server";

    connectWidget->hide();
    fieldWidget->show();
}


void ClientWidget::onDisconnected() {
    qDebug() << "Disconnected";

    fieldWidget->hide();
    connectWidget->show();
}

void ClientWidget::onTcpReadyRead() {
    while (tcpSocket->size() > 0) {
        char op = Message2::readOp(tcpSocket);

        if (op == Message2::GAME_MODEL) {
            QByteArray array = tcpSocket->read(Message2::GAME_MODEL_LENGTH);
            gameModel = Message2::GameModelFromBytes(array);

            qDebug() << "received GAME_MODEL" << array;
            continue;
        }

        if (op == Message2::PLAYER_ROLE) {
            QByteArray array = tcpSocket->read(Message2::PLAYER_ROLE_LENGTH);
            role = Message2::PlayerRoleFromBytes(array);

            qDebug() << "received PLAYER_ROLE" << array;
            continue;
        }

        qDebug() << "Unknown OP. Clearing socket message input";
        tcpSocket->readAll();
        break;
    }

    update();
}

void ClientWidget::onFieldMousePressed(int row, int col) {
    if (gameModel.CheckStatus() == GameModel::Status::PROCESS && gameModel.CheckWinner() == GameModel::Piece::FREE) {

        tcpSocket->write(Message2::PlayerMoveToBytes(row, col));
        qDebug() << "sent PLAYER_MOVE" << row << col;

    } else {

        tcpSocket->write(Message2::RequestNewGameToBytes());
        qDebug() << "sent PLAYER_REQUEST_NEW_GAME";
    }
}
