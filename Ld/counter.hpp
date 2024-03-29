#ifndef COUNETER_HPP
#define COUNETER_HPP

#include "output.hpp"
#include "typeField.hpp"
#include "textField.hpp"

namespace Ld {

/*!
 * \brief Klasa Counter udostępnia symbol licznika z języka LD.
 */
class Counter : public Output
{
    Q_OBJECT
public:
    explicit Counter(QQuickItem *parent = nullptr);
    Base *clone(QQuickItem *parent = nullptr) override;

    void paintBase(QPainter *painter) override;
    void paintAdditions(QPainter *painter) override;

    Type getType() const override;
    QByteArray getData() const override;
    friend QDataStream & ::operator >>(QDataStream &, Ld::Base **);

    LdProperty::TypeField &getPropertyType();
    LdProperty::TextField &getCounter();

protected:
    LdProperty::TypeField type_;
    LdProperty::TextField counter_;
};

} //namespace Ld

#endif // COUNETER_HPP
