#ifndef WEEKTIMER_HPP
#define WEEKTIMER_HPP

#include "input.hpp"

namespace Ld {

class Weektimer : public Input
{
    Q_OBJECT
public:
    explicit Weektimer(QQuickItem *parent = nullptr);
    Base *clone(QQuickItem *parent = nullptr) override;

    void paint(QPainter *painter) override;

    Type getType() const override;
    QByteArray getData() const override;
    friend QDataStream & ::operator >>(QDataStream &, Ld::Base **);

protected:
};


} //namespace Ld

#endif // WEEKTIMER_HPP
