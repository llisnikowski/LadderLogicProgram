#include "containerLd.hpp"
#include "line.hpp"
#include "factory.hpp"

ContainerLd::ContainerLd(QQuickItem *parent)
    : QQuickItem{parent},
    container_{Line{INPUTS_IN_LINE_1 * NUMBERS_OBJECTS_PER_INPUT +
                    OUTPUTS_IN_LINE_1 * NUMBERS_OBJECTS_PER_OUTPUT},
               Line{INPUTS_IN_LINE_2 * NUMBERS_OBJECTS_PER_INPUT},
               Line{INPUTS_IN_LINE_3 * NUMBERS_OBJECTS_PER_INPUT}}
{
//
}

ContainerLd::Item ContainerLd::getItem(uint line, uint x)
{
    if(line >= container_.count()) return nullptr;
    if(x >= container_[line].count()) return nullptr;
    return container_.at(line).at(x);
}



void ContainerLd::changedFactory()
{
    if(factory_)
        container_[0][0] = factory_->create<Ld::Line>(this);
}
