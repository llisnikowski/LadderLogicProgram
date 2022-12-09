/*!
 * \file factory.cpp
 * \author Łukasz Liśnikowski
*/
#include "factoryLd.hpp"
#include "painter.hpp"


Ld::Painter *FactoryLd::painter_ = nullptr;

/*!
 * \brief Ustawia klase Painter która będzie przypisana do nowo tworzonych obiektów.
 *
 * Ustwawie również zmienną objectSize_ na podstawie klasy Painter.
 * \param painter: Wskaźnik do klasy Painter.
 */
void FactoryLd::setPainter(Ld::Painter *painter)
{
    painter_ = painter;
}


Ld::Painter *FactoryLd:: getPainter()
{
    return painter_;
}

















