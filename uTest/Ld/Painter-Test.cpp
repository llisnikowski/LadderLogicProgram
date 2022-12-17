#include <gtest/gtest.h>

#include <QDebug>
#include <QPainter>
#include <QPen>
#include "painterLd.hpp"


using namespace testing;

TEST(LD_Paineter, SizeTest)
{
    Ld::PainterLd painter{nullptr, {2.354, 12}};
}


