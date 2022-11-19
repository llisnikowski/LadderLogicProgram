#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "base.hpp"
#include <QPainter>
#include "painter.hpp"

using namespace testing;

class MockBaseLd : public Ld::Base
{
public:
protected:
    MOCK_METHOD1(paint, void(QPainter *painter));
};


TEST(LD_Base, setPainter)
{
    auto base = std::make_shared<MockBaseLd>();
    Ld::Painter painter(1);

    EXPECT_TRUE(base->getPainter() == nullptr);

    // TODO EXPECT_CALL(*compLd, paint(_));
    base->setPainter(&painter);

    EXPECT_TRUE(base->getPainter() == &painter);
}
