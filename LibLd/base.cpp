/*!
 * \file base.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "base.hpp"

namespace Ld{


/*!
 * \brief Konstructor klasy Base.
 * \param parent: Rodzic/Element nadrzędny.
 */
Base::Base(QQuickItem *parent)
    :QQuickPaintedItem{parent}, ldPainter_{}
{
}

/*!
 * \brief Ustawia klase Painter odpowiedzialną za wyświetlanie na ekranie.
 *
 * Wywołanie funkcji powoduję również wyświetlenie symbolu wywołując funkcję
 * <a href="https://doc.qt.io/qt-5/qquickpainteditem.html#update">
 * QQuickPaintedItem::update()</a>.
 * \param ldPainter: Wskaźnik do klasy Painter.
 * \see getLdPainter()
 */
void Base::setPainter(Painter *ldPainter)
{
    this->ldPainter_ = ldPainter;
    update();
}

/*!
 * \brief Zwraca klase Painter przypisaną do obiektu.
 * \return Wskaźnik do używanej klasy LdPainter.
 * \see setLdPainter()
 */
Painter *Base::getPainter()
{
    return ldPainter_;
}




} // namespace Ld
