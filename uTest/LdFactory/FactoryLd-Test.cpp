#include "factoryLd.hpp"
#include <gtest/gtest.h>
#include "line.hpp"
#include "contact.hpp"
#include <QSizeF>

using namespace testing;




TEST(LD_Factory, create)
{
    QQuickItem parent;
    auto line = FactoryLd::create<Ld::Line>(&parent);

    EXPECT_TRUE(line->parent() == &parent);
    EXPECT_TRUE(line->parentItem() == &parent);
    EXPECT_FLOAT_EQ(line->width(), 0);
    EXPECT_FLOAT_EQ(line->height(), 0);
    EXPECT_FLOAT_EQ(line->x(), 0);
    EXPECT_FLOAT_EQ(line->y(), 0);
}

TEST(LD_Factory, createWithLambda)
{
    QQuickItem parent;
    auto contact = FactoryLd::create<Ld::Contact>(&parent,[](Ld::Contact *obj){
        obj->setSize({33.8, 25.6});
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


