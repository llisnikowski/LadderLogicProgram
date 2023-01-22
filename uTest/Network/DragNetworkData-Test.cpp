#include <gtest/gtest.h>

#include "contact.hpp"
#include "containerLd.hpp"
#include "dragNetworkData.hpp"
#include <QIODevice>
#include "node.hpp"
#include <QDebug>
#include "position.hpp"

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
    dragData.setId(12);
    dragData.setPosition({7,5});

    QByteArray outputData = dragData.getData();
    QDataStream dataStream(&outputData, QIODevice::ReadOnly);
    QByteArray ldSymbol;
    int networkNr;
    Position position;
    dataStream >> ldSymbol >> networkNr >> position;

    EXPECT_TRUE(ldSymbol == contact.getData());
    ASSERT_EQ(networkNr, 12);
    EXPECT_EQ(position.line, 7);
    EXPECT_EQ(position.x, 5);

    DragNetworkData dragData2;
    EXPECT_TRUE(dragData2.setData(outputData));
    EXPECT_TRUE(dragData2.getData() == dragData.getData());
}

TEST(DragNetworkData, setGetLd)
{
    DragNetworkData dragData;
    Ld::Node node;
    dragData.setLd(node);
    EXPECT_TRUE(dragData.getLd() == node.getData());
}

TEST(DragNetworkData, setGetId)
{
    DragNetworkData dragData;
    dragData.setId(25);
    EXPECT_EQ(dragData.getId(), 25);
}

TEST(DragNetworkData, setGetContainerLd)
{
    ContainerLd container;
    DragNetworkData dragData;
    dragData.setContainer(&container);
    EXPECT_EQ(dragData.getId(), container.getId());
}

TEST(DragNetworkData, setGetPosition)
{
    DragNetworkData dragData;
    dragData.setPosition({7, 99});
    EXPECT_EQ(dragData.getPosition().line, 7);
    EXPECT_EQ(dragData.getPosition().x, 99);
}





















