#include "containerLd.hpp"
#include "base.hpp"
#include "input.hpp"
#include "line.hpp"
#include "node.hpp"
#include "factory.hpp"
#include "type.hpp"


ContainerLd::ContainerLd(QQuickItem *parent)
    : QQuickItem{parent},
    container_{}
{
}

ContainerLd::~ContainerLd()
{
}





const ContainerLd::Item ContainerLd::getItem(uint line, uint x)
{
    if(line >= container_.count()) return nullptr;
    if(x >= container_[line].count()) return nullptr;
    return container_.at(line).at(x);
}

ContainerLd::Item ContainerLd::getItemNoConst(uint line, uint x)
{
    if(line >= container_.count()) return nullptr;
    if(x >= container_[line].count()) return nullptr;
    return container_.at(line).at(x);
}

const Ld::Drag *ContainerLd::getDragItem(uint line, uint x)
{
    auto obj = getItem(line, x);
    if(!obj) return nullptr;
    if(obj->getType() >= Ld::Type::Drag){
        return static_cast<const Ld::Drag*>(obj);
    }
    return nullptr;
}

Ld::Drag *ContainerLd::getDragItemNoConst(uint line, uint x)
{
    auto obj = getItem(line, x);
    if(!obj) return nullptr;
    if(obj->getType() >= Ld::Type::Drag){
        return static_cast<Ld::Drag*>(obj);
    }
    return nullptr;
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
    if(line >= container_.count()) return;
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
        return addInput(static_cast<Ld::Input*>(obj), line, x);
    }
    else if(obj->getType() >= Ld::Type::Output){
        if(addOuput(static_cast<Ld::Output*>(obj), line, x)) return false;
    }

    return true;
}

bool ContainerLd::addInput(Ld::Input *obj, uint line, uint x)
{
    x = x % 2 ? x : x+1;
    if(!checkAddInputCondition(obj, line, x)) return false;

//    shiftRightObject(line, x, 2);
    container_[line].insert(x, obj->clone(this));
    container_[line].insert(x + 1, factory_->create<Ld::Line>(this,{64,64}));
//    container_[line][x] = obj->clone(this);
//    container_[line][x+1] = factory_->create<Ld::Line>(this,{64,64});

    insertNode(line-1);
    insertNode(line);
    addLineIfLineIsEmpty(line + 1);

    return true;
}

bool ContainerLd::addOuput(Ld::Output *obj, uint line, uint x)
{
    x = x % 2 ? x : x+1;
    if(!checkAddOutputCondition(obj, line, x)) return false;

    container_[line].insert(x, obj->clone(this));
    container_[line].insert(x+1, factory_->create<Ld::Line>(this,{64,64}));

    return true;
}

bool ContainerLd::remove(uint line, int x)
{
    if(!checkRemoveCondition(line, x)) return false;

    delete container_[line][x+1];
    delete container_[line][x];
    container_[line].remove(x, 2);

    shiftUp();
//    if(!container_[line][x]) shiftLeftObject(line, x+2, 2);
    removeUnnecesseryNode();
    removeEmptyLine();
    return true;
}

bool ContainerLd::move(uint fromLine, int fromX, uint toLine, int toX)
{
    if(fromLine >= container_.count()) return false;
    toX = (toX / 2) * 2 + 1;
    fromX = (fromX / 2) * 2 + 1;
    if(fromX >= container_[fromLine].count()) return false;

    Ld::Drag *moveObj = getDragItemNoConst(fromLine, fromX);
    Ld::Base *moveNextObj = getItemNoConst(fromLine, fromX + 1);
    if(!moveObj || !moveNextObj) return false;
    if(!checkRemoveCondition(fromLine, fromX)) return false;


    container_[fromLine][fromX] = nullptr;
    container_[fromLine][fromX + 1] = nullptr;
    shiftLeftObject(fromLine, fromX+2, 2);

    if(!checkAddCondition(moveObj, toLine, toX)){
        container_[fromLine][fromX] = moveObj;
        container_[fromLine][fromX + 1] = moveNextObj;
        return false;
    }
    container_[toLine][toX] = moveObj;
    container_[toLine][toX+1] = moveNextObj;

    shiftUp();
    removeUnnecesseryNode();
    removeEmptyLine();
//    insertNode(line-1);
//    insertNode(line);
//    addLineIfLineIsEmpty(line + 1);

//    if(fromLine >= container_.count()
//        || toLine >= container_.count()) return false;
//    toX = (toX / 2) * 2 + 1;
//    fromX = (fromX / 2) * 2 + 1;
//    if(fromX >= container_[fromLine].count() ||
//       toX >= container_[toLine].count()) return false;



//    Ld::Base *obj = container_[fromLine][fromX];
//    if(!obj) return false;
//    if(obj->getType() < Ld::Type::Drag) return false;

//    if(fromLine == toLine){

//        if(toX >= fromX - 2 && toX <= fromX + 1) return false;
//        int nodePlace = findNode(toLine);
//        if(fromX < toX){
//            if(nodePlace > fromX && nodePlace < toX){
//                if(getNumberObjectInLine(fromLine, Ld::Type::Input)
//                    >= MAX_INPUT_IN_LINE[fromLine]) return false;
//            }
//            Ld::Base *moveObj1 = container_[fromLine][fromX];
//            container_[fromLine][fromX] = nullptr;
//            Ld::Base *moveObj2 = container_[fromLine][fromX+1];;
//            container_[fromLine][fromX+1] = nullptr;
//            if(!shiftLeftObject(fromLine, fromX+2, 2, toX+1)) return false;
//            container_[toLine][toX] = moveObj1;
//            container_[toLine][toX+1] = moveObj2;
//        }
//        else{

//        }
//    }
//    else{

//    }
    return true;
}

