#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "base.hpp"
#include "painter.hpp"
#include <QPainter>
#include <QQuickItem>

using namespace testing;

class MockBaseLd : public Ld::Base
{
public:
    MOCK_METHOD1(clone, Ld::Base *(QQuickItem*));
    MOCK_CONST_METHOD0(getData, QByteArray());
    MOCK_METHOD1(paint, void(QPainter *painter));
protected:
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
