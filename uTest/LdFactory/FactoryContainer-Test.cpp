#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>
#include "factoryContainer.hpp"
#include "factory.hpp"

using namespace testing;

class MockFactoryContainer : public Ld::FactoryContainer
{
public:
    MOCK_METHOD0(changed, void());
protected:
    void changedFactory(){changed();}
};

TEST(LD_FactoryContainer, constructor)
{
    Ld::FactoryContainer factoryContainer;
}

TEST(LD_FactoryContainer, set)
{
    Ld::Factory factory;
    Ld::FactoryContainer factoryContainer;

    EXPECT_FALSE(factoryContainer.getFactory());

    factoryContainer.setFactory(&factory);
    EXPECT_TRUE(factoryContainer.getFactory() == &factory);
}


TEST(LD_FactoryContainer, changedFactory)
{
    MockFactoryContainer factoryContainer;

    EXPECT_CALL(factoryContainer, changed()).Times(1);
    factoryContainer.setFactory(nullptr);
}
