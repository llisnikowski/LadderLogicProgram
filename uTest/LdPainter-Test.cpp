#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <QDebug>
#include <QPainter>
#include <QPen>
#include "../LibComponentLd/ldPainter.hpp"


using namespace testing;

TEST(LdPaineter, SizeTest)
{
    Ld::LdPainter painter{241.23, 2.354};

    EXPECT_FLOAT_EQ(painter.getCellSize(), 241.23);
    EXPECT_FLOAT_EQ(painter.getPenSize(), 2.354);
}


