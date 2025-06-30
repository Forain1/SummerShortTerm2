#include "scenestate.h"

SceneState::SceneState(QObject *parent)
    : QObject{parent}
{
    currentPageIndex=Index::MenuIndex;
}

void SceneState::setCurrentPageIndex(Index::PageIndex index){
    if(index!=currentPageIndex){
        currentPageIndex=index;
        emit currentPageIndexChanged(index);
    }
}
