#include "containerLd.hpp"
#include "base.hpp"
#include "dropNetworkValidator.hpp"
#include "dragNetworkData.hpp"
#include "input.hpp"
#include "line.hpp"
#include "node.hpp"
#include "factoryLd.hpp"
#include "type.hpp"

int ContainerLd::currentId = 0;

ContainerLd::ContainerLd(QQuickItem *parent)
    : QQuickItem{parent},
    id_{currentId++}, container_{}
{
    addLineIfLineIsEmpty(0);
    updateSize();
    updateLdObjectData();
    setHeight(container_.count() * LD_H);
}

ContainerLd::~ContainerLd()
{
}

Ld::Base *ContainerLd::getItem(uint line, uint x)
{
    if(line >= container_.count()) return nullptr;
    if(x >= container_[line].count()) return nullptr;
    return container_.at(line).at(x);
}

const Ld::Base *ContainerLd::getItem(uint line, uint x) const
{
    if(line >= container_.count()) return nullptr;
    if(x >= container_[line].count()) return nullptr;
    return container_.at(line).at(x);
}


Ld::Drag *ContainerLd::getDragItem(uint line, uint x)
{
    auto obj = getItem(line, x);
    if(!obj) return nullptr;
    if(obj->getType() >= Ld::Type::Drag){
        return static_cast<Ld::Drag*>(obj);
    }
    return nullptr;
}

