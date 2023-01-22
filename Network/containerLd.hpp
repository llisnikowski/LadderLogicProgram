#ifndef CONTAINERLD_HPP
#define CONTAINERLD_HPP

#include <QQuickItem>
#include <QVector>
#include <cstddef>
#include "address.hpp"
#include "address.hpp"
#include "input.hpp"
#include "output.hpp"
#include "type.hpp"
#include <functional>
#include "position.hpp"

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
    explicit ContainerLd(QQuickItem *parent = nullptr);
    virtual ~ContainerLd();

    using Item = Ld::Base*;
    using Line = QVector<Item>;
    using Array = QVector<Line>;


    using ItArg = void(Position poz, Ld::Base* obj);
    using ItArgConst = void(Position poz, const Ld::Base* obj);
    using ItEndLineArg = void(int line);
    using ItEndXArg = void(int x);
    void iteratorLineX(QVector<Ld::Type> types, std::function<ItArg> fun,
                       std::function<ItEndLineArg> endLineFun = nullptr);
    void iteratorLineX(QVector<Ld::Type> types, std::function<ItArgConst> fun,
                       std::function<ItEndLineArg> endLineFun = nullptr) const;
    void iteratorXLine(QVector<Ld::Type> types, std::function<ItArg> fun,
                       std::function<ItEndXArg> endXFun = nullptr);
    void iteratorLine(int line, QVector<Ld::Type> types, std::function<ItArg> fun);
    void iteratorLine(int line, QVector<Ld::Type> types, std::function<ItArgConst> fun) const;
    void iteratorX(int x, QVector<Ld::Type> types, std::function<ItArg> fun);

    const Array & getArray() const {return container_;}
    Ld::Base* getItem(Position poz);
    const Ld::Base* getItem(Position poz) const;
    Ld::Address *getAddressItem(Position poz);
    const Ld::Address *getAddressItem(Position poz) const;

    QString getSchemat();
    int getId() const;

    friend QDataStream &operator<<(QDataStream &stream, ContainerLd &containerLd);
    friend QDataStream &operator>>(QDataStream &stream, ContainerLd &containerLd);

signals:
    void addLdObject(ContainerLd*);

public:
    bool add(Ld::Address *obj, Position poz);
    bool addInput(Ld::Input *obj, Position poz);
    bool addOuput(Ld::Output *obj, Position poz);
    bool remove(Position poz);
    bool move(Position fromPoz, Position toPoz);

    bool checkAddCondition(const Ld::Address *obj, Position poz) const;
    bool checkAddInputCondition(const Ld::Input *obj, Position poz) const;
    bool checkAddOutputCondition(const Ld::Output *obj, Position poz) const;
    bool checkRemoveCondition(Position poz) const;
    bool checkMoveCondition(Position fromPoz, Position toPoz) const;

private:
    int find(int line, Ld::Type type) const;
    int getNumberObject(Ld::Type type) const;
    int getNumberObjectInLine(int line, Ld::Type type) const;
    bool setToNearestAddresItem(Position &pos, bool lastField = true) const;
    void addNewRow(int line);
    void insertNode();
    void removeUnnecesseryNode();
    void removeEmptyLine();
    void shiftUp();
    void updateSize();
    void updateLdObjectData();
    void updateLineDisplay();
    void updateNodeDisplay();

    static int currentId;
    int id_;
    Array container_;
};


QDataStream &operator<<(QDataStream &stream, ContainerLd &containerLd);
QDataStream &operator>>(QDataStream &stream, ContainerLd &containerLd);

#endif // CONTAINERLD_HPP
