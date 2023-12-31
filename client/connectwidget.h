#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>

namespace Ui {
class ConnectWidget;
}

class ConnectWidget : public QWidget
{
    Q_OBJECT

signals:
    void connectClicked();

private slots:
    void onConnectClicked();

public:
    explicit ConnectWidget(QWidget *parent = nullptr);
    ~ConnectWidget();

private:
    Ui::ConnectWidget *ui;
};

#endif // CONNECTWIDGET_H
