#include "base.hpp"
#include <QQmlEngine>
#include <functional>

namespace Ld{


Base::Base(QQuickItem *parent)
    :QQuickPaintedItem{parent}, isDrag_{}, properties_{},
    selected_{}
{
    setAcceptedMouseButtons(Qt::LeftButton);
    QObject::connect(this, &Base::clicked,
                     std::bind(&Base::setSelect, this, true));

    if(parent){
        QQmlEngine::setContextForObject(this,
                QQmlEngine::contextForObject(parent));
    }
}

/*!
 * \brief Wirtualna funkcja zwracająca typ obiektu.
 */
Type Base::getType() const
{
    return Type::Base;
}

/*!
 * \brief Funkcja dodająca obiek właściwości do listy.
 */
void Base::addProperty(LdProperty::Base *property)
{
    if(!property) return;
    properties_.append(property);
}

/*!
 * \brief Funkcja zwracająca listę obiektów właściwości
 */
QVector<LdProperty::Base*> &Base::getPropertiesList()
{
    return properties_;
}

/*!
 * \brief Funkcja ustawiająca zaznaczenie obiektu
 */
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

/*!
 * \brief Funkcja obsługująca wydarzenie MouseMosePress.
 * \param event: Wskaźnik do obiektu
 * <a href="https://doc.qt.io/qt-6/qmouseevent.html">QMouseEvent</a>.
 */
void Base::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    isDrag_ = true;
}

/*!
 * \brief Funkcja obsługująca wydarzenie MouseRelease
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

/*!
 * \brief Funkcja wirtualna wywoływana w momencie kliknięcia obiektu
 * \param event
 */
void Base::clickEvent(QMouseEvent *event)
{
    event->accept();
    forceActiveFocus();
    emit clicked();
}






} // namespace Ld