bool ContainerLd::checkAddCondition(const Ld::Drag *obj, uint line, uint x)
{
    if(!obj) return false;
    if(obj->getType() >= Ld::Type::Input){
        return checkAddInputCondition(static_cast<const Ld::Input*>(obj), line, x);
    }
    else if(obj->getType() >= Ld::Type::Output){
        return checkAddOutputCondition(static_cast<const Ld::Output*>(obj), line, x);
    }
    return false;
}

bool ContainerLd::checkAddInputCondition(const Ld::Input *obj, uint line, uint x)
{
    if(!obj) return false;
    if(line >= container_.count()) return false;
    if(getNumberObjectInLine(line, Ld::Type::Input)
        >= MAX_INPUT_IN_LINE[line]) return false;
    if(x > container_[line].count()) return false;
    int node = findNode(line);
    if(node > -1 && x <= node) return false;
    return true;
}

bool ContainerLd::checkAddOutputCondition(const Ld::Output *obj, uint line, uint x)
{
    if(!obj) return false;
    if(line >= container_.count()) return false;
    if(line != 0) return false;
    if(getNumberObjectInLine(line, Ld::Type::Output) >= 1) return false;
    if(x > container_[line].count()) return false;

    return true;
}

bool ContainerLd::checkRemoveCondition(uint line, int x)
{
    if(line >= container_.count()) return false;
    if(x >= container_[line].count()) return false;
    Ld::Base *obj = container_[line][x];
    if(!obj) return false;
    if(obj->getType() < Ld::Type::Drag) return false;
    Ld::Base *nextObj = container_[line][x+1];
    if(!nextObj) return false;

    return true;
}



int ContainerLd::findFreePlace(uint line, uint fromX, bool toNode)
{
    if(line >= container_.count()) return -1;
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
    if(line >= container_.count()) return -1;
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

bool ContainerLd::shiftRightObject(uint line, uint from, uint distance, uint to)
{
    if(line >= container_.count()) return false;

    auto copyFrom = std::min(container_[line].end() - 1,
                             container_[line].begin() + to);
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

bool ContainerLd::shiftLeftObject(uint line, uint from, uint distance, uint to)
{
    if(line >= container_.count()) return false;
    auto copyTo = container_[line].begin() + from - distance;
    auto copyFrom = copyTo + distance;
    auto limitCopy = std::min(container_[line].end(),
                              container_[line].begin() + to + 1);

    auto checkNull = copyTo;
    for(int i = 0; i < distance; i++){
        if(*checkNull++) return false;
    }

    while(copyFrom < limitCopy){
        *copyTo++ = *copyFrom;
        *copyFrom = nullptr;
        copyFrom++;
    }
    return true;
}

void ContainerLd::addLineIfLineIsEmpty(uint line)
{
    if(line >= 3) return;
    if(line == container_.count()){
        container_.append(Line{1, nullptr});
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
        container_[line].insert(NODE_POSITION, factory_->create<Ld::Node>(this,{64,64}));
        container_[line].insert(NODE_POSITION+1, factory_->create<Ld::Line>(this,{64,64}));
    }
    else{
        if(container_[line].count() <= NODE_POSITION)
            container_[line].insert(NODE_POSITION,factory_->create<Ld::Node>(this,{64,64}));
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
            container_[line].remove(nodePosition);
            if(line == 0){
                delete container_[line][nodePosition];
                container_[line].remove(nodePosition);
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
            container_.remove(line);
        }
    }
}

void ContainerLd::shiftUp()
{
    for(int line = 0; line < container_.count() - 1; line++){
        int node = findNode(line);
        if(node < 0 || node >= 3) continue;
        if(container_[line + 1].count() < 3) continue;
        container_[line].insert(1, container_[line + 1][1]);
        container_[line].insert(2, container_[line + 1][2]);
        container_[line + 1].remove(1, 2);
    }
}


















