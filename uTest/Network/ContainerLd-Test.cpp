#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "line.hpp"
#include "containerLd.hpp"

using namespace testing;

TEST(ContainterLd, constructor)
{
    ContainerLd container;

    const ContainerLd::Array & array = container.getArray();

    EXPECT_EQ(array.count(), 3);
    EXPECT_EQ(array[0].count(), INPUTS_IN_LINE_1 * NUMBERS_OBJECTS_PER_INPUT
                            + OUTPUTS_IN_LINE_1 * NUMBERS_OBJECTS_PER_OUTPUT);
    EXPECT_EQ(array[1].count(), INPUTS_IN_LINE_2 * NUMBERS_OBJECTS_PER_INPUT);
    EXPECT_EQ(array[2].count(), INPUTS_IN_LINE_3 * NUMBERS_OBJECTS_PER_INPUT);


}

TEST(ContainterLd, empty)
{
    ContainerLd container;

    EXPECT_TRUE(qobject_cast<Ld::Line*>(container.getItem(0, 0)));
    EXPECT_FALSE(container.getItem(1, 0));
    EXPECT_FALSE(container.getItem(0, 1));
    EXPECT_FALSE(container.getItem(1, 1));
    EXPECT_FALSE(container.getItem(3, 0));
    EXPECT_FALSE(container.getItem(0, 20));
}
