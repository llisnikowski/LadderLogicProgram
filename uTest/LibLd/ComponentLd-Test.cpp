#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <memory>

#include "base.hpp"
#include <QPainter>
#include "painter.hpp"

using namespace testing;

class MockComponentLd : public Ld::Base
{
public:
protected:
    MOCK_METHOD1(paint, void(QPainter *painter));
};


TEST(ComponentLd, setPainter)
{
    auto compLd = std::make_shared<MockComponentLd>();
    Ld::Painter ldPainter(1, 1);

    EXPECT_TRUE(compLd->getLdPainter() == nullptr);

    // TODO EXPECT_CALL(*compLd, paint(_));
    compLd->setLdPainter(&ldPainter);

    EXPECT_TRUE(compLd->getLdPainter() == &ldPainter);
}
