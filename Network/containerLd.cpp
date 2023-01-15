#include "containerLd.hpp"
#include "base.hpp"
#include "drag.hpp"
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
    updateLineDisplay();
    updateSize();
    updateLdObjectData();
    setHeight(container_.count() * LD_H);
}

ContainerLd::~ContainerLd()
{
}

Ld::Base *ContainerLd::getItem(Position poz)
{
    if(poz.line < 0) return nullptr;
    if(poz.line >= container_.count()) return nullptr;
    if(poz.x < 0) return nullptr;
    if(poz.x >= container_[poz.line].count()) return nullptr;
    return container_.at(poz.line).at(poz.x);
}

const Ld::Base *ContainerLd::getItem(Position poz) const
{
    if(poz.line < 0) return nullptr;
    if(poz.line >= container_.count()) return nullptr;
    if(poz.x < 0) return nullptr;
    if(poz.x >= container_[poz.line].count()) return nullptr;
    return container_.at(poz.line).at(poz.x);
}


Ld::Address *ContainerLd::getAddressItem(Position poz)
{
    auto obj = getItem(poz);
    if(!obj) return nullptr;
    if(obj->getType() >= Ld::Type::Address){
        return static_cast<Ld::Address*>(obj);
    }
    return nullptr;
}

const Ld::Address *ContainerLd::getAddressItem(Position poz) const
{
    auto obj = getItem(poz);
    if(!obj) return nullptr;
    if(obj->getType() >= Ld::Type::Address){
        return static_cast<const Ld::Address*>(obj);
    }
    return nullptr;
}

void ContainerLd::iteratorLineX(QVector<Ld::Type> types, std::function<ItArg> fun,
                       std::function<ItEndLineArg> endLineFun)
{
    if(!fun) return;
    for(int line = 0; line < container_.count(); line++){
        iteratorLine(line, types, fun);
        if(endLineFun) endLineFun(line);
    }
}

void ContainerLd::iteratorXLine(QVector<Ld::Type> types, std::function<ItArg> fun,
                                std::function<ItEndXArg> endXFun)
{
    if(!fun) return;
    for(int x = 0; x < container_[0].count(); x++){
        iteratorX(x, types, fun);
        if(endXFun) endXFun(x);
    }
}

void ContainerLd::iteratorLine(int line, QVector<Ld::Type> types,
                               std::function<ItArg> fun)
{
    if(line < 0) return;
    if(line >= container_.count()) return;
    for(int x = 0; x < container_[line].count(); x++){
        Ld::Base *obj = container_[line][x];
        if(!obj) continue;
        for(auto type :types){
            if(obj->getType() >= type){
                fun({line, x}, obj);
                break;
            }
        }
    }
}

void ContainerLd::iteratorLine(int line, QVector<Ld::Type> types,
                               std::function<ItArgConst> fun) const
{
    if(line < 0) return;
    if(line >= container_.count()) return;
    for(int x = 0; x < container_[line].count(); x++){
        Ld::Base *obj = container_[line][x];
        if(!obj) continue;
        for(auto type :types){
            if(obj->getType() >= type){
                fun({line, x}, obj);
                break;
            }
        }
    }
}

void ContainerLd::iteratorX(int x, QVector<Ld::Type> types, std::function<ItArg> fun)
{
    if(x >= container_[0].count()) return;
    Ld::Base *obj{};
    for(int line = 0; (obj = getItem({line, x})); line++){
        if(!obj) continue;
        for(auto type :types){
            if(obj->getType() >= type){
                fun({line, x}, obj);
                break;
            }
        }
    }
}

