#ifndef CONTAINERLD_HPP
#define CONTAINERLD_HPP

#include <QQuickItem>
#include <QVector>
#include <cstddef>
#include "drag.hpp"
#include "factoryContainer.hpp"
#include "input.hpp"
#include "output.hpp"
#include "type.hpp"
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

constexpr uint MAX_INPUT_IN_LINE[] = {3, 1, 1};
constexpr uint NODE_POSITION = 3;

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
    using ItArg = void(uint line, uint x, Ld::Base* obj);
    using ItEndLineArg = void(uint line);

    explicit ContainerLd(QQuickItem *parent = nullptr);
    ~ContainerLd();



    const Array & getArray() const {return container_;}
    Item getItem(uint line, uint x);

    void iteratorLineX(ItType itType, std::function<ItArg> fun,
                       std::function<ItEndLineArg> endLineFun = nullptr);

    void iteratorLine(uint line, ItType itType, std::function<ItArg> fun);

    QString getSchemat(bool drawNull = false);

protected:
    void changedFactory() override;

private:
    bool isFreePlaceOnOutput();
    bool isFreePlaceOnInput(uint line);

public:
    bool add(Ld::Drag *obj, uint line, uint x);
    bool addInput(Ld::Input *obj, uint line, uint x);
    bool addOuput(Ld::Output *obj, uint line, uint x);
    bool remove(uint line, int x);

private:
    int findFreePlace(uint line, uint fromX, bool toNode = false);
    int findNode(uint line);
    int getNumberObjectInLine(uint line, Ld::Type type);
    bool shiftRightObject(uint line, uint from, uint distance);
    bool shiftLeftObject(uint line, uint from, uint distance);
    void addLineIfLineIsEmpty(uint line);
    void insertNode(uint line);
    void removeUnnecesseryNode();
    void removeEmptyLine();
    void shiftUp();

    Array container_;
};

#endif // CONTAINERLD_HPP
