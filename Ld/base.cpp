/*!
 * \file base.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "base.hpp"
#include <QQmlEngine>

namespace Ld{


/*!
 * \brief Konstructor klasy Base. Włącza obsługę lewego przycisku myszy.
 * \param parent: Rodzic/Element nadrzędny.
 */
Base::Base(QQuickItem *parent)
    :QQuickPaintedItem{parent}, ldPainter_{}, properties_{}, showProperties_{true}
{
    setAcceptedMouseButtons(Qt::LeftButton);

    if(parent){
        QQmlEngine::setContextForObject(this,
                QQmlEngine::contextForObject(parent));
    }
}

Type Base::getType() const
{
    return Type::Base;
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

void Base::setVisibleProperties(bool visible)
{
    if(showProperties_ == visible) return;
    showProperties_ = visible;
    for(auto property : properties_){
        property->setVisible(showProperties_);
    }
}

void Base::addProperty(LdProperty::Base *property)
{
    if(!property) return;
    properties_.append(property);

    if(showProperties_)
    property->setVisible(true);
}

/*!
 * \brief Funkcja obsługująca wydarzenie MouseButtonPress.
 * \param event: Wskaźnik do obiektu
 * <a href="https://doc.qt.io/qt-6/qmouseevent.html">QMouseEvent</a>.
 */
void Base::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void Base::mouseMoveEvent(QMouseEvent *event)
{
    isDrag_ = true;
}

/*!
 * \brief Funkcja obsługująca wydarzenie MouseRelease
 *
 * \param event: Wskaźnik do obiektu
 * <a href="https://doc.qt.io/qt-6/qmouseevent.html">QMouseEvent</a>.
 */
void Base::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
    if(isDrag_){
        isDrag_ = false;
    }
    else{
        clickEvent(event);
    }
}

void Base::clickEvent(QMouseEvent *event)
{
    qDebug() << "click";
}





} // namespace Ld
