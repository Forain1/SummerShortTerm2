#ifndef CAST_H
#define CAST_H

#include <QWidget>
#include "scene.h"

namespace Ui {
class Cast;
}

class Cast : public Scene
{
    Q_OBJECT

public:
    explicit Cast(QWidget *parent = nullptr,QString path="");
    ~Cast();

private:
    Ui::Cast *ui;
};

#endif // CAST_H
