#include "fieldwidget.h"
#include "ui_fieldwidget.h"

FieldWidget::FieldWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FieldWidget)
{
    ui->setupUi(this);
}

FieldWidget::~FieldWidget()
{
    delete ui;
}

void FieldWidget::mousePressEvent(QMouseEvent *event) {
    qDebug() << "FieldWidget mousePressEvent";

    QPoint pos = event->pos();

    int w = width();
    int h = height();

    int ws = w / 3; // step
    int hs = h / 3;

    int row = pos.y() / hs;
    int col = pos.x() / ws;

//    ((ClientWidget*) parent())->onFieldMousePressed(row, col);
    emit mousePressed(row, col);
}

void FieldWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    int w = width();
    int h = height();

    int ws = w / 3; // step
    int hs = h / 3;

    int wp = ws / 5; // padding
    int hp = hs / 5;

    painter.drawLine(ws, 0, ws, h);
    painter.drawLine(2 * ws, 0, 2 * ws, h);

    painter.drawLine(0, hs, w, hs);
    painter.drawLine(0, 2 * hs, w, 2 * hs);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int left = j * ws;
            int right = left + ws;
            int top = i * hs;
            int bottom = top + hs;

            GameModel::Piece piece = ((ClientWidget*) parent())->gameModel.field[i][j];

            if (piece == GameModel::Piece::X) {
                // x

                painter.drawLine(left + wp, top + hp, right - wp, bottom - hp);
                painter.drawLine(left + wp, bottom - hp, right - wp, top + hp);


            } else if (piece == GameModel::Piece::O) {
                // o

                painter.drawEllipse(left + wp, top + wp, right - left - 2*wp, bottom - top - 2*hp);
            }
        }
    }

    QString role = ((ClientWidget*) parent())->role == GameModel::Piece::X ? "You are X" : ((ClientWidget*) parent())->role == GameModel::Piece::O ? "You are O" : "Undefined Role";
    QString game_state = ((ClientWidget*) parent())->gameModel.GetStringStatus();
    QString text = role + ". " + game_state + ".";

    painter.drawText(0, 10, text);
}
