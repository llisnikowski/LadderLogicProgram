#ifndef CONTAINERLD_HPP
#define CONTAINERLD_HPP

#include <QQuickItem>
#include <QVector>
#include <cstddef>
#include "factoryContainer.hpp"
#include <functional>

namespace Ld {
class Base;
}

// -I-+-I-+-I-+-O-
// -I-+
// -I-+



constexpr const char * STRUCTURE_LINE_1 {"-I-+-I-I-O-"};
constexpr const char * STRUCTURE_LINE_2 {"-I-+"};
constexpr const char * STRUCTURE_LINE_3 {"-I-+"};

constexpr std::size_t NUMBERS_OBJECTS_FOR_LINE_1 {std::char_traits<char>::length(STRUCTURE_LINE_1)};
constexpr std::size_t NUMBERS_OBJECTS_FOR_LINE_2 {std::char_traits<char>::length(STRUCTURE_LINE_2)};
constexpr std::size_t NUMBERS_OBJECTS_FOR_LINE_3 {std::char_traits<char>::length(STRUCTURE_LINE_3)};

constexpr float MAX_LENGTH_LINE {64*4 + 64*4 + 16};



class ContainerLd : public QQuickItem, public Ld::FactoryContainer
{
    Q_OBJECT
public:
    using Item = Ld::Base*;
    using Line = QVector<Item>;
    using Array = QVector<Line>;

    enum ItType{
        ItIn = 0x01,
        ItOut = 0x02,
        ItLine = 0x04,
        ItNode = 0x08,
        ItNull = 0x10,
        ItInOut = ItIn | ItOut,
        ItFilled = ItInOut | ItLine | ItNode,
        ItAll = ItNull | ItFilled
    };
    using ItArg = void(int line, int x, Ld::Base* obj);
    using ItEndLineArg = void(int line);

    explicit ContainerLd(QQuickItem *parent = nullptr);



    const Array & getArray() const {return container_;}
    Item getItem(uint line, uint x);

    void iteratorLineX(ItType itType, std::function<ItArg> fun,
                       std::function<ItEndLineArg> endLineFun = nullptr);

    QString getSchemat();

protected:
    void changedFactory() override;

private:
    Array container_;
};

#endif // CONTAINERLD_HPP
