#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>

#include "../B_server/message.h"
#include "../B_server/gamemodel.h"


#include "FieldWidget.h"
#include "ConnectWidget.h"



class Message2;
class GameModel;

class ConnectWidget;
class FieldWidget;

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWidget; }
QT_END_NAMESPACE



class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

//    void ParseTokenizedMessage(const QStringList& tokens);

private slots:
//    void onSendMessageButtonClicked();
//    void onDisconnectButtonClicked();
    void onConnectClicked();

    void onConnected();
    void onDisconnected();
    void onTcpReadyRead();


public:
    void onFieldMousePressed(int row, int col);

    GameModel gameModel;
    GameModel::Piece role;

private:
    Ui::ClientWidget *ui;

    QTcpSocket* tcpSocket;

    ConnectWidget* connectWidget;
    FieldWidget* fieldWidget;

};
#endif // CLIENTWIDGET_H
