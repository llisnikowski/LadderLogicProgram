/*!
 * \file drag.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#ifndef DRAG_HPP
#define DRAG_HPP

#include "base.hpp"

namespace Ld{

/*!
 * \brief Klasa Drag udostępnia interfejs przeciągania obiektu na ekranie za
 *  pomocą myszki.
 */
class Drag : public Base
{
    Q_OBJECT
public:
    explicit Drag(QQuickItem *parent = nullptr);
};


} // namespace Ld

#endif // DRAG_HPP
