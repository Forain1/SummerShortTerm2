#include "scenestate.h"

SceneState::SceneState(QObject *parent)
    : QObject{parent}
{
    currentPageIndex=PageIndex::MenuIndex;
}

void SceneState::setCurrentPageIndex(PageIndex::Index index){
    if(index!=currentPageIndex){
        currentPageIndex=index;
        emit currentPageIndexChanged(index);
    }
}
