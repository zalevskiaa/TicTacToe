#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QVector>
#include <QDebug>

class GameModel
{
public:
    enum class Piece {
        FREE,
        X,
        O
    };

    enum class Status {
        PROCESS,
        END
    };

    // todo: maybe remove this class
    // and handle [ Player <--> Piece ] somewhere else
    enum class Player {
        P1,
        P2
    };

    static Piece playerToCell(Player player) {
        return player == Player::P1 ? Piece::X : Piece::O;
    }

    static QString cellToString(Piece cell);
    static QString statusToString(Status status);
    static QString playerToString(Player player);

    static Piece stringToCell(QString str);
    static Status stringToStatus(QString str);
    static Player stringToPlayer(QString str);


    static char pieceToChar(Piece piece);
    static char statusToChar(Status status);
    static char playerToChar(Player player);

    static Piece pieceFromChar(char c);
    static Status statusFromChar(char c);
    static Player playerFromChar(char c);

    static Player flip(Player player) {
        return player == Player::P1 ? Player::P2 : Player::P1;
    }


public:


    Piece CheckWinner() const;
    Status CheckStatus() const;
    Piece CheckTurn() const;

    QString GetStringStatus() const ;

public:
    GameModel();

    void NewGame();
    bool MakeMove(Piece piece, int row, int col);

signals:

public:
    QVector<QVector<Piece>> field;
};

#endif // GAMEMODEL_H
