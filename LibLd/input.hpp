/*!
 * \file input.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/


#ifndef INPUT_HPP
#define INPUT_HPP

#include "drag.hpp"

namespace Ld{

/*!
 * \brief Klasa Coil ustawia zachowanie symbolu jako element wejściowy.
 *
 * Klasa dziedziczy z klasy Drag udostępniając mechanizm przenoszenia.
 * \see Output
 */
class Input : public Drag
{
    Q_OBJECT
public:
    explicit Input(QQuickItem *parent = nullptr);

    Type getType() const override;
};


} // namespace Ld

#endif // INPUT_HPP
