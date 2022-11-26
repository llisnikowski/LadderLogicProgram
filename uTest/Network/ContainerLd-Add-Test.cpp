#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "coil.hpp"
#include "contact.hpp"
#include "containerLd.hpp"
#include "factory.hpp"


class ContainterLd_Add : public ::testing::Test
{
protected:

    static ContainerLd container_;
    static Ld::Factory factory_;
};

ContainerLd ContainterLd_Add::container_;
Ld::Factory ContainterLd_Add::factory_;


TEST_F(ContainterLd_Add, empty)
{
    container_.setFactory(&factory_);
    EXPECT_TRUE(container_.getSchemat(true) == "-;");
}

TEST_F(ContainterLd_Add, AddNull)
{
    container_.add(nullptr, 0, 0);
    EXPECT_TRUE(container_.getSchemat() == "-;");
}

TEST_F(ContainterLd_Add, AddOutOfScope)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 15);
    EXPECT_TRUE(container_.getSchemat() == "-;");

    container_.add(&contact, 4, 0);
    EXPECT_TRUE(container_.getSchemat() == "-;");
}

TEST_F(ContainterLd_Add, AddNotInOrder)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 4);
    EXPECT_TRUE(container_.getSchemat() == "-;");

    container_.add(&contact, 1, 0);
    EXPECT_TRUE(container_.getSchemat() == "-;");

    container_.add(&contact, 1, 1);
    EXPECT_TRUE(container_.getSchemat() == "-;");
}

TEST_F(ContainterLd_Add, AddOnLine)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 0);
    ASSERT_TRUE(container_.getSchemat() == "-I-;-;");
}

TEST_F(ContainterLd_Add, OnlyOr)
{
    Ld::Contact contact;
    container_.add(&contact, 1, 0);
    EXPECT_TRUE(container_.getSchemat(true) == "-I-+-;-I-+;-;");

    container_.remove(1, 1);
    ASSERT_TRUE(container_.getSchemat() == "-I-;-;");
}

TEST_F(ContainterLd_Add, AddNextToTheLine)
{
    Ld::Coil coil;
    container_.add(&coil, 0, 3);
    EXPECT_TRUE(container_.getSchemat(true) == "-I-O-;-;");
}

TEST_F(ContainterLd_Add, AddWithShift)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 1);
    EXPECT_TRUE(container_.getSchemat() == "-I-I-O-;-;");
}

TEST_F(ContainterLd_Add, AddToSecondLine)
{
    Ld::Contact contact;
    container_.add(&contact, 1, 1);
    EXPECT_TRUE(container_.getSchemat(true) == "-I-+-I-O-;-I-+;-;");
}


TEST_F(ContainterLd_Add, InsertFail)
{
    Ld::Contact contact;
    Ld::Coil coil;
    EXPECT_FALSE(container_.add(&contact, 0, 0));
    EXPECT_FALSE(container_.add(&contact, 0, 1));
    EXPECT_FALSE(container_.add(&contact, 0, 2));
    EXPECT_FALSE(container_.add(&contact, 0, 3));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");

    container_.add(&contact, 0, 10);
    container_.add(&contact, 0, 15);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");

    container_.add(&coil, 0, 4);
    container_.add(&coil, 0, 9);
    container_.add(&coil, 0, 10);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");

    container_.add(&contact, 1, 0);
    container_.add(&contact, 1, 1);
    container_.add(&contact, 1, 2);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");

    container_.add(&coil, 2, 1);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
}

TEST_F(ContainterLd_Add, AddToThridLine)
{
    Ld::Contact contact;
    container_.add(&contact, 2, 1);
    EXPECT_TRUE(container_.getSchemat(true) == "-I-+-I-O-;-I-+;-I-+;");
}

TEST_F(ContainterLd_Add, AddLastObject)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 6);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-I-O-;-I-+;-I-+;");
}












