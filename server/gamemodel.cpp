#include "gamemodel.h"

QString GameModel::cellToString(GameModel::Piece piece) {
    if (piece == Piece::X) {
        return "X";
    }
    if (piece == Piece::O) {
        return "O";
    }
    return ".";
}
GameModel::Piece GameModel::stringToCell(QString str) {
    if (str == "X") {
        return Piece::X;
    }
    if (str == "O") {
        return Piece::O;
    }
    return Piece::FREE;
}
QString GameModel::statusToString(GameModel::Status status) {
    if (status == Status::PROCESS) {
        return "P";
    }
    return "E";
}
GameModel::Status GameModel::stringToStatus(QString str) {
    if (str == "P") {
        return Status::PROCESS;
    }
    return Status::END;
}
QString GameModel::playerToString(GameModel::Player player) {
    if (player == Player::P1) {
        return "P1";
    }
    return "P2";
}
GameModel::Player GameModel::stringToPlayer(QString str) {
    if (str == "P1") {
        return Player::P1;
    }
    return Player::P2;
}


char GameModel::pieceToChar(Piece piece) {
    if (piece == Piece::X) {
        return 1;
    }
    if (piece == Piece::O) {
        return 2;
    }
    return 0;
}
char GameModel::statusToChar(Status status) {
    if (status == Status::PROCESS) {
        return 1;
    }
    return 0;
}
char GameModel::playerToChar(Player player) {
    if (player == Player::P1) {
        return 1;
    }
    return 2;
}

GameModel::Piece GameModel::pieceFromChar(char c) {
    if (c == 1) {
        return Piece::X;
    }
    if (c == 2) {
        return Piece::O;
    }
    return Piece::FREE;
}
GameModel::Status GameModel::statusFromChar(char c) {
    if (c == 1) {
        return Status::PROCESS;
    }
    return Status::END;
}
GameModel::Player GameModel::playerFromChar(char c) {
    if (c == 1) {
        return Player::P1;
    }
    return Player::P2;
}


GameModel::Piece GameModel::CheckWinner() const {
    Piece a = field[0][0];
    Piece b = field[1][1];
    Piece c = field[2][2];

    if (a != Piece::FREE && a == b && b == c) {
        return a;
    }

    a = field[0][2];
    b = field[1][1];
    c = field[2][0];

    if (a != Piece::FREE && a == b && b == c) {
        return a;
    }

    for (int i = 0; i < 3; ++i) {
        a = field[i][0];
        b = field[i][1];
        c = field[i][2];

        if (a != Piece::FREE && a == b && b == c) {
            return a;
        }

        a = field[0][i];
        b = field[1][i];
        c = field[2][i];

        if (a != Piece::FREE && a == b && b == c) {
            return a;
        }
    }

    return Piece::FREE;
}

GameModel::Status GameModel::CheckStatus() const {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (field[i][j] == Piece::FREE) {
                return Status::PROCESS;
            }
        }
    }
    return Status::END;
}

GameModel::Piece GameModel::CheckTurn() const {
    int x = 0;
    int o = 0;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (field[i][j] == Piece::X) {
                ++x;
            } else if (field[i][j] == Piece::O) {
                ++o;
            }
        }
    }

    if (x > o) {
        return Piece::O;
    }
    return Piece::X;
}

QString GameModel::GetStringStatus() const {
    GameModel::Piece winner = CheckWinner();
    if (winner == Piece::X) {
        return "X wins";
    }
    if (winner == Piece::O) {
        return "O wins";
    }

    GameModel::Status status = CheckStatus();
    if (status == Status::END) {
        return "draw";
    }

    GameModel::Piece turn = CheckTurn();
    if (turn == Piece::X) {
        return "X's turn";
    }
    return "O's turn";
}

GameModel::GameModel() {
    NewGame();
}

void GameModel::NewGame() {
    field = QVector<QVector<Piece>> (3, QVector<Piece>(3, Piece::FREE));
}

bool GameModel::MakeMove(Piece piece, int row, int col) {
    // todo:
    // maybe move this functional into class GameModel

    if (CheckStatus() == GameModel::Status::END) {
        qDebug() << "Bad move. Game already ended.";
        // throw "incorrect move";
        return false;
    }
    if (piece != CheckTurn()) {
        qDebug() << "Bad move. Bad cell-turn.";
        // throw "incorrect move";
        return false;
    }
    if (field[row][col] != GameModel::Piece::FREE) {
        qDebug() << "Bad move. Bad cell.";
        // throw "incorrect move";
        return false;
    }

    field[row][col] = piece;

    return true;
}
