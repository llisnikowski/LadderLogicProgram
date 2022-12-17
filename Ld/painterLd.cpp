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
    verticalLineHeight_{CONTACT_V_LINE_HEIGHT_FACTORY * objectSize.width()},
    coilArcAngle_{COIL_ARC_ANGLE},
    coilArcRadius_{COIL_ARC_RADIOUS_FACTORY * objectSize_.width()},
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

void PainterLd::drawNode()
{
    drawHoryzontalLine();
    drawVerticalLine();
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


} //namespace Ld

