#include "factoryLd.hpp"
#include <gtest/gtest.h>
#include "line.hpp"
#include "contact.hpp"
#include "painter.hpp"
#include <QSizeF>

using namespace testing;


TEST(LD_Factory, setPainter)
{
    Ld::Painter painter{1.2};
    FactoryLd::setPainter(&painter);
    EXPECT_TRUE(FactoryLd::getPainter() ==  &painter);
}



TEST(LD_Factory, create)
{
    Ld::Painter painter{1.8};
    FactoryLd::setPainter(&painter);
    QQuickItem parent;
    auto line = FactoryLd::create<Ld::Line>(&parent, {12, 7.5});

    EXPECT_TRUE(line->parent() == &parent);
    EXPECT_TRUE(line->parentItem() == &parent);
    EXPECT_FLOAT_EQ(line->width(), 12);
    EXPECT_FLOAT_EQ(line->height(), 7.5);
    EXPECT_FLOAT_EQ(line->x(), 0);
    EXPECT_FLOAT_EQ(line->y(), 0);
}

TEST(LD_Factory, createWithLambda)
{
    Ld::Painter painter{1.8};
    FactoryLd::setPainter(&painter);
    QQuickItem parent;
    auto contact = FactoryLd::create<Ld::Contact>(&parent,{33.8, 25.6}
                                               ,[](Ld::Contact *obj){
        obj->setX(10.2);
        obj->setY(15.5);
    });

    EXPECT_TRUE(contact->parent() == &parent);
    EXPECT_TRUE(contact->parentItem() == &parent);
    EXPECT_FLOAT_EQ(contact->width(), 33.8);
    EXPECT_FLOAT_EQ(contact->height(), 25.6);
    EXPECT_FLOAT_EQ(contact->x(), 10.2);
    EXPECT_FLOAT_EQ(contact->y(), 15.5);
}


