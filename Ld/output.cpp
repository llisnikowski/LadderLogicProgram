/*!
 * \file output.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "output.hpp"

namespace Ld{

/*!
 * \brief Konstructor klasy Output
 * \param parent: rodzic/element nadrzędny
 */
Output::Output(QQuickItem *parent)
    :Address{parent}
{
}

Type Output::getType() const
{
    return Type::Output;
}







}// namespace Ld
