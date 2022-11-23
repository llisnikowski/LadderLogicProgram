#include <gtest/gtest.h>

#include "contact.hpp"
#include "dragNetworkData.hpp"
#include <QPoint>
#include <QIODevice>
#include "ldFunction.hpp"
#include "node.hpp"
#include <QDebug>

using namespace testing;

TEST(DragNetworkData, constructor)
{
    DragNetworkData dragData1;
    EXPECT_FALSE(dragData1.parent());
    QObject parent;
    DragNetworkData dragData2{&parent};
    EXPECT_TRUE(dragData2.parent() == &parent);
}

TEST(DragNetworkData, setData)
{
    DragNetworkData dragData;

    Ld::Contact contact;
    dragData.setLd(contact);
    dragData.setNetworkId(12);
    dragData.setPosition({7,5});

    QByteArray outputData = dragData.getData();
    QDataStream dataStream(&outputData, QIODevice::ReadOnly);
    QByteArray ldSymbol;
    int networkNr;
    QPoint point;
    dataStream >> ldSymbol >> networkNr >> point;

    EXPECT_TRUE(ldSymbol == contact.getData());
    ASSERT_EQ(networkNr, 12);
    EXPECT_EQ(point.x(), 7);
    EXPECT_EQ(point.y(), 5);

    DragNetworkData dragData2;
    dragData2.setData(outputData);
    EXPECT_TRUE(dragData2.getData() == dragData.getData());
}

TEST(DragNetworkData, setGetLd)
{
    DragNetworkData dragData;
    Ld::Node node;
    dragData.setLd(node);
    EXPECT_TRUE(dragData.getLd() == node.getData());
}

TEST(DragNetworkData, setGetNetworkId)
{
    DragNetworkData dragData;
    dragData.setNetworkId(25);
    EXPECT_EQ(dragData.getNetworkId(), 25);
}

TEST(DragNetworkData, setGetPosition)
{
    DragNetworkData dragData;
    dragData.setPosition({7, 99});
    EXPECT_EQ(dragData.getPosition().x(), 7);
    EXPECT_EQ(dragData.getPosition().y(), 99);
}





















