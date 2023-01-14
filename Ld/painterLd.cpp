/*!
 * \file ldPainter.cpp
 * \author Łukasz Liśnikowski
*/
#include "painterLd.hpp"
#include <QPainter>
#include <QPen>
#include <QDebug>

namespace Ld {

/*!
 * \brief Konstructor Klasy LdPainter.
 * \param cellSize: Domyślna szerokość symbolu w pixelach.
 * \param penSize: Domyślna grubość pędzla.
 */
PainterLd::PainterLd(QPainter *painter, QSizeF objectSize)
    :painter_{painter},
    objectSize_{objectSize},
    verticalLineX_{CONTACT_V_LINE_X_FACTORY * objectSize.width()},
    verticalLineHeight_{CONTACT_V_LINE_HEIGHT_FACTORY * objectSize.height()},
    contactSlashOffsetX_{CONTACT_SLASH_OFFSET_X_FACTORY * objectSize.width()},
    contactSlashHeight_{CONTACT_SLASH_HEIGHT_FACTORY*objectSize.height()},
    coilArcAngle_{COIL_ARC_ANGLE},
    coilArcRadius_{COIL_ARC_RADIOUS_FACTORY * objectSize_.height()},
    coilArcOffsetX_{COIL_ARC_OFFSET_FACTORY * objectSize_.width()}
{
}

/*!
 * \brief Funkcja odpowiedzialna za rysowanie styku.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void PainterLd::drawContact()
{
    drawContactContour();
}

void PainterLd::drawContactSlash()
{
    drawSlashLine(verticalLineX_ + contactSlashOffsetX_, contactSlashHeight_);
}

/*!
 * \brief Funkcja odpowiedzialna za rysowanie cewki.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void PainterLd::drawCoil()
{
    drawCoilContour();
}

/*!
 * \brief Funkcja odpowiedzialna za rysowanie symbolu linii.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void PainterLd::drawLine()
{
    drawHoryzontalLine();
}

void PainterLd::drawLineStart()
{
    drawVerticalLine(painter_->pen().width()/2, 16);
}

void PainterLd::drawLineEnd()
{
    drawVerticalLine(objectSize_.width() - painter_->pen().width()/2, 16);
}

void PainterLd::drawNode(bool left, bool right, bool top, bool bottom)
{
    if(left){
        drawLineToMiddle(0, objectSize_.height() / 2);
    }
    if(right){
        drawLineToMiddle(objectSize_.width(), objectSize_.height() / 2);
    }
    if(top){
        drawLineToMiddle(objectSize_.width() / 2, 0);
    }
    if(bottom){
        drawLineToMiddle(objectSize_.width() / 2, objectSize_.height());
    }
    drawPointInMiddle(NODE_POINT_SIZE_FACTORY * objectSize_.height());
}

/*!
 * \brief Funkcja rysująca sam styk.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void PainterLd::drawContactContour()
{
    drawVerticalPairLine(verticalLineX_, verticalLineHeight_);
    drawHorizontalPairLine(verticalLineX_);
}

/*!
 * \brief Funkcja rysująca samą cewkę.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void PainterLd::drawCoilContour()
{
    drawPairArc(coilArcAngle_, coilArcRadius_, coilArcOffsetX_);
    drawHorizontalPairLine(objectSize_.width() / 2 - coilArcRadius_
                           + coilArcOffsetX_);
}

/*!
 * \brief Funkcja rysująca parę pionowych linii.
 *
 * Linie są wyśrodkowane względem osi X i
 * symetryczne względem środkowej osi Y obiektu.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 * \param x: Pozycja X linii.
 * \param height: Długość linii.
 * \see drawVerticalLine().
 */
void PainterLd::drawVerticalPairLine(float x, float height)
{
    drawVerticalLine(x, height);
    drawVerticalLine(objectSize_.width() - x, height);
}

void PainterLd::drawVerticalLine(float x, float height)
{
    painter_->drawLine(x, objectSize_.height() / 2 - height / 2,
                       x, objectSize_.height() / 2 + height / 2);
}

void PainterLd::drawSlashLine(float x, float height)
{
    painter_->drawLine(x,
                       objectSize_.height() / 2 + height / 2,
                       objectSize_.width() - x,
                       objectSize_.height() / 2 - height / 2);
}

/*!
 * \brief Funkcja rysująca pionową linię.
 *
 * Linie są wyśrodkowane względem osi X.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 * \param x: Pozycja X linii.
 * \param height: Długość linii.
 * \see drawVerticalPairLine().
 */
void PainterLd::drawVerticalLine()
{
    painter_->drawLine(objectSize_.width() / 2, 0,
                     objectSize_.width() / 2, objectSize_.height());
}

/*!
 * \brief Funkcja rysująca parę poziomych linii.
 *
 * Linie są wyśrodkowane względem osi X.
 * Pierwsz linia jest rysowana od lewej strony obiektu do podanego X.
 * Druga linia jest symetryczna względem osi Y.
 * \param painter: Referencja do klasy.
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 * \param x: Pozycja X linii.
 */
void PainterLd::drawHorizontalPairLine(float x)
{
    painter_->drawLine(0, objectSize_.height() / 2, x, objectSize_.height() / 2);
    painter_->drawLine(objectSize_.width() - x, objectSize_.height() / 2,
                     objectSize_.width(),     objectSize_.height() / 2);
}

/*!
 * \brief Funkcja rysująca parę łuków o podanym kącie, promieniu
 * i przesunięciu wzdłuż osi X.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 * \param angle: Kąt łuku.
 * \param radius: Promień łuku.
 * \param offsetX: Przesunięcię wzdłuż osi X.
 */
void PainterLd::drawPairArc(float angle, float radius, float offsetX)
{
    painter_->drawArc(getCenteredRect(radius * 2, radius * 2, offsetX), (-angle/2 + 180) * 16, angle * 16);
    painter_->drawArc(getCenteredRect(radius * 2, radius * 2, -offsetX), (-angle/2) * 16, angle * 16);
}

/*!
 * \brief Funkcja zwraca wyśrodkowany względem obiektu prostokąt.
 * \param width: Szerokość prostokątu.
 * \param height: Wysokość prostokątu.
 * \param offsetX: Przesunięcię wzdłuż osi X.
 * \param offsetY: Przesunięcię wzdłuż osi Y.
 * \return Obiekt prostokąta
 * <a href="https://doc.qt.io/qt-5/qrectf.html">QRectF</a>.
 */
QRectF PainterLd::getCenteredRect(float width, float height, float offsetX, float offsetY)
{
    float halfDifferenceWidth = (objectSize_.width() - width) / 2;
    float halfDifferenceHeight = (objectSize_.height() - height) / 2;
    return QRectF{halfDifferenceWidth + offsetX, halfDifferenceHeight + offsetY, width, height};
}

/*!
 * \brief Funkcja rysująca prostą linię od lewej do prawej.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void PainterLd::drawHoryzontalLine()
{
    painter_->drawLine(0, objectSize_.height() / 2, objectSize_.width(),
                       objectSize_.height() / 2);
}

void PainterLd::drawLineToMiddle(float x, float y)
{
    painter_->drawLine(x, y, objectSize_.width() / 2,
                       objectSize_.height() / 2);
}

void PainterLd::drawPointInMiddle(float size)
{
    QPen oldPen = painter_->pen();
    QPen newPen = oldPen;
    newPen.setWidth(size);
    painter_->setPen(newPen);
    painter_->drawPoint(objectSize_.width() / 2,
                        objectSize_.height() / 2);
    painter_->setPen(oldPen);
}

void PainterLd::fillColor(QColor color)
{
    painter_->fillRect(QRectF{{0, 0}, objectSize_}, color);
}

void PainterLd::drawFrame(qreal frameWidth)
{
    painter_->drawRect(frameWidth / 2, frameWidth / 2,
                     objectSize_.width() - frameWidth / 2,
                       objectSize_.height() - frameWidth / 2);
}

void PainterLd::printCenterLetter(QChar letter)
{
    QFont font = painter_->font();
    font.setPixelSize(CENTER_LETTER_SIZE);
    font.setBold(CENTER_LETTER_BOLD);
    painter_->setFont(font);
    QRectF litterRect {{CORRECT_CENTER_LETTER_OFFSET_X,
                       CORRECT_CENTER_LETTER_OFFSET_Y}, objectSize_};
    painter_->drawText(litterRect, Qt::AlignCenter, letter);
}


} //namespace Ld

