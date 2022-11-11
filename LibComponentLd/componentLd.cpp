/*!
 * \file componentLd.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "componentLd.hpp"

namespace Ld{


/*!
 * \brief Konstructor klasy ComponentLd.
 * \param parent: Rodzic/Element nadrzędny.
 */
ComponentLd::ComponentLd(QQuickItem *parent)
    :QQuickPaintedItem{parent}, ldPainter_{}
{
}

/*!
 * \brief Ustawia klase LdPainter odpowiedzialną za wyświetlanie na ekranie.
 *
 * Wywołanie funkcji powoduję również wyświetlenie symbolu wywołując funkcję
 * <a href="https://doc.qt.io/qt-5/qquickpainteditem.html#update">
 * QQuickPaintedItem::update()</a>.
 * \param ldPainter: Wskaźnik do nowo używanej klasy.
 * \see getLdPainter()
 */
void ComponentLd::setLdPainter(LdPainter *ldPainter)
{
    this->ldPainter_ = ldPainter;
    update();
}

/*!
 * \brief Zwraca klase LdPainter przypisaną do obiektu.
 * \return Wskaźnik do używanej klasy LdPainter.
 * \see setLdPainter()
 */
LdPainter *ComponentLd::getLdPainter()
{
    return ldPainter_;
}




} // namespace Ld
