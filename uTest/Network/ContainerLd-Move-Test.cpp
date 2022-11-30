#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "coil.hpp"
#include "contact.hpp"
#include "containerLd.hpp"
#include "factory.hpp"


class ContainterLd_Move : public ::testing::Test
{
protected:

    static ContainerLd container_;
    static Ld::Factory factory_;
};

ContainerLd ContainterLd_Move::container_;
Ld::Factory ContainterLd_Move::factory_;


TEST_F(ContainterLd_Move, moveOneObject)
{
    container_.setFactory(&factory_);
    Ld::Contact contact;
    container_.add(&contact, 0, 0);

    EXPECT_TRUE(container_.getSchemat() == "-I-;-;");

    EXPECT_TRUE(container_.move(0, 1, 1, 0));

    EXPECT_TRUE(container_.getSchemat() == "-I-;-;");

    Ld::Coil coil;
    container_.add(&coil, 0, 3);

    EXPECT_TRUE(container_.move(0, 1, 1, 0));
    EXPECT_TRUE(container_.getSchemat() == "-I-O-;-;");
}

TEST_F(ContainterLd_Move, movefirstLineInRigthWithoutNode)
{
    Ld::Contact contact;

    container_.add(&contact, 0, 3);
    container_.add(&contact, 0, 5);


    EXPECT_TRUE(container_.getSchemat() == "-I-I-I-O-;-;");

    auto item1 = container_.getItem(0, 1);
    auto item2 = container_.getItem(0, 3);
    auto item3 = container_.getItem(0, 5);

    EXPECT_TRUE(container_.move(0, 1, 0, 6));
    EXPECT_TRUE(container_.getSchemat() == "-I-I-I-O-;-;");
    EXPECT_EQ(container_.getItem(0, 1), item2);
    EXPECT_EQ(container_.getItem(0, 3), item3);
    EXPECT_EQ(container_.getItem(0, 5), item1);
}

TEST_F(ContainterLd_Move, movefirstLineInLeftWithoutNode)
{
    auto item1 = container_.getItem(0, 1);
    auto item2 = container_.getItem(0, 3);
    auto item3 = container_.getItem(0, 5);

    container_.move(0, 5, 0, 1);

    EXPECT_TRUE(container_.getSchemat() == "-I-I-I-O-;-;");
    EXPECT_EQ(container_.getItem(0, 1), item3);
    EXPECT_EQ(container_.getItem(0, 3), item1);
    EXPECT_EQ(container_.getItem(0, 5), item2);
}

TEST_F(ContainterLd_Move, moveDown)
{
    auto item1 = container_.getItem(0, 1);
    auto item2 = container_.getItem(0, 3);
    auto item3 = container_.getItem(0, 5);

    container_.move(0, 3, 1, 0);

    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
    EXPECT_EQ(container_.getItem(0, 1), item1);
    EXPECT_EQ(container_.getItem(0, 5), item3);
    EXPECT_EQ(container_.getItem(1, 1), item2);

    container_.move(0, 5, 2, 0);

    EXPECT_TRUE(container_.getSchemat() == "-I-+-O-;-I-+;-I-+;");
    EXPECT_EQ(container_.getItem(0, 1), item1);
    EXPECT_EQ(container_.getItem(1, 1), item2);
    EXPECT_EQ(container_.getItem(2, 1), item3);
}

TEST_F(ContainterLd_Move, moveUp)
{
    auto item1 = container_.getItem(0, 1);
    auto item2 = container_.getItem(1, 1);
    auto item3 = container_.getItem(2, 1);

    container_.move(1, 1, 0, 4);

    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
    EXPECT_EQ(container_.getItem(0, 1), item1);
    EXPECT_EQ(container_.getItem(0, 5), item2);
    EXPECT_EQ(container_.getItem(1, 1), item3);
}

TEST_F(ContainterLd_Move, moveBehindNode)
{
    auto item1 = container_.getItem(0, 1);
    auto item2 = container_.getItem(0, 5);
    auto item3 = container_.getItem(1, 1);

    container_.move(0, 1, 0, 4);

    EXPECT_TRUE(container_.getSchemat() == "-I-I-I-O-;-;");
    EXPECT_EQ(container_.getItem(0, 1), item3);
    EXPECT_EQ(container_.getItem(0, 3), item1);
    EXPECT_EQ(container_.getItem(0, 5), item2);
}

