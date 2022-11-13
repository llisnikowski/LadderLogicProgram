#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "contact.hpp"
#include "qobject.h"
#include "symbolsBar.hpp"
#include "painter.hpp"
#include "contact.hpp"
#include "coil.hpp"


using namespace testing;

TEST(LD_SymbolsBar, SetLdPainter)
{
    Ld::SymbolsBar symbolsBar;
    Ld::Painter ldPainter{1,1};

    EXPECT_TRUE(symbolsBar.getLdPainter() == nullptr);

    symbolsBar.setLdPainter(&ldPainter);

    EXPECT_TRUE(symbolsBar.getLdPainter() == &ldPainter);
}


TEST(LD_SymbolsBar, SetNewParentItem)
{
    Ld::SymbolsBar symbolsBar;
    QQuickItem parentItem;

    EXPECT_EQ(symbolsBar.childItems().count(), 0);

    symbolsBar.setNewParentItem(&parentItem);

    EXPECT_TRUE(symbolsBar.parentItem() == &parentItem);
    EXPECT_EQ(symbolsBar.childItems().count(), 2);
    EXPECT_TRUE(symbolsBar.findChild<Ld::Contact *>());
    EXPECT_TRUE(symbolsBar.findChild<Ld::Coil *>());
}
