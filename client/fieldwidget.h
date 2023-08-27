#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include <QWidget>
#include <QPainter>

//#include "../B_server/gamemodel.h"
#include "ClientWidget.h"

#include <QMouseEvent>

namespace Ui {
class FieldWidget;
}

class FieldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FieldWidget(QWidget *parent = nullptr);
    ~FieldWidget();

signals:
    void mousePressed(int row, int col);

private:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    Ui::FieldWidget *ui;
};

#endif // FIELDWIDGET_H
