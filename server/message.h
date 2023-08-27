#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QStringList>

#include <QTcpSocket>

#include "GameModel.h"

#include <QPoint>

class Message2 {
public:
    static const char OP;

    static char readOp(QTcpSocket* socket) {
        QByteArray array = socket->read(2);

        if (array[0] != OP) {
            qDebug() << "readMessageBytes failed. Expected OP but got" << array;

            qDebug() << "readMessageBytes failed. reading all from socket to nowhere";
            socket->readAll();

            return 0;
        }

        return array[1];
    }

    static const char GAME_MODEL;
    static const int GAME_MODEL_LENGTH;

    static QByteArray GameModelToBytes(const GameModel& gameModel);
    static GameModel GameModelFromBytes(const QByteArray& array);

    static const char PLAYER_ROLE;
    static const char PLAYER_ROLE_LENGTH;

    static QByteArray PlayerRoleToBytes(GameModel::Piece piece);
    static GameModel::Piece PlayerRoleFromBytes(const QByteArray& array);

    static const char REQUEST_NEW_GAME;
    static const char REQUEST_NEW_GAME_LENGTH;

    static QByteArray RequestNewGameToBytes();
    static void RequestNewGameFromBytes(const QByteArray& array);

    static const char PLAYER_MOVE;
    static const char PLAYER_MOVE_LENGTH;

    static QByteArray PlayerMoveToBytes(char row, char col);
    static QPoint PlayerMoveFromBytes(const QByteArray& array);
};

QString PlayerNameMessage2(QString playerName);

#endif // MESSAGE_H
