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
 * \brief Klasa Coil udostępnia symbol węzła z języka LD.
 */
class Node : public Base
{
    Q_OBJECT
public:
    Node(QQuickItem *parent = nullptr);
};


} //namespace Ld

#endif // NODE_HPP
