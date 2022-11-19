#include "containerLd.hpp"
#include "line.hpp"
#include "factory.hpp"


ContainerLd::ContainerLd(QQuickItem *parent)
    : QQuickItem{parent},
    container_{Line{NUMBERS_OBJECTS_FOR_LINE_1},
               Line{NUMBERS_OBJECTS_FOR_LINE_2},
               Line{NUMBERS_OBJECTS_FOR_LINE_3}}
{
}

ContainerLd::Item ContainerLd::getItem(uint line, uint x)
{
    if(line >= container_.count()) return nullptr;
    if(x >= container_[line].count()) return nullptr;
    return container_.at(line).at(x);
}



void ContainerLd::changedFactory()
{
    if(factory_){
        container_[0][0] = factory_->create<Ld::Line>(this,{MAX_LENGTH_LINE,64});
    }
}
