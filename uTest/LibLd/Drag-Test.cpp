#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "drag.hpp"
#include <QPainter>
//#include "painter.hpp"

using namespace testing;

class MockDrag : public Ld::Drag
{
public:
    MOCK_METHOD1(paint, void(QPainter *painter));
};


TEST(LD_Drag, setPainter)
{
}
