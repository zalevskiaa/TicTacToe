#include "message.h"

const char Message2::OP = '0';

const char Message2::GAME_MODEL = 1;
const int Message2::GAME_MODEL_LENGTH = 9; // todo: maybe send this number as third byte before message body: [OP, OP_type, OP_len] [message_body]

QByteArray Message2::GameModelToBytes(const GameModel& gameModel) {
    QByteArray array;

    array.append(OP);
    array.append(GAME_MODEL);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            char c = GameModel::pieceToChar(gameModel.field[i][j]);
            array.append(c);
        }
    }

    return array;
}
GameModel Message2::GameModelFromBytes(const QByteArray& array) {
    GameModel gameModel;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            char c = array[3 * i + j];
            gameModel.field[i][j] = GameModel::pieceFromChar(c);
        }
    }

    return gameModel;
}

const char Message2::PLAYER_ROLE = 2;
const char Message2::PLAYER_ROLE_LENGTH = 1;

QByteArray Message2::PlayerRoleToBytes(GameModel::Piece piece) {
    QByteArray array;

    array.append(OP);
    array.append(PLAYER_ROLE);

    array.append(GameModel::pieceToChar(piece));

    return array;
}
GameModel::Piece Message2::PlayerRoleFromBytes(const QByteArray& array) {
    char c = array[0];
    GameModel::Piece piece = GameModel::pieceFromChar(c);

    return piece;
}

const char Message2::REQUEST_NEW_GAME = 3;
const char Message2::REQUEST_NEW_GAME_LENGTH = 0;

QByteArray Message2::RequestNewGameToBytes() {
    QByteArray array;

    array.append(OP);
    array.append(REQUEST_NEW_GAME);

    return array;
}
void Message2::RequestNewGameFromBytes(const QByteArray& array) {
    return;
}

const char Message2::PLAYER_MOVE = 4;
const char Message2::PLAYER_MOVE_LENGTH = 2;

QByteArray Message2::PlayerMoveToBytes(char row, char col) {
    QByteArray array;

    array.append(OP);
    array.append(PLAYER_MOVE);

    array.append(row);
    array.append(col);

    return array;
}
QPoint Message2::PlayerMoveFromBytes(const QByteArray& array) {
    return QPoint(array[0], array[1]);
}
