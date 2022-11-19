#include <gtest/gtest.h>

#include <QDebug>
#include <QPainter>
#include <QPen>
#include "painter.hpp"


using namespace testing;

TEST(LD_Paineter, SizeTest)
{
    Ld::Painter painter{2.354};

    EXPECT_FLOAT_EQ(painter.getPenSize(), 2.354);
}


