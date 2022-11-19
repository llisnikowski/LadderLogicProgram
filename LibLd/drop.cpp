/*!
 * \file drop.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "drop.hpp"

namespace Ld {

/*!
 * \brief Konstructor klasy Drop. Inicjalizuje mechanizm
 * <a href="https://doc.qt.io/qt-6/dnd.html"> Drag and Drop</a>.
 * \param parent: rodzic/element nadrzędny.
 */
Drop::Drop(QQuickItem *parent)
    :Base{parent}
{
    setFlag(ItemAcceptsDrops , true);
}

/*!
 * \brief Funkcja obsługująca wydarzenie EnterEvent.
 *
 * \param event: Wskaźnik do obiektu
 * <a href="https://doc.qt.io/qt-6/qdragenterevent.html">
 * QDragEnterEvent</a>.
 */
void Drop::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "dragEnterEvent";
    event->accept();
}

/*!
 * \brief Funkcja obsługująca wydarzenie DragLeave.
 *
 * \param event: Wskaźnik do obiektu
 * <a href="https://doc.qt.io/qt-6/qdragleaveevent.html">
 * QDragLeaveEvent</a>.
 */
void Drop::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

/*!
 * \brief Funkcja obsługująca wydarzenie DragMove.
 *
 * \param event Wskaźnik do obiektu
 * <a href="https://doc.qt.io/qt-6/qdragmoveevent.html">
 * QDragMoveEvent</a>.
 */
void Drop::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
}

/*!
 * \brief Funkcja obsługująca wydarzenie DropEvent.
 *
 * \param event Wskaźnik do obiektu
 * <a href="https://doc.qt.io/qt-6/qdropevent.html">
 * QDragEnterEvent</a>.
 */
void Drop::dropEvent(QDropEvent *event)
{
    qDebug() << "dropEvent";
    event->setDropAction(Qt::CopyAction);
    event->accept();
}




} // namespace Ld
