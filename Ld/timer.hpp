#ifndef TIMER_HPP
#define TIMER_HPP

#include "output.hpp"
#include "typeField.hpp"
#include "textWithComboboxField.hpp"

namespace Ld {

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

    LdProperty::TypeField &getPropertyType();
    LdProperty::TextWithComboboxField &getTime();

protected:
    LdProperty::TypeField type_;
    LdProperty::TextWithComboboxField time_;
};

} //namespace Ld

#endif // TIMER_HPP
