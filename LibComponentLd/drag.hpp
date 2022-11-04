#ifndef DRAG_HPP
#define DRAG_HPP

#include "componentLd.hpp"

namespace Ld{


class Drag : public ComponentLd
{
    Q_OBJECT
public:
    explicit Drag(QQuickItem *parent = nullptr);
};


} // namespace Ld

#endif // DRAG_HPP
