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
 * \brief Drag jest klasą udostępniającą interfejs przeciągania symbolu
 * za pomocą myszki.
 */
class Drag : public ComponentLd
{
    Q_OBJECT
public:
    explicit Drag(QQuickItem *parent = nullptr);
};


} // namespace Ld

#endif // DRAG_HPP
