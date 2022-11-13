/*!
 * \file ldPainter.cpp
 * \author Łukasz Liśnikowski
*/
#include "painter.hpp"
#include <QPainter>
#include <QPen>
#include <QDebug>

namespace Ld {

/*!
 * \brief Konstructor Klasy LdPainter.
 * \param cellSize: Domyślna szerokość symbolu w pixelach.
 * \param penSize: Domyślna grubość pędzla.
 */
Painter::Painter(float cellSize, float penSize)
    :cellSize_{cellSize},
    penSize_{penSize},
    verticalLineX_{CONTACT_V_LINE_X_FACTORY * cellSize},
    verticalLineHeight_{CONTACT_V_LINE_HEIGHT_FACTORY * cellSize},
    coilArcAngle_{COIL_ARC_ANGLE},
    coilArcRadius_{COIL_ARC_RADIOUS_FACTORY * cellSize},
    coilArcOffsetX_{COIL_ARC_OFFSET_FACTORY * cellSize}
{
}

/*!
 * \brief Funkcja odpowiedzialna za rysowanie styku.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void Painter::drawContact(QPainter &painter)
{
    painter.setPen(QPen(Qt::white, penSize_));
    drawContactContour(painter);
}

/*!
 * \brief Funkcja odpowiedzialna za rysowanie cewki.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void Painter::drawCoil(QPainter &painter)
{
    painter.setPen(QPen(Qt::white, penSize_));
    drawCoilContour(painter);
}

/*!
 * \brief Funkcja rysująca sam styk.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void Painter::drawContactContour(QPainter &painter)
{
    drawVerticalPairLine(painter, verticalLineX_, verticalLineHeight_);
    drawHorizontalPairLine(painter, verticalLineX_);
}

/*!
 * \brief Funkcja rysująca samą cewkę.
 * \param painter: Referencja do klasy
 * <a href="https://doc.qt.io/qt-5/qpainter.html">QPainter</a>.
 */
void Painter::drawCoilContour(QPainter &painter)
{
    drawPairArc(painter, coilArcAngle_, coilArcRadius_, coilArcOffsetX_);
    drawHorizontalPairLine(painter,
                cellSize_ / 2 - coilArcRadius_ + coilArcOffsetX_);
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
void Painter::drawVerticalPairLine(QPainter &painter, float x, float height)
{
    drawVerticalLine(painter, x, height);
    drawVerticalLine(painter, cellSize_ - x, height);
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
void Painter::drawVerticalLine(QPainter &painter, float x, float height)
{
    painter.drawLine(x, cellSize_ / 2 - height / 2,
                     x, cellSize_ / 2 + height / 2);
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
void Painter::drawHorizontalPairLine(QPainter &painter, float x)
{
    painter.drawLine(0, cellSize_ / 2, x, cellSize_ / 2);
    painter.drawLine(cellSize_ - x, cellSize_ / 2,
                     cellSize_,     cellSize_ / 2);
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
void Painter::drawPairArc(QPainter &painter, float angle, float radius, float offsetX)
{
    painter.drawArc(getCenteredRect(radius * 2, radius * 2, offsetX), (-angle/2 + 180) * 16, angle * 16);
    painter.drawArc(getCenteredRect(radius * 2, radius * 2, -offsetX), (-angle/2) * 16, angle * 16);
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
QRectF Painter::getCenteredRect(float width, float height, float offsetX, float offsetY)
{
    float halfDifferenceWidth = (cellSize_ - width) / 2;
    float halfDifferenceHeight = (cellSize_ - height) / 2;
    return QRectF{halfDifferenceWidth + offsetX, halfDifferenceHeight + offsetY, width, height};
}


} //namespace Ld

