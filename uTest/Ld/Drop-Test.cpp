#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "drop.hpp"
#include "dragData.hpp"
#include "dropValidator.hpp"
#include "line.hpp"
#include "qquickitem.h"

using namespace testing;

class MockDragAndDropData : public Ld::DragData
{
public:
    MOCK_CONST_METHOD0(getData, QByteArray ());
    MOCK_METHOD1(setData, bool(const QByteArray &data));
};

class MockDropValidator : public Ld::DropValidator
{
public:
    MOCK_METHOD1(valid, Qt::DropAction(const QByteArray &dragArrayData));
    MOCK_METHOD1(doAction, void(const QByteArray & dropData));
};


TEST(LD_Drop, parent)
{
    Ld::Drop * drop = new Ld::Line{};
    EXPECT_FALSE(drop->parentItem());
    delete drop;

    drop = new Ld::Line{nullptr};
    EXPECT_FALSE(drop->parentItem());
    delete drop;

    QQuickItem parent;
    drop = new Ld::Line{&parent};
    EXPECT_TRUE(drop->parentItem() == &parent);
    delete drop;
}

TEST(LD_Drop, dragEnterEvent)
{
}
