#include "containerLd.hpp"
#include "line.hpp"
#include "factory.hpp"
#include "type.hpp"


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

void ContainerLd::iteratorLineX(ItType itType, std::function<ItArg> fun,
                       std::function<ItEndLineArg> endLineFun)
{
    if(!fun) return;
    for(int line = 0; line < container_.count(); line++){
        for(int x = 0; x < container_[line].count(); x++){
            Ld::Base *obj = container_[line][x];
            if(!obj){
                if(itType & ItNull) fun(line, x, obj);
            }
            else if(obj->getType() >= Ld::Type::Input){
                if(itType & ItIn)  fun(line, x, obj);
            }
            else if(obj->getType() >= Ld::Type::Output){
                if(itType & ItOut)  fun(line, x, obj);
            }
            else if(obj->getType() >= Ld::Type::Line){
                if(itType & ItLine)  fun(line, x, obj);
            }
            else if(obj->getType() >= Ld::Type::Node){
                if(itType & ItNode)  fun(line, x, obj);
            }
        }
        if(endLineFun) endLineFun(line);
    }
}

QString ContainerLd::getSchemat()
{
    QString schemat;
    iteratorLineX(ItAll,[&schemat](int line, int x, Ld::Base* obj){
            if(!obj){
                schemat += '.';
            }
            else if(obj->getType() >= Ld::Type::Input){
                schemat += 'I';
            }
            else if(obj->getType() >= Ld::Type::Output){
                schemat += 'O';
            }
            else if(obj->getType() >= Ld::Type::Line){
                schemat += '-';
            }
            else if(obj->getType() >= Ld::Type::Node){
                schemat += '+';
            }
        },
        [&schemat](int line){
            schemat += ';';
        }
    );

    return schemat;
}



void ContainerLd::changedFactory()
{
    if(factory_){
        container_[0][0] = factory_->create<Ld::Line>(this,{MAX_LENGTH_LINE,64});
    }
}
