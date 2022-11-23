#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "line.hpp"
#include "containerLd.hpp"
#include "factory.hpp"

using namespace testing;



class MockIteratorTester{
public:
    MOCK_METHOD3(fun, void(int line, int x, Ld::Base* obj));
};

TEST(ContainterLd, constructor)
{
    ContainerLd container;

    const ContainerLd::Array & array = container.getArray();

    EXPECT_EQ(array.count(), 3);
    EXPECT_EQ(array[0].count(), QString("-I-+-I-I-O-").length());
    EXPECT_EQ(array[1].count(), QString("-I-+").length());
    EXPECT_EQ(array[2].count(), QString("-I-+").length());
}

TEST(ContainterLd, empty)
{
    ContainerLd container;

    EXPECT_FALSE(container.getItem(0, 0));
    EXPECT_FALSE(container.getItem(1, 0));
    EXPECT_FALSE(container.getItem(0, 1));
    EXPECT_FALSE(container.getItem(1, 1));
    EXPECT_FALSE(container.getItem(3, 0));
    EXPECT_FALSE(container.getItem(0, 20));
}

TEST(ContainterLd, setFactoryNullprt)
{
    ContainerLd container;
    container.setFactory(nullptr);

    EXPECT_FALSE(container.getItem(0, 0));
    EXPECT_FALSE(container.getItem(1, 0));
    EXPECT_FALSE(container.getItem(0, 1));
    EXPECT_FALSE(container.getItem(1, 1));
    EXPECT_FALSE(container.getItem(3, 0));
    EXPECT_FALSE(container.getItem(0, 20));
}

TEST(ContainterLd, setFactory)
{
    ContainerLd container;
    Ld::Factory factory;
    container.setFactory(&factory);

    EXPECT_TRUE(qobject_cast<Ld::Line*>(container.getItem(0, 0)));
    EXPECT_FALSE(container.getItem(1, 0));
    EXPECT_FALSE(container.getItem(0, 1));
    EXPECT_FALSE(container.getItem(1, 1));
    EXPECT_FALSE(container.getItem(3, 0));
    EXPECT_FALSE(container.getItem(0, 20));
}

TEST(ContainterLd, iterator)
{
//    ContainerLd container;

//    MockIteratorTester iteratorTester;

}








