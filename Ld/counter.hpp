#ifndef COUNETER_HPP
#define COUNETER_HPP

#include "output.hpp"
#include "comboboxField.hpp"
#include "textField.hpp"

namespace Ld {

class Counter : public Output
{
    Q_OBJECT
public:
    explicit Counter(QQuickItem *parent = nullptr);
    Base *clone(QQuickItem *parent = nullptr) override;

    void paint(QPainter *painter) override;

    Type getType() const override;
    QByteArray getData() const override;
    friend QDataStream & ::operator >>(QDataStream &, Ld::Base **);

protected:
    LdProperty::ComboboxField type_;
    LdProperty::TextField counter_;
};

} //namespace Ld

#endif // COUNETER_HPP
