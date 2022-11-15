/*!
 * \file drag.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "drag.hpp"
#include <QMimeData>
#include <QPixmap>
#include <QPainter>
#include <QDrag>

namespace Ld{

/*!
 * \brief Konstructor klasy Drag
 * \param parent: rodzic/element nadrzędny
 */
Drag::Drag(QQuickItem *parent)
    :Base{parent}
{
    setAcceptedMouseButtons(Qt::LeftButton);
}

/*!
 * \brief Akceptuje wydażenie naciśnięcia przycisku myszką. Umożliwia wykrycie
 *  kolejnych zdarzeń jak przeciąganie lub zwolnienie klawisza.
 * \param event: Wydarzenie naciśnięcia przycisku myszy.
 * \see
 * <a href="https://doc.qt.io/qt-5/qmouseevent.html">QMouseEvent</a>.
 */
void Drag::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

/*!
 * \brief Ustawia przeciąganie obiektu po wystąpieniu wydażenia ruchu
 *  kursora.
 * \param event: Wydarzenie ruchu kursora myszy.
 * \see
 * <a href="https://doc.qt.io/qt-5/qmouseevent.html">QMouseEvent</a>.
 */
void Drag::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();

    QDrag *drag = createQDrag(*event);
    Qt::DropAction dragAction = drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::IgnoreAction);
    if (dragAction == Qt::CopyAction) {
    }
    else if (dragAction == Qt::MoveAction) {
    }
}

/*!
 * \brief Wirtualna metoda rysująca ikonę przeciągania.
 *
 * Nie przesłonięta uruchamia domyślną metode rysującą obiekt (paint()).
 * \param painter: Referencja do klasy rysującej
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void Drag::paintDrag(QPainter &painter)
{
    paint(&painter);
}

/*!
 * \brief Tworzy klasę
 * <a href="https://doc.qt.io/qt-5/qdrag.html">QDrag</a>
 * zapewniającą obsługę dla metody przeciągnij i upuść.
 * \param event: Wydarzenie
 * <a href="https://doc.qt.io/qt-5/qmouseevent.html">QMouseEvent</a>.
 * \return Wskaźnik do utworzonego obiektu
 * <a href="https://doc.qt.io/qt-5/qdrag.html">QDrag</a>.
 */
QDrag *Drag::createQDrag(QMouseEvent &event)
{
    QDrag *drag = new QDrag(this);
    drag->setMimeData(createDragData(event));
    drag->setPixmap(createDragPixmap());
    drag->setHotSpot(event.pos() - QPoint(0,0));
    return drag;
}

/*!
 * \brief Tworzy kontener danych dla wydarzenia przeciągania.
 * \param event: Wydarzenie
 * <a href="https://doc.qt.io/qt-5/qmouseevent.html">QMouseEvent</a>.
 * \return Wskaźnik do utworzonego obiektu
 * <a href="https://doc.qt.io/qt-5/qmimedata.html">QMimeData</a>.
 */
QMimeData *Drag::createDragData(QMouseEvent &event)
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QPoint(event.pos() - QPoint(0,0));

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    return mimeData;
}

/*!
 * \brief Tworzy ikonę przeciągania.
 * \return Obraz
 * <a href="https://doc.qt.io/qt-5/qpixmap.html">QPixmap</a>.
 */
QPixmap Drag::createDragPixmap()
{
    QPixmap pixmap(width(), height());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing, true);
    paintDrag(painter);
    return pixmap;
}




} // namespace Ld