#ifndef SETTLEMENT_H
#define SETTLEMENT_H

#include <QWidget>

namespace Ui {
class Settlement;
}

class Settlement : public QWidget
{
    Q_OBJECT

public:
    explicit Settlement(QWidget *parent = nullptr);
    ~Settlement();

private:
    Ui::Settlement *ui;

signals:
    void onceMoreBtnClicked();
    void returnMenuBtnClicked();
};

#endif // SETTLEMENT_H
