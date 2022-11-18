#include <gtest/gtest.h>

#include "networkList.hpp"
#include "qquickitem.h"

using namespace testing;

TEST(NetworkList, parentItem)
{
    NetworkList networkList1;
    EXPECT_FALSE(networkList1.parentItem());

    QQuickItem parent;
    NetworkList networkList2(&parent);
    EXPECT_TRUE(networkList2.parentItem() == &parent);
    EXPECT_TRUE(networkList2.parent() == &parent);
}

TEST(NetworkList, setParentItem)
{
    QQuickItem parent;
    NetworkList networkList;

    EXPECT_EQ(networkList.childItems().count(), 0);
    networkList.joinToParent(&parent);
    EXPECT_EQ(networkList.childItems().count(), 1);
}
