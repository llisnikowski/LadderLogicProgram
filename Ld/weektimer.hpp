#ifndef WEEKTIMER_HPP
#define WEEKTIMER_HPP

#include "input.hpp"
#include "textField.hpp"
#include "daysOfWeekField.hpp"

namespace Ld {

/*!
 * \brief Klasa Coil udostępnia symbol zegara tygodniowego.
 *
 * Przechowuje dni tygodnia oraz godziny włączenia i wyłączenia zegara
 */
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

    LdProperty::TextField &getTimeOn();
    LdProperty::TextField &getTimeOff();
    LdProperty::DaysOfWeekField &getDaysOfWeek();

protected:
    LdProperty::TextField timeOn_;
    LdProperty::TextField timeOff_;
    LdProperty::DaysOfWeekField daysOfWeek_;
};


} //namespace Ld

#endif // WEEKTIMER_HPP
