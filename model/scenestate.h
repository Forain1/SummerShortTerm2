#ifndef SCENESTATE_H
#define SCENESTATE_H

#include <QObject>
#include "../common/pageindex.h"

class SceneState : public QObject
{
    Q_OBJECT
public:
    explicit SceneState(QObject *parent = nullptr);
    PageIndex::Index getCurrentPageIndex(){return currentPageIndex;}
    void setCurrentPageIndex(PageIndex::Index index);

    bool isMenu(){return currentPageIndex==PageIndex::MenuIndex;}
    bool isCast(){return currentPageIndex==PageIndex::CastIndex;}
    bool isFight(){return currentPageIndex==PageIndex::FightIndex;}
    bool isSettle(){return currentPageIndex==PageIndex::SettleIndex;}
private:
    PageIndex::Index currentPageIndex;
signals:
    void currentPageIndexChanged(PageIndex::Index index);
};

#endif // SCENESTATE_H
