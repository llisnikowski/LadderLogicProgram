#include <gtest/gtest.h>

#include "network.hpp"

using namespace testing;

TEST(Network, getNr)
{
    Network network;
    EXPECT_EQ(network.getNr(), 0);

    Network network2{7};
    EXPECT_EQ(network2.getNr(), 7);

    Network network3{nullptr, 19};
    EXPECT_EQ(network3.getNr(), 19);
}


