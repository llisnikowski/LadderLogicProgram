#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <memory>

#include "componentLd.hpp"
#include <QPainter>
#include "ldPainter.hpp"

using namespace testing;

class MockComponentLd : public Ld::ComponentLd
{
public:
protected:
    MOCK_METHOD1(paint, void(QPainter *painter));
};


TEST(ComponentLd, setPainter)
{
    auto compLd = std::make_shared<MockComponentLd>();
    Ld::LdPainter ldPainter(1, 1);

    EXPECT_TRUE(compLd->getLdPainter() == nullptr);

    // TODO EXPECT_CALL(*compLd, paint(_));
    compLd->setLdPainter(&ldPainter);

    EXPECT_TRUE(compLd->getLdPainter() == &ldPainter);
}
