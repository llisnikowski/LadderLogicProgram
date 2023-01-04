/*!
 * \file input.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/


#ifndef INPUT_HPP
#define INPUT_HPP

#include "address.hpp"

namespace Ld{

/*!
 * \brief Klasa Input ustawia zachowanie symbolu jako element wejściowy.
 *
 * Klasa dziedziczy pośrednio z klasy Drag udostępniając mechanizm przenoszenia
 * oraz z klasy Address udostępniając adres obiektu.
 * \see Output
 */
class Input : public Address
{
    Q_OBJECT
public:
    explicit Input(QQuickItem *parent = nullptr);

    Type getType() const override;
};


} // namespace Ld

#endif // INPUT_HPP
