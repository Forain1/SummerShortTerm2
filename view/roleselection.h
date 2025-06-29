#ifndef ROLESELECTION_H
#define ROLESELECTION_H

#include <QWidget>

namespace Ui {
class RoleSelection;
}

class RoleSelection : public QWidget
{
    Q_OBJECT

public:
    explicit RoleSelection(QWidget *parent = nullptr);
    ~RoleSelection();

private:
    Ui::RoleSelection *ui;
};

#endif // ROLESELECTION_H
