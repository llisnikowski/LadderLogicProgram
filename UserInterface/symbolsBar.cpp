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

    int i{};
    for(auto type : {Ld::Type::Contact, Ld::Type::Coil, Ld::Type::Timer,
                      Ld::Type::Counter, Ld::Type::Weektimer, Ld::Type::Text})
    {
        FactoryLd::create<ImitatorLd>(this, [type, &i](ImitatorLd *obj){
            obj->setType(type);
            obj->setSize({64, 64});
            obj->setY(64 * i++);
            obj->setDragData(new DragNetworkData(obj, obj->getData(), -1, {}));
        });
    }

}



} // namespace Ld