TEST_F(ContainterLd_Move, slideDown)
{
    auto item1 = container_.getItem(0, 1);
    auto item2 = container_.getItem(0, 3);
    auto item3 = container_.getItem(0, 5);

    container_.move(0, 1, 1, 1);

    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
    EXPECT_EQ(container_.getItem(0, 1), item2);
    EXPECT_EQ(container_.getItem(0, 5), item3);
    EXPECT_EQ(container_.getItem(1, 1), item1);
}

TEST_F(ContainterLd_Move, moveAfterNode)
{
    auto item1 = container_.getItem(0, 1);
    auto item2 = container_.getItem(0, 5);
    auto item3 = container_.getItem(1, 1);

    container_.move(1, 1, 0, 4);

    EXPECT_TRUE(container_.getSchemat() == "-I-I-I-O-;-;");
    EXPECT_EQ(container_.getItem(0, 1), item1);
    EXPECT_EQ(container_.getItem(0, 3), item3);
    EXPECT_EQ(container_.getItem(0, 5), item2);

    container_.move(0, 5, 1, 0);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
}

TEST_F(ContainterLd_Move, moveNextTo)
{
    auto item1 = container_.getItem(0, 1);
    auto item2 = container_.getItem(0, 3);
    auto item3 = container_.getItem(0, 5);

    EXPECT_TRUE(container_.move(0, 1, 0, 1));

    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
    EXPECT_EQ(container_.getItem(0, 1), item1);
    EXPECT_EQ(container_.getItem(0, 3), item2);
    EXPECT_EQ(container_.getItem(0, 5), item3);

    EXPECT_TRUE(container_.move(0, 1, 0, 0));

    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
    EXPECT_EQ(container_.getItem(0, 1), item1);
    EXPECT_EQ(container_.getItem(0, 3), item2);
    EXPECT_EQ(container_.getItem(0, 5), item3);

    EXPECT_TRUE(container_.move(0, 1, 0, 2));

    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
    EXPECT_EQ(container_.getItem(0, 1), item1);
    EXPECT_EQ(container_.getItem(0, 3), item2);
    EXPECT_EQ(container_.getItem(0, 5), item3);

    EXPECT_TRUE(container_.move(0, 7, 0, 7));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");

    EXPECT_TRUE(container_.move(0, 7, 0, 8));
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");


    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
}

TEST_F(ContainterLd_Move, moveOutOfScope)
{
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
    EXPECT_FALSE(container_.move(0, 1, 0, -1));
    EXPECT_FALSE(container_.move(0, 1, 0, 20));
    EXPECT_FALSE(container_.move(0, 7, 0, 20));
    EXPECT_FALSE(container_.move(0, 1, 4, 1));
    EXPECT_FALSE(container_.move(0, 1, 1, 5));
    EXPECT_FALSE(container_.move(0, 12, 0, 5));
    EXPECT_FALSE(container_.move(4, 1, 0, 5));
    EXPECT_FALSE(container_.move(1, 7, 0, 5));
    EXPECT_FALSE(container_.move(1, 4, 0, 5));
}

TEST_F(ContainterLd_Move, failMove)
{
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-O-;-I-+;-;");
    EXPECT_FALSE(container_.move(0, 1, 1, 1));
    EXPECT_FALSE(container_.move(0, 1, 1, 3));
    EXPECT_FALSE(container_.move(0, 1, 1, 4));
    EXPECT_FALSE(container_.move(0, 7, 2, 1));
    EXPECT_FALSE(container_.move(1, 1, 0, 8));
    EXPECT_FALSE(container_.move(0, 5, 0, 8));
    EXPECT_FALSE(container_.move(0, 5, 0, 0));
    EXPECT_FALSE(container_.move(0, 5, 0, 1));
    EXPECT_FALSE(container_.move(0, 5, 0, 2));
    EXPECT_FALSE(container_.move(0, 7, 0, 0));
    EXPECT_FALSE(container_.move(0, 7, 0, 1));
    EXPECT_FALSE(container_.move(0, 7, 0, 2));
    EXPECT_FALSE(container_.move(1, 1, 0, 1));
    EXPECT_FALSE(container_.move(1, 1, 0, 3));

    Ld::Contact contact;
    container_.add(&contact, 0, 5);
    EXPECT_TRUE(container_.getSchemat() == "-I-+-I-I-O-;-I-+;-;");
    EXPECT_FALSE(container_.move(1, 1, 0, 5));
    EXPECT_FALSE(container_.move(1, 1, 0, 7));
    EXPECT_FALSE(container_.move(1, 1, 0, 9));
}










