#ifndef TIMER_HPP
#define TIMER_HPP

#include "comboboxField.hpp"
#include "output.hpp"
#include "textField.hpp"
#include "typeField.hpp"

namespace Ld {

/*!
 * \brief Klasa Timer udostępnia symbol timera z języka LD.
 */
class Timer : public Output
{
    Q_OBJECT
public:
    explicit Timer(QQuickItem *parent = nullptr);
    Base *clone(QQuickItem *parent = nullptr) override;

    void paint(QPainter *painter) override;

    Type getType() const override;
    QByteArray getData() const override;
    friend QDataStream & ::operator >>(QDataStream &, Ld::Base **);

    LdProperty::TypeField &getTimeCourse();
    LdProperty::ComboboxField &getTimeMode();
    LdProperty::TextField &getTime(int i);

protected:
    LdProperty::TypeField timeCourse_;
    LdProperty::ComboboxField timeMode_;
    LdProperty::TextField times_[2];
};

} //namespace Ld

#endif // TIMER_HPP
