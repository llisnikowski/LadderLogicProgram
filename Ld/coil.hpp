/*!
 * \file coil.hpp
 * \author Łukasz Liśnikowski
*/

#ifndef COIL_HPP
#define COIL_HPP

#include "output.hpp"
#include "typeField.hpp"

namespace Ld {

/*!
 * \brief Klasa Coil udostępnia symbol cewki z języka LD.
 */
class Coil : public Output
{
    Q_OBJECT
public:
    explicit Coil(QQuickItem *parent = nullptr);

    Base *clone(QQuickItem *parent = nullptr) override;

    Type getType() const override;

    void paint(QPainter *painter) override;
    QByteArray getData() const override;
    friend QDataStream & ::operator >>(QDataStream &, Ld::Base **);

    LdProperty::TypeField &getPropertyType();

protected:
    LdProperty::TypeField type_;
};

} //namespace Ld

#endif // COIL_HPP
