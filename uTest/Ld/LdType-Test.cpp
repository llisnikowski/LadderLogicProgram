#include <stdint.h>
#include <gtest/gtest.h>
#include <QVector>

#include "Ld/type.hpp"


using namespace testing;

struct TypeTestParameters {
    Ld::Type type;
    QVector<Ld::Type> trueType;
};

class TypeConditional : public ::testing::TestWithParam<TypeTestParameters> {

};

TEST_P(TypeConditional, comparisonOperator) {
    TypeTestParameters const& parameters = GetParam();
    for(Ld::Type testType :
         {Ld::Type::None, Ld::Type::Base, Ld::Type::Drop, Ld::Type::Drag,
          Ld::Type::Node, Ld::Type::Line, Ld::Type::Address, Ld::Type::Input, Ld::Type::Output,
          Ld::Type::Contact, Ld::Type::Coil, Ld::Type::Timer, Ld::Type::Counter,
          Ld::Type::Weektimer, Ld::Type::Text, Ld::Type::EmptyDrop}){
        EXPECT_TRUE((parameters.type >= testType)
                    == parameters.trueType.contains(testType));
        EXPECT_TRUE((parameters.type != testType)
                    != parameters.trueType.contains(testType));
    }

}

INSTANTIATE_TEST_SUITE_P(BasicTest, TypeConditional,
                        ::testing::Values
(
    TypeTestParameters{Ld::Type::None, {Ld::Type::None}},
    TypeTestParameters{Ld::Type::Base, {Ld::Type::None, Ld::Type::Base}},
    TypeTestParameters{Ld::Type::Node, {Ld::Type::None, Ld::Type::Base, Ld::Type::Node}},
    TypeTestParameters{Ld::Type::Drop, {Ld::Type::None, Ld::Type::Base, Ld::Type::Drop}},
    TypeTestParameters{Ld::Type::Drag, {Ld::Type::None, Ld::Type::Base, Ld::Type::Drag}},
    TypeTestParameters{Ld::Type::Line, {Ld::Type::None, Ld::Type::Base,
                                        Ld::Type::Drop, Ld::Type::Line}},
    TypeTestParameters{Ld::Type::EmptyDrop, {Ld::Type::None, Ld::Type::Base,
                                        Ld::Type::Drop, Ld::Type::EmptyDrop}},
    TypeTestParameters{Ld::Type::Address, {Ld::Type::None, Ld::Type::Base,
                                           Ld::Type::Drag, Ld::Type::Address}},
    TypeTestParameters{Ld::Type::Input, {Ld::Type::None, Ld::Type::Base,
                                         Ld::Type::Drag, Ld::Type::Address, Ld::Type::Input}},
    TypeTestParameters{Ld::Type::Output, {Ld::Type::None, Ld::Type::Base,
                                        Ld::Type::Drag, Ld::Type::Address, Ld::Type::Output}},
    TypeTestParameters{Ld::Type::Contact, {Ld::Type::None, Ld::Type::Base,
                            Ld::Type::Drag, Ld::Type::Address, Ld::Type::Input, Ld::Type::Contact}},
    TypeTestParameters{Ld::Type::Weektimer, {Ld::Type::None, Ld::Type::Base,
                            Ld::Type::Drag, Ld::Type::Address, Ld::Type::Input, Ld::Type::Weektimer}},
    TypeTestParameters{Ld::Type::Coil, {Ld::Type::None, Ld::Type::Base,
                            Ld::Type::Drag, Ld::Type::Address, Ld::Type::Output, Ld::Type::Coil}},
    TypeTestParameters{Ld::Type::Timer, {Ld::Type::None, Ld::Type::Base,
                            Ld::Type::Drag, Ld::Type::Address, Ld::Type::Output, Ld::Type::Timer}},
    TypeTestParameters{Ld::Type::Counter, {Ld::Type::None, Ld::Type::Base,
                            Ld::Type::Drag, Ld::Type::Address, Ld::Type::Output, Ld::Type::Counter}},
    TypeTestParameters{Ld::Type::Text, {Ld::Type::None, Ld::Type::Base,
                            Ld::Type::Drag, Ld::Type::Address, Ld::Type::Output, Ld::Type::Text}}
));

