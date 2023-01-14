#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "coil.hpp"
#include "contact.hpp"
#include "containerLd.hpp"


class ContainterLd_Remove : public ::testing::Test
{
protected:

    static ContainerLd container_;
};

ContainerLd ContainterLd_Remove::container_;

TEST_F(ContainterLd_Remove, init)
{
    Ld::Contact contact;
    Ld::Coil coil;

    container_.add(&contact, {0, 0});
    container_.add(&contact, {0, 0});
    container_.add(&contact, {0, 3});
    container_.add(&contact, {1, 0});
    container_.add(&contact, {2, 0});
    container_.add(&coil, {0, 8});

    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-I-O-;-I-+;-I-+;");
}

TEST_F(ContainterLd_Remove, removeOutOfScope)
{
    EXPECT_FALSE(container_.remove({0, 15}));
    EXPECT_FALSE(container_.remove({3, 0}));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-I-O-;-I-+;-I-+;");
}

TEST_F(ContainterLd_Remove, removeLineAndNode)
{
    EXPECT_FALSE(container_.remove({0, 3}));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-I-O-;-I-+;-I-+;");
}

TEST_F(ContainterLd_Remove, removeContact)
{
    EXPECT_TRUE(container_.remove({0, 5}));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-I-+;");
}

TEST_F(ContainterLd_Remove, removeCoil)
{
    EXPECT_TRUE(container_.remove({0, 7}));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-;-I-+;-I-+;");
}

TEST_F(ContainterLd_Remove, removeThridLine)
{
    EXPECT_TRUE(container_.remove({2, 1}));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-;-I-+;-;");
}

TEST_F(ContainterLd_Remove, removeSecondLine)
{
    EXPECT_TRUE(container_.remove({1, 1}));
    EXPECT_TRUE(container_.getSchemat() == "-I-I-;-;");
}

TEST_F(ContainterLd_Remove, shiftUp)
{
    Ld::Contact contact;
    container_.add(&contact, {1, 1});
    container_.add(&contact, {2, 1});
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-;-I-+;-I-+;");

    EXPECT_TRUE(container_.remove({1, 1}));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-;-I-+;-;");

    EXPECT_TRUE(container_.remove({0, 1}));
    EXPECT_TRUE(container_.getSchemat() == "-I-I-;-;");
}

TEST_F(ContainterLd_Remove, doubleShiftUp)
{
    Ld::Contact contact;
    container_.add(&contact, {1, 1});
    container_.add(&contact, {2, 1});
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-;-I-+;-I-+;");


    EXPECT_TRUE(container_.remove({0, 1}));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-;-I-+;-;");
}

TEST_F(ContainterLd_Remove, onlyOr)
{
    EXPECT_TRUE(container_.remove({0, 5}));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-;-I-+;-;");
}

TEST_F(ContainterLd_Remove, singleContact)
{
    EXPECT_TRUE(container_.remove({0, 1}));
    EXPECT_TRUE(container_.getSchemat() == "-I-;-;");
}

TEST_F(ContainterLd_Remove, singleCoil)
{
    Ld::Coil coil;
    container_.add(&coil, {0, 2});

    EXPECT_TRUE(container_.getSchemat() == "-I-O-;-;");

    EXPECT_TRUE(container_.remove({0, 1}));
    EXPECT_TRUE(container_.getSchemat() == "-O-;");
}

TEST_F(ContainterLd_Remove, removeLastObject)
{
    EXPECT_TRUE(container_.remove({0, 1}));
    EXPECT_TRUE(container_.getSchemat() == "-;");
}













