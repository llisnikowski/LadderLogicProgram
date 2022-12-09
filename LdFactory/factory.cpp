/*!
 * \file factory.cpp
 * \author Łukasz Liśnikowski
*/
#include "factory.hpp"
#include "painter.hpp"

/*!
 * \brief Konstructor Klasy Factory.
 * \param parent: Rodzic/Element nadrzędny.
 */
Ld::Factory::Factory(QObject *parent)
    :QObject{parent}, painter_{}
{
}

/*!
 * \brief Ustawia klase Painter która będzie przypisana do nowo tworzonych obiektów.
 *
 * Ustwawie również zmienną objectSize_ na podstawie klasy Painter.
 * \param painter: Wskaźnik do klasy Painter.
 */
void Ld::Factory::setPainter(Painter *painter)
{
    painter_ = painter;
}

/*!
 * \brief Zwraca klase Painter przypisywaną do obiektów.
 * \return Wskaźnik do używanej klasy LdPainter.
 */
Ld::Painter *Ld::Factory::getPainter() {
    return painter_;
}

















