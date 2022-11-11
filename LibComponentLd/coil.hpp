/*!
 * \file coil.hpp
 * \author Łukasz Liśnikowski
*/

#ifndef COIL_HPP
#define COIL_HPP

#include "output.hpp"

namespace Ld {

/*!
 * \brief Klasa Coil udostępnia symbol cewki z języka LD.
 */
class Coil : public Output
{
    Q_OBJECT
public:
    explicit Coil(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;
};

} //namespace Ld

#endif // COIL_HPP
