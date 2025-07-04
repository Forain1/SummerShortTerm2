#ifndef ESC_H
#define ESC_H

#include <QDialog>

namespace Ui {
class Esc;
}

class Esc : public QDialog
{
    Q_OBJECT

public:
    explicit Esc(QWidget *parent = nullptr);
    ~Esc();
signals:
    void pressMenu();
    void volumeChange(int);
private:
    Ui::Esc *ui;
};

#endif // ESC_H
