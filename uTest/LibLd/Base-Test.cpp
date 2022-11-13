#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
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
    Ld::Painter ldPainter(1, 1);

    EXPECT_TRUE(base->getLdPainter() == nullptr);

    // TODO EXPECT_CALL(*compLd, paint(_));
    base->setLdPainter(&ldPainter);

    EXPECT_TRUE(base->getLdPainter() == &ldPainter);
}
