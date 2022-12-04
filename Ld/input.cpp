/*!
 * \file input.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "input.hpp"

namespace Ld{

/*!
 * \brief Konstructor klasy Input
 * \param parent: rodzic/element nadrzędny
 */
Input::Input(QQuickItem *parent)
    :Drag{parent}
{
}

Type Input::getType() const
{
    return Type::Input;
}



} // namespace Ld
