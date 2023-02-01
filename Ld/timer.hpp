#ifndef TIMER_HPP
#define TIMER_HPP

#include "comboboxField.hpp"
#include "image.hpp"
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

    void paintBase(QPainter *painter) override;
    void paintAdditions(QPainter *painter) override;

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
    LdProperty::Image waveforms_;
};

} //namespace Ld

#endif // TIMER_HPP
