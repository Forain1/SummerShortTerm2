#ifndef SCENESTATE_H
#define SCENESTATE_H

#include <QObject>
#include "../common/index.h"

class SceneState : public QObject
{
    Q_OBJECT
public:
    explicit SceneState(QObject *parent = nullptr);
    Index::PageIndex getCurrentPageIndex(){return currentPageIndex;}
    void setCurrentPageIndex(Index::PageIndex index);

    bool isMenu(){return currentPageIndex==Index::MenuIndex;}
    bool isCast(){return currentPageIndex==Index::CastIndex;}
    bool isFight(){return currentPageIndex==Index::BattleIndex;}
    bool isSettle(){return currentPageIndex==Index::SettlementIndex;}
private:
    Index::PageIndex currentPageIndex;
signals:
    //更新currentPage后发出信号
    void currentPageIndexChanged(Index::PageIndex index);
public slots:
    //更新currentPage
    void turnToPage(Index::PageIndex index);
};

#endif // SCENESTATE_H
