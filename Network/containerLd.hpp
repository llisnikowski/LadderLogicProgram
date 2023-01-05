#ifndef CONTAINERLD_HPP
#define CONTAINERLD_HPP

#include <QQuickItem>
#include <QVector>
#include <cstddef>
#include "drag.hpp"
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
constexpr float LD_H {64};
constexpr float LD_W {64};
constexpr float NODE_W{16};
constexpr float LINE_BESIDE_NODE{32};

constexpr uint MAX_INPUT_IN_LINE[] = {3, 1, 1};
constexpr uint NODE_POSITION = 3;

class ContainerLd : public QQuickItem
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
        ItDropDrag = ItInOut | ItLine,
        ItFilled = ItInOut | ItLine | ItNode,
        ItAll = ItNull | ItFilled
    };
    using ItArg = void(uint line, uint x, Ld::Base* obj);
    using ItArgConst = void(uint line, uint x, Ld::Base* obj);
    using ItEndLineArg = void(uint line);
    using ItEndXArg = void(uint x);

    explicit ContainerLd(QQuickItem *parent = nullptr);
    virtual ~ContainerLd();

    const Array & getArray() const {return container_;}
    Ld::Base* getItem(uint line, uint x);
    const Ld::Base *getItem(uint line, uint x) const;
    Ld::Drag *getDragItem(uint line, uint x);
    const Ld::Drag *getDragItem(uint line, uint x) const;

    void iteratorLineX(ItType itType, std::function<ItArg> fun,
                       std::function<ItEndLineArg> endLineFun = nullptr);
    void iteratorXLine(ItType itType, std::function<ItArg> fun,
                       std::function<ItEndXArg> endXFun = nullptr);

    void iteratorLine(uint line, ItType itType, std::function<ItArg> fun);
    void iteratorLine(uint line, ItType itType, std::function<ItArgConst> fun) const;
    void iteratorX(uint x, ItType itType, std::function<ItArg> fun);

    QString getSchemat();
    int getId() const;
    void setId(int id){id_ = id;}

    friend QDataStream &operator<<(QDataStream &stream, ContainerLd &containerLd);
    friend QDataStream &operator>>(QDataStream &stream, ContainerLd &containerLd);

signals:
    void addLdObject(ContainerLd*);

public:
    bool add(Ld::Drag *obj, uint line, uint x);
    bool addInput(Ld::Input *obj, uint line, uint x);
    bool addOuput(Ld::Output *obj, uint line, uint x);
    bool remove(uint line, uint x);
    bool move(uint fromLine, uint fromX, uint toLine, uint toX);

    bool checkAddCondition(const Ld::Drag *obj, uint line, uint x) const;
    bool checkAddInputCondition(const Ld::Input *obj, uint line, uint x) const;
    bool checkAddOutputCondition(const Ld::Output *obj, uint line, uint x) const;
    bool checkRemoveCondition(uint line, uint x) const;
    bool checkMoveCondition(uint fromLine, uint fromX, uint toLine, uint toX) const;

private:
    int find(uint line, Ld::Type type) const;
    int getNumberObjectInLine(uint line, Ld::Type type) const;
    void addLineIfLineIsEmpty(uint line);
    void insertNode();
    void removeUnnecesseryNode();
    void removeEmptyLine();
    void shiftUp();
    void updateSize();
    void updateLdObjectData();
    void updateNodeDisplay();

    static int currentId;
    int id_;
    Array container_;
};


QDataStream &operator<<(QDataStream &stream, ContainerLd &containerLd);
QDataStream &operator>>(QDataStream &stream, ContainerLd &containerLd);

#endif // CONTAINERLD_HPP
