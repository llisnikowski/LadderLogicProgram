#include <gtest/gtest.h>

#include "imitatorLd.hpp"
#include "qobject.h"
#include "symbolsBar.hpp"


using namespace testing;


TEST(LD_SymbolsBar, SetNewParentItem)
{
    Ld::SymbolsBar symbolsBar;
    QQuickItem parentItem;

    symbolsBar.setNewParentItem(&parentItem);
//    auto child = symbolsBar.findChildren<ImitatorLd>();
//    EXPECT_TRUE(child.count() == 7);
}
