#include "containerLd.hpp"
#include "base.hpp"
#include "input.hpp"
#include "line.hpp"
#include "node.hpp"
#include "factory.hpp"
#include "type.hpp"


ContainerLd::ContainerLd(QQuickItem *parent)
    : QQuickItem{parent},
    container_{Line{NUMBERS_OBJECTS_FOR_LINE_1, nullptr},
               Line{NUMBERS_OBJECTS_FOR_LINE_2, nullptr},
               Line{NUMBERS_OBJECTS_FOR_LINE_3, nullptr}}
{
}

ContainerLd::~ContainerLd()
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
        iteratorLine(line, itType,fun);
        if(endLineFun) endLineFun(line);
    }
}

void ContainerLd::iteratorLine(uint line, ItType itType, std::function<ItArg> fun)
{
    if(line >= 3) return;
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
}

QString ContainerLd::getSchemat(bool drawNull)
{
    QString schemat;
    iteratorLineX(ItAll,
        [&schemat, drawNull](uint line, uint x, Ld::Base* obj){
            if(!obj){
                if(drawNull) schemat += '.';
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
        addLineIfLineIsEmpty(0);
    }
}




bool ContainerLd::add(Ld::Drag *obj, uint line, uint x)
{
    if(!obj) return false;
    if(obj->getType() >= Ld::Type::Input){
        if(!addInput(static_cast<Ld::Input*>(obj), line, x)) return false;
        insertNode(line-1);
        insertNode(line);
        addLineIfLineIsEmpty(line + 1);
    }
    else if(obj->getType() >= Ld::Type::Output){
        if(addOuput(static_cast<Ld::Output*>(obj), line, x)) return false;
    }

    return true;
}

bool ContainerLd::addInput(Ld::Input *obj, uint line, uint x)
{
    if(!obj) return false;
    if(line >= container_.count()) return false;
    if(getNumberObjectInLine(line, Ld::Type::Input)
        >= MAX_INPUT_IN_LINE[line]) return false;
    x = x % 2 ? x : x+1;
    int freePlace = findFreePlace(line, x, true);
    if(freePlace < 0) return false;
    if(freePlace > x){
        if(!shiftRightObject(line, x, 2)) return false;
    }
    if(container_[line][x-1] == nullptr) return false;
    container_[line][x] = obj->clone(this);
    container_[line][x+1] = factory_->create<Ld::Line>(this,{64,64});

    return true;
}

bool ContainerLd::addOuput(Ld::Output *obj, uint line, uint x)
{
    if(!obj) return false;
    if(line >= container_.count()) return false;
    if(line != 0) return false;
    if(getNumberObjectInLine(line, Ld::Type::Output) >= 1) return false;
    x = x % 2 ? x : x+1;
    int freePlace = findFreePlace(line, x, true);
    if(freePlace < 0) return false;
    if(x < freePlace) return false;
    if(container_[line][x-1] == nullptr) return false;
    container_[line][x] = obj->clone(this);
    container_[line][x+1] = factory_->create<Ld::Line>(this,{64,64});

    return true;
}

bool ContainerLd::remove(uint line, int x)
{
    if(line >= container_.count()) return false;
    if(x >= container_[line].count()) return false;
    Ld::Base *obj = container_[line][x];
    if(!obj) return false;
    if(obj->getType() < Ld::Type::Drag) return false;
    Ld::Base *nextObj = container_[line][x+1];
    if(!nextObj) return false;
    delete obj;
    delete nextObj;
    container_[line][x+1] = nullptr;
    container_[line][x] = nullptr;

    shiftUp();
    if(!container_[line][x]) shiftLeftObject(line, x+2, 2);
    removeUnnecesseryNode();
    removeEmptyLine();
    return true;
}



int ContainerLd::findFreePlace(uint line, uint fromX, bool toNode)
{
    if(line >= 3) return -1;
    for(int x = fromX; x < container_[line].count() - 1; x++){
        Ld::Base *obj = container_[line][x];
        Ld::Base *nextObj = container_[line][x];
        if(!obj){
            if(!nextObj) return x;
            else return -1;
        }
        else if(toNode && obj->getType() >= Ld::Type::Node){
            return -1;
        }
    }
    return -1;
}

int ContainerLd::findNode(uint line)
{
    if(line >= 3) return -1;
    for(int x = 0; x < container_[line].count(); x++){
        Ld::Base *obj = container_[line][x];
        if(!obj) continue;
        if(obj->getType() >= Ld::Type::Node){
            return x;
        }
    }
    return -1;
}

int ContainerLd::getNumberObjectInLine(uint line, Ld::Type type)
{
    int numberObject = 0;
    iteratorLine(line, ItAll, [type, &numberObject](uint line, uint x, Ld::Base* obj){
        if(!obj){
            if(type == Ld::Type::None) numberObject++;
        }
        else if(obj->getType() >= type){
            numberObject++;
        }
    });
    return numberObject;
}

bool ContainerLd::shiftRightObject(uint line, uint from, uint distance)
{
    if(line >= 3) return false;

    auto copyFrom = container_[line].end() - 1;
    auto copyTo = copyFrom;
    auto copyBegin = container_[line].begin() + from;

    for(int i = 0; i < distance; i++){
        if(*copyFrom--) return false;
    }
    while(copyFrom >= copyBegin){
        *copyTo-- = *copyFrom;
        *copyFrom = nullptr;
        copyFrom--;
    }
    return true;
}

bool ContainerLd::shiftLeftObject(uint line, uint from, uint distance)
{
    if(line >= 3) return false;
    auto copyTo = container_[line].begin() + from - distance;
    auto copyFrom = copyTo + distance;

    auto checkNull = copyTo;
    for(int i = 0; i < distance; i++){
        if(*checkNull++) return false;
    }

    while(copyFrom < container_[line].end()){
        *copyTo++ = *copyFrom;
        *copyFrom = nullptr;
        copyFrom++;
    }
    return true;
}

void ContainerLd::addLineIfLineIsEmpty(uint line)
{
    if(line >= 3) return;
    if(!container_[line][0]){
        container_[line][0] = factory_->create<Ld::Line>(this,{64,64});
    }
}

void ContainerLd::insertNode(uint line)
{
    if(getNumberObjectInLine(line, Ld::Type::Node) >= 1) return;
    if(getNumberObjectInLine(line, Ld::Type::Input) <= 0) return;

    if(getNumberObjectInLine(line+1, Ld::Type::Input) <= 0 &&
        getNumberObjectInLine(line-1, Ld::Type::Input) <= 0) return;

    if(line == 0){
        if(shiftRightObject(line, NODE_POSITION, 2)){
            container_[line][NODE_POSITION] = factory_->create<Ld::Node>(this,{64,64});
            container_[line][NODE_POSITION+1] = factory_->create<Ld::Line>(this,{64,64});
        }
    }
    else{
        if(container_[line][NODE_POSITION] == nullptr)
        container_[line][NODE_POSITION] = factory_->create<Ld::Node>(this,{64,64});
    }
}

void ContainerLd::removeUnnecesseryNode()
{
    for(int line = container_.count() - 1; line >= 0 ; line--){
        int nodePosition = findNode(line);
        if(nodePosition < 0) continue;
        bool remove = false;
        if(getNumberObjectInLine(line, Ld::Type::Input) <= 0) remove = true;
        if(getNumberObjectInLine(line-1, Ld::Type::Input) <= 0 &&
            getNumberObjectInLine(line+1, Ld::Type::Input) <= 0) remove = true;

        if(remove){
            delete container_[line][nodePosition];
            container_[line][nodePosition] = nullptr;
            if(line == 0){
                delete container_[line][nodePosition+1];
                container_[line][nodePosition+1] = nullptr;
                shiftLeftObject(line, nodePosition + 2, 2);
            }
        }
    }
}

void ContainerLd::removeEmptyLine()
{
    for(int line = container_.count() - 1; line >= 1 ; line--){
        if(getNumberObjectInLine(line, Ld::Type::Base) == 1 &&
            getNumberObjectInLine(line-1, Ld::Type::Base) == 1){
            Ld::Base *obj = container_[line][0];
            if(!obj) return;
            delete obj;
            container_[line][0] = nullptr;
        }
    }
}

void ContainerLd::shiftUp()
{
    for(int line = 0; line < container_.count() - 1; line++){
        if(!container_[line][1] && !container_[line][2] &&
            getNumberObjectInLine(line + 1, Ld::Type::Base) > 1){
            container_[line][1] = container_[line + 1][1];
            container_[line][2] = container_[line + 1][2];
            container_[line + 1][1] = nullptr;
            container_[line + 1][2] = nullptr;
        }
    }
}


















