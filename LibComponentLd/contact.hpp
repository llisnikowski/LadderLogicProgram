/*!
 * \file contact.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#ifndef CONTACT_HPP
#define CONTACT_HPP

#include "input.hpp"

namespace Ld {

/*!
 * \brief Klasa Coil udostępnia symbol styku z języka LD.
 */
class Contact : public Input
{
    Q_OBJECT
public:
    explicit Contact(QQuickItem *parent = nullptr);
};



} //namespace Ld

#endif // CONTACT_HPP
