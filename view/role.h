#ifndef ROLE_H
#define ROLE_H

#include <QWidget>

namespace Ui {
class Role;
}

class Role : public QWidget
{
    Q_OBJECT

public:
    explicit Role(int num,QWidget *parent = nullptr);
    ~Role();

signals:
    void roleBtnClicked(int i);
public slots:
    void setBtn(bool);
private:
    int roleNum;
    Ui::Role *ui;
};

#endif // ROLE_H
