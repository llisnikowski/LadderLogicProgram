#include <gtest/gtest.h>

#include "dropNetworkValidator.hpp"
#include <QPoint>
#include <QIODevice>
#include <QDebug>

using namespace testing;

TEST(DrogNetworkData, constructor)
{
    DropNetworkValidator dragData1;
    EXPECT_FALSE(dragData1.parent());
    QObject parent;
    DropNetworkValidator dragData2{&parent};
    EXPECT_TRUE(dragData2.parent() == &parent);
}

TEST(DrogNetworkData, setData)
{

}

TEST(DrogNetworkData, setGetContainerLd)
{
    ContainerLd containerLd;
    DropNetworkValidator dragData;
    dragData.setContainer(&containerLd);
    EXPECT_TRUE(dragData.getContainer() == &containerLd);
}

TEST(DrogNetworkData, setGetPosition)
{
    DropNetworkValidator dragData;
    dragData.setPosition({7, 99});
    EXPECT_EQ(dragData.getPosition().line, 7);
    EXPECT_EQ(dragData.getPosition().x, 99);
}





















