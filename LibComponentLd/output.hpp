#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "drag.hpp"

namespace Ld {

class Output : public Drag
{
    Q_OBJECT
public:
    explicit Output(QQuickItem *parent = nullptr);
};



} // namespace Ld

#endif // OUTPUT_HPP
