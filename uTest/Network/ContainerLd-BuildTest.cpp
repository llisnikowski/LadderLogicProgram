#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "coil.hpp"
#include "contact.hpp"
#include "containerLd.hpp"
#include "factory.hpp"


class ContainterLdBuild : public ::testing::Test
{
protected:

    static ContainerLd container_;
    static Ld::Factory factory_;
};

ContainerLd ContainterLdBuild::container_;
Ld::Factory ContainterLdBuild::factory_;


TEST_F(ContainterLdBuild, empty)
{
    container_.setFactory(&factory_);
    EXPECT_TRUE(container_.getSchemat() == "-;;;");
}

TEST_F(ContainterLdBuild, AddNull)
{
    container_.add(nullptr, 0, 0);
    EXPECT_TRUE(container_.getSchemat() == "-;;;");
}

TEST_F(ContainterLdBuild, AddOutOfScope)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 15);
    EXPECT_TRUE(container_.getSchemat() == "-;;;");

    container_.add(&contact, 4, 0);
    EXPECT_TRUE(container_.getSchemat() == "-;;;");
}

TEST_F(ContainterLdBuild, AddNotInOrder)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 4);
    EXPECT_TRUE(container_.getSchemat() == "-;;;");

    container_.add(&contact, 1, 0);
    EXPECT_TRUE(container_.getSchemat() == "-;;;");

    container_.add(&contact, 1, 1);
    EXPECT_TRUE(container_.getSchemat() == "-;;;");
}

TEST_F(ContainterLdBuild, AddOnLine)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 0);
    ASSERT_TRUE(container_.getSchemat() == "-I-;-;;");
}

TEST_F(ContainterLdBuild, AddNextToTheLine)
{
    Ld::Coil coil;
    container_.add(&coil, 0, 3);
    EXPECT_TRUE(container_.getSchemat() == "-I-O-;-;;");
}

TEST_F(ContainterLdBuild, AddWithShift)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 1);
    EXPECT_TRUE(container_.getSchemat() == "-I-I-O-;-;;");
}

TEST_F(ContainterLdBuild, AddToSecondLine)
{
    Ld::Contact contact;
    container_.add(&contact, 1, 1);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
}


TEST_F(ContainterLdBuild, InsertFail)
{
    Ld::Contact contact;
    Ld::Coil coil;
    container_.add(&contact, 0, 0);
    container_.add(&contact, 0, 1);
    container_.add(&contact, 0, 2);
    container_.add(&contact, 0, 3);
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

TEST_F(ContainterLdBuild, AddToThridLine)
{
    Ld::Contact contact;
    container_.add(&contact, 2, 1);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-I-+;");
}

TEST_F(ContainterLdBuild, AddLastObject)
{
    Ld::Contact contact;
    container_.add(&contact, 0, 6);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-I-O-;-I-+;-I-+;");
}












