/*!
 * \file drop.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "drop.hpp"
#include "dropValidator.hpp"
#include <QMimeData>

namespace Ld {


Drop::Drop(QQuickItem *parent)
    :Base{parent}, droppingItem_{}, dropValidator_{}, dragAction_{}
{
    setFlag(ItemAcceptsDrops , true);
}

Drop::~Drop()
{
    if(dropValidator_) delete dropValidator_;
}

Type Drop::getType() const
{
    return Type::Drop;
}

/*!
 * \brief Ustawia obiekt sprawdzający rezultat przenoszenia obiektu dla mechanizmu
 * <a href="https://doc.qt.io/qt-6/dnd.html">
 *  Drag and Drop</a>.
 */
void Drop::setDropValidator(DropValidator *validator)
{
    if(dropValidator_) delete dropValidator_;
    dropValidator_ = validator;
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
    if(!dropValidator_){
        dragAction_ = Qt::IgnoreAction;
    }
    else{
        dragAction_ = dropValidator_->valid(
            event->mimeData()->data("application/x-dnditemdata"));
        if(dragAction_ != Qt::IgnoreAction){
            droppingItem_ = true;
            event->accept();
            update();
        }
    }
    event->setDropAction(dragAction_);
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
    droppingItem_ = false;
    update();
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
    droppingItem_= false;
    event->accept();
    event->setDropAction(dragAction_);
    if(dragAction_ != Qt::IgnoreAction){
        dropValidator_->doAction(
            event->mimeData()->data("application/x-dnditemdata"));
    }
    update();
}





} // namespace Ld
