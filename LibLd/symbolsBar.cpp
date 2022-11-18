/*!
 * \file symbolsBar.cpp
 * \author Łukasz Liśnikowski
*/
#include "symbolsBar.hpp"
#include "contact.hpp"
#include "coil.hpp"
#include "factory.hpp"
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

    if(!factory_) return;
    factory_->createContact(this);
    auto coil = factory_->createCoil(this);
    coil->setY(factory_->getObjectSize());
}

void SymbolsBar::changedFactory()
{
    update();
}


} // namespace Ld