const Ld::Drag *ContainerLd::getDragItem(uint line, uint x) const
{
    auto obj = getItem(line, x);
    if(!obj) return nullptr;
    if(obj->getType() >= Ld::Type::Drag){
        return static_cast<const Ld::Drag*>(obj);
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

void ContainerLd::iteratorLine(uint line, ItType itType,
                               std::function<ItArg> fun)
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

void ContainerLd::iteratorLine(uint line, ItType itType,
                               std::function<ItArgConst> fun) const
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

QString ContainerLd::getSchemat()
{
    QString schemat;
    iteratorLineX(ItAll,
        [&schemat](uint line, uint x, Ld::Base* obj){
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

int ContainerLd::getId() const
{
    return id_;
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

    container_[line].insert(x, FactoryLd::initObject(obj->clone(this)));
    container_[line].insert(x + 1, FactoryLd::create<Ld::Line>(this));

    insertNode();
    addLineIfLineIsEmpty(line + 1);
    updateSize();
    updateLdObjectData();
    emit addLdObject(this);
    return true;
}

bool ContainerLd::addOuput(Ld::Output *obj, uint line, uint x)
{
    x = x % 2 ? x : x+1;
    if(!checkAddOutputCondition(obj, line, x)) return false;

    container_[line].insert(x, FactoryLd::initObject(obj->clone(this)));
    container_[line].insert(x+1, FactoryLd::create<Ld::Line>(this));

    updateSize();
    updateLdObjectData();
    emit addLdObject(this);
    return true;
}

bool ContainerLd::remove(uint line, uint x)
{
    if(!checkRemoveCondition(line, x)) return false;

    container_[line][x+1]->deleteLater();
    container_[line][x]->deleteLater();
    container_[line].remove(x, 2);

    shiftUp();
    removeUnnecesseryNode();
    removeEmptyLine();
    updateSize();
    updateLdObjectData();
    return true;
}

bool ContainerLd::move(uint fromLine, uint fromX, uint toLine, uint toX)
{
    toX = (toX / 2) * 2 + 1;
    fromX = (fromX / 2) * 2 + 1;
    if(!checkMoveCondition(fromLine, fromX, toLine, toX)) return false;

    if(fromLine == toLine && toX > fromX){
        toX -= 2;
    }

    Ld::Drag *moveObj = getDragItem(fromLine, fromX);
    Ld::Base *moveNextObj = getItem(fromLine, fromX + 1);
    container_[fromLine][fromX] = nullptr;
    container_[fromLine][fromX+1] = nullptr;
    container_[fromLine].remove(fromX, 2);
    container_[toLine].insert(toX, moveObj);
    container_[toLine].insert(toX+1, moveNextObj);

    insertNode();
    shiftUp();
    addLineIfLineIsEmpty((fromLine > toLine ? fromLine : toLine) + 1);
    removeUnnecesseryNode();
    removeEmptyLine();
    updateSize();
    updateLdObjectData();
    return true;
}

bool ContainerLd::checkAddCondition(const Ld::Drag *obj, uint line, uint x) const
{
    x = x % 2 ? x : x+1;
    if(!obj) return false;
    if(obj->getType() >= Ld::Type::Input){
        return checkAddInputCondition(static_cast<const Ld::Input*>(obj), line, x);
    }
    else if(obj->getType() >= Ld::Type::Output){
        return checkAddOutputCondition(static_cast<const Ld::Output*>(obj), line, x);
    }
    return false;
}

bool ContainerLd::checkAddInputCondition(const Ld::Input *obj, uint line, uint x) const
{
    x = x % 2 ? x : x+1;
    if(!obj) return false;
    if(line >= container_.count()) return false;
    if(getNumberObjectInLine(line, Ld::Type::Input)
        >= MAX_INPUT_IN_LINE[line]) return false;
    if(x > container_[line].count()) return false;
    int outputPlace = find(line, Ld::Type::Output);
    if(outputPlace > 0 && x > outputPlace) return false;
    int node = find(line, Ld::Type::Node);
    if(node > -1 && x <= node) return false;
    return true;
}

bool ContainerLd::checkAddOutputCondition(const Ld::Output *obj, uint line, uint x) const
{
    if(!obj) return false;
    if(line >= container_.count()) return false;
    if(line != 0) return false;
    if(getNumberObjectInLine(line, Ld::Type::Output) >= 1) return false;
    if(x > container_[line].count()) return false;

    return true;
}

bool ContainerLd::checkRemoveCondition(uint line, uint x) const
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

bool ContainerLd::checkMoveCondition(uint fromLine, uint fromX, uint toLine, uint toX) const
{
    toX = (toX / 2) * 2 + 1;
    fromX = (fromX / 2) * 2 + 1;
    if(fromLine >= container_.count()) return false;
    if(fromX >= container_[fromLine].count()) return false;
    if(toLine >= container_.count()) return false;
    if(toX >= container_[toLine].count() + 1) return false;

    Ld::Base *fromObj = container_[fromLine][fromX];
    if(!fromObj) return false;
    if(fromObj->getType() < Ld::Type::Drag) return false;
    Ld::Base *nextObj = container_[fromLine][fromX];
    if(!nextObj) return false;

    const Ld::Drag *moveObj = getDragItem(fromLine, fromX);
    if(!moveObj) return false;
    if(moveObj->getType() >= Ld::Type::Input){
        if(toLine >= container_.count()) return false;
        if(find(toLine, Ld::Type::Output) >= 0
            && toX > find(toLine, Ld::Type::Output)) return false;

        int node = find(toLine, Ld::Type::Node);
        if(fromLine == toLine){
            if(fromX < toX){
                if((node > fromX && node < toX) &&
                    (getNumberObjectInLine(toLine, Ld::Type::Input)
                     >= MAX_INPUT_IN_LINE[toLine])) return false;
            }
            else{
                if(node < fromX && node >= toX) return false;
            }
        }
        else{
            if(getNumberObjectInLine(toLine, Ld::Type::Input)
                >= MAX_INPUT_IN_LINE[toLine]) return false;
            if(node > -1 && toX <= node) return false;
        }

    }
    else if(moveObj->getType() >= Ld::Type::Output){
        if(toLine != 0) return false;
        if(fromX > toX) return false;
    }
    return true;
}


int ContainerLd::find(uint line, Ld::Type type) const
{
    if(line >= container_.count()) return -1;
    for(int x = 0; x < container_[line].count(); x++){
        Ld::Base *obj = container_[line][x];
        if(!obj) continue;
        if(obj->getType() >= type){
            return x;
        }
    }
    return -1;
}

int ContainerLd::getNumberObjectInLine(uint line, Ld::Type type) const
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


void ContainerLd::addLineIfLineIsEmpty(uint line)
{
    if(line >= 3) return;
    if(line == container_.count()){
        container_.append(Line{1, nullptr});
        container_[line][0] = FactoryLd::create<Ld::Line>(this);
        setHeight(container_.count() * LD_H);
    }
}

void ContainerLd::insertNode()
{
    for(int line = 0; line < container_.count(); line++){
        if(getNumberObjectInLine(line, Ld::Type::Node) >= 1) continue;
        if(getNumberObjectInLine(line, Ld::Type::Input) <= 0) continue;

        if(getNumberObjectInLine(line+1, Ld::Type::Input) <= 0 &&
            getNumberObjectInLine(line-1, Ld::Type::Input) <= 0) continue;

        if(line == 0){
            container_[line].insert(NODE_POSITION, FactoryLd::create<Ld::Node>(this));
            container_[line].insert(NODE_POSITION+1, FactoryLd::create<Ld::Line>(this));
        }
        else{
            if(container_[line].count() <= NODE_POSITION)
                container_[line].insert(NODE_POSITION, FactoryLd::create<Ld::Node>(this));
        }
    }
    updateNodeDisplay();
}

void ContainerLd::removeUnnecesseryNode()
{
    for(int line = container_.count() - 1; line >= 0 ; line--){
        int nodePosition = find(line, Ld::Type::Node);
        if(nodePosition < 0) continue;
        bool remove = false;
        if(getNumberObjectInLine(line, Ld::Type::Input) <= 0) remove = true;
        if(getNumberObjectInLine(line-1, Ld::Type::Input) <= 0 &&
            getNumberObjectInLine(line+1, Ld::Type::Input) <= 0) remove = true;

        if(remove){
            container_[line][nodePosition]->deleteLater();
            container_[line].remove(nodePosition);
            if(line == 0){
                container_[line][nodePosition-1]->deleteLater();
                container_[line].remove(nodePosition-1);
            }
        }
    }
    updateNodeDisplay();
}

void ContainerLd::removeEmptyLine()
{
    for(int line = container_.count() - 1; line >= 1 ; line--){
        if(getNumberObjectInLine(line, Ld::Type::Base) == 1 &&
            getNumberObjectInLine(line-1, Ld::Type::Input) == 0){
            Ld::Base *obj = container_[line][0];
            if(!obj) return;
            delete obj;
            container_.remove(line);
            setHeight(container_.count() * LD_H);
        }
    }
}

void ContainerLd::shiftUp()
{
    for(int line = 0; line < container_.count() - 1; line++){
        int node = find(line, Ld::Type::Node);
        if((node < 0 && getNumberObjectInLine(line, Ld::Type::Input) >= 1 )
            || node >= 3) continue;
        if(container_[line + 1].count() < 3) continue;
        container_[line].insert(1, container_[line + 1][1]);
        container_[line].insert(2, container_[line + 1][2]);
        container_[line + 1].remove(1, 2);
    }
}

void ContainerLd::updateSize()
{
    int curX = 0;
    iteratorLineX(ItAll, [this, &curX](uint line, uint x, Ld::Base* obj){
        int width = 0;
        if(!obj) return;
        if(obj->getType() >= Ld::Type::Drag) width = LD_W;
        else if(obj->getType() >= Ld::Type::Node) width = NODE_W;
        else if(x == container_[line].count() - 1) {
            if(line <= 1){
                width = MAX_LENGTH_LINE - curX;
            }
            else{
                width = 2 * LD_W + LINE_BESIDE_NODE + NODE_W;
            }
        }
        else if(obj->getType() >= Ld::Type::Line){
            if(container_[line][x+1]->getType() >= Ld::Type::Output){
                width = MAX_LENGTH_LINE - curX - LD_W * 2;
            }
            else if(x == 0) {
                width = LD_W;
            }
            else if(container_[line][x-1]->getType() >= Ld::Type::Node ||
                     container_[line][x+1]->getType() >= Ld::Type::Node){
                width = LINE_BESIDE_NODE;
            }
            else{
                width = LD_W;
            }
        }
        else width = LD_W;

        obj->setSize({static_cast<qreal>(width), LD_H});
        obj->setX(curX);
        obj->setY(line * LD_H);
        curX += width;
    },
    [&curX](uint line){
        curX = 0;
        });
}

void ContainerLd::updateLdObjectData()
{
    iteratorLineX(ItDropDrag, [this](uint line, uint x, Ld::Base* obj){
        if(obj->getType() >= Ld::Type::Drag){
            static_cast<Ld::Drag*>(obj)->setDragData(new DragNetworkData(obj,
                        obj->getData(), this, QPoint{(int)line, (int)x}));
        }
        else if(obj->getType() >= Ld::Type::Drop){
            static_cast<Ld::Drop*>(obj)->setDropValidator(
                new DropNetworkValidator(obj, this,
                                         QPoint{(int)line, (int)x}));
        }
    });
}

void ContainerLd::updateNodeDisplay()
{
    iteratorLineX(ItNode, [this](uint line, uint x, Ld::Base* obj){
        Ld::Node* node = static_cast<Ld::Node*>(obj);
        node->displayLine(getItem(line, x+1), getItem(line-1, x), getItem(line+1, x));
    });
}















