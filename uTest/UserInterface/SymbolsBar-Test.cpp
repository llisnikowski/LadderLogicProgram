#include <gtest/gtest.h>

#include "contact.hpp"
#include "factoryLd.hpp"
#include "qobject.h"
#include "symbolsBar.hpp"
#include "contact.hpp"
#include "coil.hpp"


using namespace testing;


TEST(LD_SymbolsBar, SetNewParentItem)
{
    Ld::SymbolsBar symbolsBar;
    QQuickItem parentItem;

    symbolsBar.setNewParentItem(&parentItem);
    auto contact = symbolsBar.findChild<Ld::Contact *>();
    auto coil = symbolsBar.findChild<Ld::Coil *>();
    EXPECT_TRUE(contact);
    EXPECT_TRUE(coil);
}
