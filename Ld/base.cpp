/*!
 * \file base.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "base.hpp"
#include <QQmlEngine>
#include <functional>

namespace Ld{


/*!
 * \brief Konstructor klasy Base. Włącza obsługę lewego przycisku myszy.
 * \param parent: Rodzic/Element nadrzędny.
 */
Base::Base(QQuickItem *parent)
    :QQuickPaintedItem{parent}, isDrag_{}, properties_{},
    showProperties_{true}, selected_{}
{
    setAcceptedMouseButtons(Qt::LeftButton);
    QObject::connect(this, &Base::clicked,
                     std::bind(&Base::setSelect, this, true));

    if(parent){
        QQmlEngine::setContextForObject(this,
                QQmlEngine::contextForObject(parent));
    }
}

Type Base::getType() const
{
    return Type::Base;
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

QVector<LdProperty::Base*> &Base::getPropertiesList()
{
    return properties_;
}

void Base::setSelect(bool sel)
{
    selected_ = sel;
    update();
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
    forceActiveFocus();
    emit clicked();
}






} // namespace Ld
