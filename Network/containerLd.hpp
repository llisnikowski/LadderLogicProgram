#ifndef CONTAINERLD_HPP
#define CONTAINERLD_HPP

#include <QQuickItem>
#include <QVector>
#include "factoryContainer.hpp"

namespace Ld {
class Base;
}

// -I-+-I-+-I-+-O-
// -I-+
// -I-+

constexpr int INPUTS_IN_LINE_1{3};
constexpr int OUTPUTS_IN_LINE_1{1};
constexpr int INPUTS_IN_LINE_2{1};
constexpr int INPUTS_IN_LINE_3{1};

constexpr int NUMBERS_OBJECTS_PER_INPUT {4};
constexpr int NUMBERS_OBJECTS_PER_OUTPUT {3};



class ContainerLd : public QQuickItem, public Ld::FactoryContainer
{
    Q_OBJECT
public:
    using Item = Ld::Base*;
    using Line = QVector<Item>;
    using Array = QVector<Line>;

    explicit ContainerLd(QQuickItem *parent = nullptr);

    const Array & getArray() const {return container_;}
    Item getItem(uint line, uint x);

protected:
    void changedFactory() override;

private:
    Array container_;
};

#endif // CONTAINERLD_HPP
