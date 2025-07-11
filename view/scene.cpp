#include "scene.h"
#include <QPainter>

Scene::Scene(QWidget *parent,QString path)
    : QWidget{parent},bgPath(path)
{
      bg = QPixmap(bgPath);
}


void Scene::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    if (!bg.isNull()) {
      //  qDebug() << "Scene size:" << this->size();
        QSize widgetSize = this->size();
        // 让背景图填满整个窗口，不保持比例（可改为 KeepAspectRatioByExpanding ）
        bg = bg.scaled(widgetSize,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, bg);
    }
    // 继续执行基类的 paintEvent
    QWidget::paintEvent(event);
}



