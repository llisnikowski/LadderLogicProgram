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
#include "timer.hpp"
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
    FactoryLd::create<Ld::Contact>(this, [this](Ld::Contact *obj){
        obj->setSize({64, 64});
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
        obj->setVisibleProperties(false);
    });
    FactoryLd::create<Ld::Coil>(this, [this](Ld::Coil *obj){
        obj->setSize({64, 64});
        obj->setY(64);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
        obj->setVisibleProperties(false);
    });
    FactoryLd::create<Ld::Timer>(this, [this](Ld::Timer *obj){
        obj->setSize({64, 64});
        obj->setY(64 * 2);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
        obj->setVisibleProperties(false);
    });
    FactoryLd::create<Ld::Counter>(this, [this](Ld::Counter *obj){
        obj->setSize({64, 64});
        obj->setY(64 * 3);
        obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
        obj->setVisibleProperties(false);
    });
}



} // namespace Ld
