/*!
 * \file output.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/


#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include "address.hpp"

namespace Ld {

/*!
 * \brief Klasa Coil ustawia zachowanie symbolu jako element wyjściowy.
 *
 * Klasa dziedziczy z klasy Drag udostępniając mechanizm przenoszenia.
 * \see Input
 */
class Output : public Address
{
    Q_OBJECT
public:
    explicit Output(QQuickItem *parent = nullptr);

    Type getType() const override;
};



} // namespace Ld

#endif // OUTPUT_HPP
