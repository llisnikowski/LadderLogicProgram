#ifndef INPUT_HPP
#define INPUT_HPP

#include "drag.hpp"

namespace Ld{

class Input : public Drag
{
    Q_OBJECT
public:
    explicit Input(QQuickItem *parent = nullptr);
};


} // namespace Ld

#endif // INPUT_HPP
