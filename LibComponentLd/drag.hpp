/*!
 * \file drag.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#ifndef DRAG_HPP
#define DRAG_HPP

#include "componentLd.hpp"

namespace Ld{

/*!
 * \brief Klasa Drag udostępnia interfejs przeciągania obiektu na ekranie za
 *  pomocą myszki.
 */
class Drag : public ComponentLd
{
    Q_OBJECT
public:
    explicit Drag(QQuickItem *parent = nullptr);
};


} // namespace Ld

#endif // DRAG_HPP
