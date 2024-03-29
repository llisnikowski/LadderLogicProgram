/*!
 * \file node.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/


#ifndef NODE_HPP
#define NODE_HPP

#include "base.hpp"

namespace Ld {

/*!
 * \brief Klasa Node udostępnia symbol węzła z języka LD.
 */
class Node : public Base
{
    Q_OBJECT
public:
    Node(QQuickItem *parent = nullptr);

    Base *clone(QQuickItem *parent = nullptr) override;

    void paint(QPainter *painter) override;
    Type getType() const override;
    QByteArray getData() const override;

    void displayLine(bool right, bool top, bool bottom);

private:
    bool isNextLine;
    bool isTopLine;
    bool isBottomLine;
};


} //namespace Ld

#endif // NODE_HPP
