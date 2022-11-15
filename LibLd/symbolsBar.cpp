/*!
 * \file symbolsBar.cpp
 * \author Łukasz Liśnikowski
*/
#include "symbolsBar.hpp"
#include "contact.hpp"
#include "coil.hpp"
#include <QDebug>

namespace Ld {

SymbolsBar::SymbolsBar()
    :ldPainter_{}
{

}


void SymbolsBar::setLdPainter(Painter *ldPainter)
{
    this->ldPainter_ = ldPainter;
    update();
}

Painter *SymbolsBar::getLdPainter()
{
    return ldPainter_;
}


void SymbolsBar::setNewParentItem(QQuickItem *parentItem)
{
    if(!parentItem) return;
    setWidth(parentItem->width());
    setHeight(parentItem->height());
    setParentItem(parentItem);

    auto contact = new Contact(this);
    contact->setWidth(64);
    contact->setHeight(64);
    contact->setPainter(ldPainter_);
    auto coil = new Coil(this);
    coil->setWidth(64);
    coil->setHeight(64);
    coil->setY(64);
    coil->setPainter(ldPainter_);
}


} // namespace Ld
