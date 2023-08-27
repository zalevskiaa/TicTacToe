#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

#include "message.h"
#include "gamemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();


private slots:
    void onTcpReadyRead();

    void onNewConnection();
    void onAboutToClose();
    void onDisconnected();

private:
    Ui::Widget *ui;

    QTcpServer* tcpServer;
    QVector<QTcpSocket*> tcpSockets;

    void SendGameModelToBothPlayers();

    GameModel gameModel;
};
#endif // SERVERWIDGET_H
