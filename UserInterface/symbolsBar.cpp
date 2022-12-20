/*!
 * \file symbolsBar.cpp
 * \author Łukasz Liśnikowski
*/
#include "symbolsBar.hpp"
#include "contact.hpp"
#include "coil.hpp"
#include "counter.hpp"
#include "dragNetworkData.hpp"
#include "dropDeleter.hpp"
#include "emptyDrop.hpp"
#include "factoryLd.hpp"
#include "imitatorLd.hpp"
#include "text.hpp"
#include "timer.hpp"
#include "type.hpp"
#include "weektimer.hpp"
#include <QDebug>

namespace Ld {

SymbolsBar::SymbolsBar()
{

}


void SymbolsBar::setNewParentItem(QQuickItem *parentItem)
{
    if(!parentItem) return;
    setWidth(parentItem->width());
    setHeight(parentItem->height());
    setParentItem(parentItem);

    connect(parentItem, &QQuickItem::heightChanged, this,
            [this, parentItem](){this->setHeight(parentItem->height());}
    );

    FactoryLd::create<Ld::EmptyDrop>(this, [this](Ld::EmptyDrop *obj){
        connect(this, &QQuickItem::heightChanged, obj,
                [this, obj](){obj->setHeight(this->height());});
        obj->setSize({width(), height()});
        obj->setDropValidator(new DropDeleter(obj));
    });
    FactoryLd::create<ImitatorLd>(this, [this](ImitatorLd *obj){
        obj->setType(Ld::Type::Contact);
        obj->setSize({64, 64});
        obj->setY(0);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
    });
    FactoryLd::create<ImitatorLd>(this, [this](ImitatorLd *obj){
        obj->setType(Ld::Type::Coil);
        obj->setSize({64, 64});
        obj->setY(64);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
    });
    FactoryLd::create<ImitatorLd>(this, [this](ImitatorLd *obj){
        obj->setType(Ld::Type::Timer);
        obj->setSize({64, 64});
        obj->setY(64*2);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
    });
    FactoryLd::create<ImitatorLd>(this, [this](ImitatorLd *obj){
        obj->setType(Ld::Type::Counter);
        obj->setSize({64, 64});
        obj->setY(64*3);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
    });
    FactoryLd::create<ImitatorLd>(this, [this](ImitatorLd *obj){
        obj->setType(Ld::Type::Weektimer);
        obj->setSize({64, 64});
        obj->setY(64*4);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
    });
    FactoryLd::create<ImitatorLd>(this, [this](ImitatorLd *obj){
        obj->setType(Ld::Type::Text);
        obj->setSize({64, 64});
        obj->setY(64*5);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
    });
}



} // namespace Ld
