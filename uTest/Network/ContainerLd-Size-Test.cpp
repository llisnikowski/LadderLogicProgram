#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "coil.hpp"
#include "contact.hpp"
#include "containerLd.hpp"


class ContainterLd_Size : public ::testing::Test
{

protected:
    ContainerLd container_;
};


bool testSizeAndPos(QQuickItem * obj, qreal x,  qreal y,  qreal w,  qreal h){
    if(!obj){
        qDebug() << "empty pointer QQuickItem";
        return false;
    }
    if(obj->x() != x) {
        qDebug() << "x: " <<  obj->x() << " != " << x;
        return false;
    }
    if(obj->y() != y) {
        qDebug() << "y: " <<  obj->y() << " != " << y;
        return false;
    }
    if(obj->width() != w) {
        qDebug() << "w: " <<  obj->width() << " != " << w;
        return false;
    }
    if(obj->height() != h) {
        qDebug() << "h: " <<  obj->height() << " != " << h;
        return false;
    }
    return true;
}

bool testSize(QQuickItem * obj, qreal w,  qreal h){
    if(!obj){
        qDebug() << "empty pointer QQuickItem";
        return false;
    }
    if(obj->width() != w) {
        qDebug() << "w: " <<  obj->width() << " != " << w;
        return false;
    }
    if(obj->height() != h) {
        qDebug() << "h: " <<  obj->height() << " != " << h;
        return false;
    }
    return true;
}

TEST_F(ContainterLd_Size, init)
{
    EXPECT_TRUE(container_.getSchemat() == "-;");
    EXPECT_EQ(1 ,1);
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 0), 0, 0,
                         MAX_LENGTH_LINE, LD_H));
}

TEST_F(ContainterLd_Size, onlyContact)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 0);

    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 0), 0, 0, LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 1), LD_W, 0, LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 2), LD_W* 2, 0,
                         MAX_LENGTH_LINE - 2 * LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(1, 0), 0, LD_H,
                         MAX_LENGTH_LINE, LD_H));
}

TEST_F(ContainterLd_Size, onlyCoil)
{
    Ld::Coil coil;
    container_.add(&coil, 0, 0);

    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 0), 0, 0,
                               MAX_LENGTH_LINE - 2 * LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 1),
                               MAX_LENGTH_LINE - 2 * LD_W, 0, LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 2),
                               MAX_LENGTH_LINE - LD_W, 0, LD_W, LD_H));
}

TEST_F(ContainterLd_Size, contactAndCoil)
{
    Ld::Contact contact;
    Ld::Coil coil;
    container_.add(&contact, 0, 0);
    container_.add(&contact, 0, 0);
    container_.add(&coil, 0, 5);

    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 0),
                               0, 0, LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 1),
                               LD_W, 0, LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 2),
                               2 * LD_W, 0, LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 3),
                               3 * LD_W, 0, LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 4),
                               4 * LD_W, 0, MAX_LENGTH_LINE - 6 * LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 5),
                               MAX_LENGTH_LINE - 2 * LD_W, 0, LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(0, 6),
                               MAX_LENGTH_LINE - LD_W, 0, LD_W, LD_H));
    EXPECT_TRUE(testSizeAndPos(container_.getItem(1, 0),
                               0, LD_H, MAX_LENGTH_LINE, LD_H));
}

TEST_F(ContainterLd_Size, node)
{
    Ld::Contact contact;
    Ld::Coil coil;
    container_.add(&contact, 0, 0);
    container_.add(&contact, 0, 0);
    container_.add(&contact, 1, 0);
    container_.add(&coil, 0, 7);

    EXPECT_TRUE(testSize(container_.getItem(0, 0), LD_W, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(0, 1), LD_W, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(0, 2), LINE_BESIDE_NODE, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(0, 3), NODE_W, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(0, 4), LINE_BESIDE_NODE, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(0, 5), LD_W, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(0, 6),
                         MAX_LENGTH_LINE
                             - 5 * LD_W
                             - 2 * LINE_BESIDE_NODE
                             -  NODE_W,
                         LD_H));
    EXPECT_TRUE(testSize(container_.getItem(0, 7), LD_W, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(0, 8), LD_W, LD_H));

    EXPECT_TRUE(testSize(container_.getItem(1, 0), LD_W, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(1, 1), LD_W, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(1, 2), LINE_BESIDE_NODE, LD_H));
    EXPECT_TRUE(testSize(container_.getItem(1, 3), NODE_W, LD_H));

    EXPECT_TRUE(testSize(container_.getItem(2, 0),
                         2 * LD_W + LINE_BESIDE_NODE + NODE_W, LD_H));
}