QString ContainerLd::getSchemat()
{
    QString schemat;
    iteratorLineX({Ld::Type::Base},
        [&schemat](Position poz, Ld::Base* obj){
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


bool ContainerLd::add(Ld::Drag *obj, Position poz)
{
    if(!obj) return false;
    if(obj->getType() >= Ld::Type::Input){
        return addInput(static_cast<Ld::Input*>(obj), poz);
    }
    else if(obj->getType() >= Ld::Type::Output){
        if(addOuput(static_cast<Ld::Output*>(obj), poz)) return false;
    }

    return true;
}

bool ContainerLd::addInput(Ld::Input *obj, Position poz)
{
    if(!setToNearestAddresItem(poz)) return false;
    if(!checkAddInputCondition(obj, poz)) return false;

    container_[poz.line].insert(poz.x, FactoryLd::initObject(obj->clone(this)));
    container_[poz.line].insert(poz.x + 1, FactoryLd::create<Ld::Line>(this));

    insertNode();
    addLineIfLineIsEmpty(poz.line + 1);
    updateLineDisplay();
    updateSize();
    updateLdObjectData();
    emit addLdObject(this);
    return true;
}

bool ContainerLd::addOuput(Ld::Output *obj, Position poz)
{
    if(!setToNearestAddresItem(poz, true)) return false;
    if(!checkAddOutputCondition(obj, poz)) return false;

    container_[poz.line].insert(poz.x, FactoryLd::initObject(obj->clone(this)));
    container_[poz.line].insert(poz.x+1, FactoryLd::create<Ld::Line>(this));

    updateLineDisplay();
    updateSize();
    updateLdObjectData();
    emit addLdObject(this);
    return true;
}

bool ContainerLd::remove(Position poz)
{
    if(!setToNearestAddresItem(poz, false)) return false;
    if(!checkRemoveCondition(poz)) return false;

    container_[poz.line][poz.x+1]->deleteLater();
    container_[poz.line][poz.x]->deleteLater();
    container_[poz.line].remove(poz.x, 2);

    shiftUp();
    removeUnnecesseryNode();
    removeEmptyLine();
    updateLineDisplay();
    updateSize();
    updateLdObjectData();
    return true;
}

bool ContainerLd::move(Position fromPoz, Position toPoz)
{
    if(!setToNearestAddresItem(fromPoz)) return false;
    if(!setToNearestAddresItem(toPoz)) return false;
    if(!checkMoveCondition(fromPoz, toPoz)) return false;

    if(fromPoz.line == toPoz.line && toPoz.x > fromPoz.x){
        toPoz.x -= 2;
    }

    Ld::Drag *moveObj = getAddressItem(fromPoz);
    Ld::Base *moveNextObj = getItem(fromPoz + Position{0, 1});
    container_[fromPoz.line][fromPoz.x] = nullptr;
    container_[fromPoz.line][fromPoz.x+1] = nullptr;
    container_[fromPoz.line].remove(fromPoz.x, 2);
    container_[toPoz.line].insert(toPoz.x, moveObj);
    container_[toPoz.line].insert(toPoz.x+1, moveNextObj);

    insertNode();
    shiftUp();
    addLineIfLineIsEmpty((fromPoz.line > toPoz.line ? fromPoz.line : toPoz.line) + 1);
    removeUnnecesseryNode();
    removeEmptyLine();
    updateLineDisplay();
    updateSize();
    updateLdObjectData();
    return true;
}

bool ContainerLd::checkAddCondition(const Ld::Drag *obj, Position poz) const
{
    if(!setToNearestAddresItem(poz)) return false;
    if(!obj) return false;
    if(obj->getType() >= Ld::Type::Input){
        return checkAddInputCondition(static_cast<const Ld::Input*>(obj), poz);
    }
    else if(obj->getType() >= Ld::Type::Output){
        return checkAddOutputCondition(static_cast<const Ld::Output*>(obj), poz);
    }
    return false;
}

bool ContainerLd::checkAddInputCondition(const Ld::Input *obj, Position poz) const
{
    if(!obj) return false;
    if(!setToNearestAddresItem(poz)) return false;
    if(getNumberObjectInLine(poz.line, Ld::Type::Input)
        >= MAX_INPUT_IN_LINE[poz.line]) return false;
    int outputPlace = find(poz.line, Ld::Type::Output);
    if(outputPlace > 0 && poz.x > outputPlace) return false;
    int node = find(poz.line, Ld::Type::Node);
    if(node > -1 && poz.x <= node) return false;
    return true;
}

bool ContainerLd::checkAddOutputCondition(const Ld::Output *obj, Position poz) const
{
    if(!obj) return false;
    if(!setToNearestAddresItem(poz, true)) return false;
    if(poz.line > 0) return false;
    if(getNumberObjectInLine(poz.line, Ld::Type::Output) >= 1) return false;
    if(poz.x > container_[poz.line].count()) return false;

    return true;
}

bool ContainerLd::checkRemoveCondition(Position poz) const
{
    if(!setToNearestAddresItem(poz, false)) return false;
    Ld::Base *obj = container_[poz.line][poz.x];
    if(!obj) return false;
    if(obj->getType() < Ld::Type::Drag) return false;
    Ld::Base *nextObj = container_[poz.line][poz.x+1];
    if(!nextObj) return false;

    return true;
}

bool ContainerLd::checkMoveCondition(Position fromPoz, Position toPoz) const
{
    if(!setToNearestAddresItem(fromPoz)) return false;
    if(!setToNearestAddresItem(toPoz)) return false;

    Ld::Base *fromObj = container_[fromPoz.line][fromPoz.x];
    if(!fromObj) return false;
    if(fromObj->getType() < Ld::Type::Drag) return false;
    Ld::Base *nextObj = container_[fromPoz.line][fromPoz.x];
    if(!nextObj) return false;

    const Ld::Drag *moveObj = getAddressItem(fromPoz);
    if(!moveObj) return false;
    if(moveObj->getType() >= Ld::Type::Input){
        if(toPoz.line >= container_.count()) return false;
        if(find(toPoz.line, Ld::Type::Output) >= 0
            && toPoz.x > find(toPoz.line, Ld::Type::Output)) return false;

        int node = find(toPoz.line, Ld::Type::Node);
        if(fromPoz.line == toPoz.line){
            if(fromPoz.x < toPoz.x){
                if((node > fromPoz.x && node < toPoz.x) &&
                    (getNumberObjectInLine(toPoz.line, Ld::Type::Input)
                     >= MAX_INPUT_IN_LINE[toPoz.line])) return false;
            }
            else{
                if(node < fromPoz.x && node >= toPoz.x) return false;
            }
        }
        else{
            if(getNumberObjectInLine(toPoz.line, Ld::Type::Input)
                >= MAX_INPUT_IN_LINE[toPoz.line]) return false;
            if(node > -1 && toPoz.x <= node) return false;
        }

    }
    else if(moveObj->getType() >= Ld::Type::Output){
        if(toPoz.line != 0) return false;
        if(fromPoz.x > toPoz.x) return false;
    }
    return true;
}


int ContainerLd::find(int line, Ld::Type type) const
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

int ContainerLd::getNumberObjectInLine(int line, Ld::Type type) const
{
    int numberObject = 0;
    iteratorLine(line, {Ld::Type::Base}, [type, &numberObject](Position poz, Ld::Base* obj){
        if(!obj){
            if(type == Ld::Type::None) numberObject++;
        }
        else if(obj->getType() >= type){
            numberObject++;
        }
    });
    return numberObject;
}

bool ContainerLd::setToNearestAddresItem(Position &pos, bool lastField) const
{
    if(pos.line < 0 || pos.line > container_.count() - 1) return false;
    if(!lastField){
        if(pos.x < 0 || pos.x > container_[pos.line].count() - 1) return false;
    }
    else{
        if(pos.x < 0 || pos.x > container_[pos.line].count()) return false;
    }
    pos.x = (pos.x / 2) * 2 + 1;
    return true;
}


void ContainerLd::addLineIfLineIsEmpty(int line)
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
    qreal curY = 0;
    iteratorLineX({Ld::Type::Base}, [this, &curX, &curY](Position poz, Ld::Base* obj){
        qreal width = 0;
        qreal height = LD_H;
        if(!obj) return;
        if(poz.x == 0){
            if(poz.x == container_[poz.line].count() - 1
                && poz.line >= 1){
                height = LD_H/2;
            }
            curY += height;
        }
        if(obj->getType() >= Ld::Type::Drag) width = LD_W;
        else if(obj->getType() >= Ld::Type::Node) width = NODE_W;
        else if(poz.x == container_[poz.line].count() - 1) {
            if(poz.line <= 1){
                width = MAX_LENGTH_LINE - curX;
            }
            else{
                width = 1.5 * LD_W + LINE_BESIDE_NODE + NODE_W;
            }
        }
        else if(obj->getType() >= Ld::Type::Line){
            if(container_[poz.line][poz.x+1]->getType() >= Ld::Type::Output){
                width = MAX_LENGTH_LINE - curX - LD_W * 1.5;
            }
            else if(poz.x == 0) {
                width = LD_W / 2;
            }
            else if(poz.x == container_[poz.line].count() - 1){
                width = LD_W / 2;
            }
            else if(container_[poz.line][poz.x-1]->getType() >= Ld::Type::Node ||
                     container_[poz.line][poz.x+1]->getType() >= Ld::Type::Node){
                width = LINE_BESIDE_NODE;
            }
            else{
                width = LD_W;
            }
        }
        else width = LD_W;

        obj->setSize({static_cast<qreal>(width), height});
        obj->setX(curX);
        obj->setY(poz.line * LD_H);
        curX += width;
    },
    [&curX](int line){
        curX = 0;
        });
    setHeight(curY);
}

void ContainerLd::updateLdObjectData()
{
    iteratorLineX({Ld::Type::Drop, Ld::Type::Drag}, [this](Position poz, Ld::Base* obj){
        if(obj->getType() >= Ld::Type::Drag){
            static_cast<Ld::Drag*>(obj)->setDragData(new DragNetworkData(obj,
                        obj->getData(), this, poz));
        }
        else if(obj->getType() >= Ld::Type::Drop){
            static_cast<Ld::Drop*>(obj)->setDropValidator(
                new DropNetworkValidator(obj, this, poz));
        }
    });
}

void ContainerLd::updateLineDisplay()
{
    iteratorLineX({Ld::Type::Line}, [this](Position poz, Ld::Base* obj){
        auto lineLd = static_cast<Ld::Line*>(obj);
        if(poz.x == 0){
            if(poz.x == container_[poz.line].count() - 1){
                if(poz.line == 0){
                    lineLd->setDisplayType(Ld::Line::DisplayType::fromLeftToRigth);
                }
                else{
                    lineLd->setDisplayType(Ld::Line::DisplayType::invisible);
                }
            }
            else{
                lineLd->setDisplayType(Ld::Line::DisplayType::fromLeft);
            }
        }
        else if(poz.x==container_[poz.line].count()-1){
            lineLd->setDisplayType(Ld::Line::DisplayType::toRight);
        }
        else{
            lineLd->setDisplayType(Ld::Line::DisplayType::normal);
        }
    });
}

void ContainerLd::updateNodeDisplay()
{
    iteratorLineX({Ld::Type::Node}, [this](Position poz, Ld::Base* obj){
        Ld::Node* node = static_cast<Ld::Node*>(obj);
        node->displayLine(getItem(poz + Position{0, 1}),
                          getItem(poz + Position{-1, 0}),
                          getItem(poz + Position{1, 0}));
    });
}








QDataStream &operator<<(QDataStream &stream, ContainerLd &containerLd)
{
    int count = 0;
    containerLd.iteratorLineX(
        {Ld::Type::Address}, [&count](Position poz, Ld::Base* obj){
            count++;
        });
    stream << count;
    containerLd.iteratorXLine(
        {Ld::Type::Address}, [&stream](Position poz, Ld::Base* obj){
            stream << poz << obj->getData();
        });
    return stream;
}


QDataStream &operator>>(QDataStream &stream, ContainerLd &containerLd)
{
    int count;
    stream >> count;
    Position pos;
    QByteArray ldByteArray;
    for(int i = 0; i < count; i++){
        stream >> pos >> ldByteArray;
        Ld::Base *newObj = getLdObject(ldByteArray);
        if(!newObj) return stream;
        if(!(newObj->getType() >= Ld::Type::Drag)){
            delete newObj;
            return stream;
        }
        containerLd.add(static_cast<Ld::Drag*>(newObj), pos);
        delete newObj;
    }
    return stream;
}






