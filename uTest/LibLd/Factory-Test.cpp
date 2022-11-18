#include "factory.hpp"
#include <gtest/gtest.h>
#include "line.hpp"
#include "contact.hpp"
#include "coil.hpp"
#include "painter.hpp"
#include <QSizeF>

using namespace testing;

TEST(LD_Factory, constructor)
{
    QObject parent;
    Ld::Factory factory{&parent};

    EXPECT_TRUE(factory.parent() == &parent);
}

TEST(LD_Factory, setObjectSize)
{
    Ld::Factory factory;
    factory.setObjectSize(12.3);
    EXPECT_FLOAT_EQ(factory.getObjectSize(), 12.3);
}

TEST(LD_Factory, setPainter)
{
    Ld::Painter painter{43.6, 1.2};
    Ld::Factory factory;
    factory.setPainter(&painter);
    EXPECT_FLOAT_EQ(factory.getObjectSize(), 43.6);
    EXPECT_TRUE(factory.getPainter() ==  &painter);
}



TEST(LD_Factory, createLine)
{
    Ld::Painter painter{33.6, 1.8};
    Ld::Factory factory;
    factory.setPainter(&painter);
    QQuickItem parent;
    auto line = factory.createLine(&parent);

    EXPECT_TRUE(line->parent() == &parent);
    EXPECT_TRUE(line->parentItem() == &parent);
    EXPECT_FLOAT_EQ(line->width(), 33.6);
    EXPECT_FLOAT_EQ(line->height(), 33.6);
}

TEST(LD_Factory, createContact)
{
    Ld::Painter painter{33.8, 1.8};
    Ld::Factory factory;
    factory.setPainter(&painter);
    QQuickItem parent;
    auto line = factory.createContact(&parent);

    EXPECT_TRUE(line->parent() == &parent);
    EXPECT_TRUE(line->parentItem() == &parent);
    EXPECT_FLOAT_EQ(line->width(), 33.8);
    EXPECT_FLOAT_EQ(line->height(), 33.8);
}

TEST(LD_Factory, createCoil)
{
    Ld::Painter painter{32.6, 1.8};
    Ld::Factory factory;
    factory.setPainter(&painter);
    QQuickItem parent;
    auto line = factory.createCoil(&parent);

    EXPECT_TRUE(line->parent() == &parent);
    EXPECT_TRUE(line->parentItem() == &parent);
    EXPECT_FLOAT_EQ(line->width(), 32.6);
    EXPECT_FLOAT_EQ(line->height(), 32.6);
}


