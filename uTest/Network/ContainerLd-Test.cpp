#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "line.hpp"
#include "containerLd.hpp"

using namespace testing;



class MockIteratorTester{
public:
    MOCK_METHOD3(fun, void(int line, int x, Ld::Base* obj));
};

TEST(ContainterLd, constructor)
{
    ContainerLd container;

    const ContainerLd::Array & array = container.getArray();
    ASSERT_EQ(array.count(), 1);

    EXPECT_EQ(array[0].count(), 1);

    EXPECT_TRUE(qobject_cast<const Ld::Line*>(container.getItem(0, 0)));
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








