#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "contact.hpp"
#include "factory.hpp"
#include "painter.hpp"
#include "qobject.h"
#include "symbolsBar.hpp"
#include "contact.hpp"
#include "coil.hpp"


using namespace testing;

TEST(LD_SymbolsBar, SetLdPainter)
{
    Ld::SymbolsBar symbolsBar;
    Ld::Factory factory;

    EXPECT_TRUE(symbolsBar.getFactory() == nullptr);

    symbolsBar.setFactory(&factory);

    EXPECT_TRUE(symbolsBar.getFactory() == &factory);
}


TEST(LD_SymbolsBar, SetNewParentItem_NoFactory)
{
    Ld::SymbolsBar symbolsBar;
    QQuickItem parentItem;

    EXPECT_EQ(symbolsBar.childItems().count(), 0);

    symbolsBar.setNewParentItem(nullptr);
    EXPECT_EQ(symbolsBar.childItems().count(), 0);

    symbolsBar.setNewParentItem(&parentItem);

    EXPECT_TRUE(symbolsBar.parentItem() == &parentItem);
    EXPECT_EQ(symbolsBar.childItems().count(), 0);
}

TEST(LD_SymbolsBar, SetNewParentItem_TestFactory_NullPainter)
{
    Ld::SymbolsBar symbolsBar;
    QQuickItem parentItem;
    Ld::Factory factory;
    symbolsBar.setFactory(&factory);

    symbolsBar.setNewParentItem(&parentItem);
    auto contact = symbolsBar.findChild<Ld::Contact *>();
    auto coil = symbolsBar.findChild<Ld::Coil *>();
    EXPECT_FALSE(contact->getPainter());
    EXPECT_FALSE(coil->getPainter());
}

TEST(LD_SymbolsBar, SetNewParentItem_TestFactory)
{
    Ld::SymbolsBar symbolsBar;
    QQuickItem parentItem;
    Ld::Painter painter{12,1};
    Ld::Factory factory;
    factory.setPainter(&painter);
    symbolsBar.setFactory(&factory);

    symbolsBar.setNewParentItem(&parentItem);
    auto contact = symbolsBar.findChild<Ld::Contact *>();
    auto coil = symbolsBar.findChild<Ld::Coil *>();
    EXPECT_TRUE(contact->getPainter() == &painter);
    EXPECT_TRUE(coil->getPainter() == &painter);
}
