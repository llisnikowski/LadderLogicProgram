/*!
 * \file lPainter.hpp
 * \author Łukasz Liśnikowski
*/
#ifndef LDPAINTER_H
#define LDPAINTER_H

#include <QObject>
#include <QQmlEngine>
#include <QSizeF>
#include <QColor>
#include <QPair>

/*!
 * \defgroup GlobalParameters Globalne parametry rysowania
 * \brief Parametry rysowania dla całej klasy.
 * \see LocalParameters
 * @{
 */
constexpr qreal CONTACT_V_LINE_X_FACTORY {0.35};
constexpr qreal CONTACT_VL_LINE_HEIGHT_FACTORY {0.25};
constexpr qreal CONTACT_V_LINE_HEIGHT_FACTORY {0.25};
constexpr qreal CONTACT_SLASH_OFFSET_X_FACTORY {0.07};
constexpr qreal CONTACT_SLASH_HEIGHT_FACTORY {0.16};
constexpr qreal COIL_ARC_ANGLE {90};
constexpr qreal COIL_ARC_RADIOUS_FACTORY {0.2};
constexpr qreal COIL_ARC_OFFSET_FACTORY {0.02};
constexpr int CENTER_LETTER_SIZE {16};
constexpr bool CENTER_LETTER_BOLD {true};
constexpr qreal CORRECT_CENTER_LETTER_OFFSET_X {0.0};
constexpr qreal CORRECT_CENTER_LETTER_OFFSET_Y {-2.0};
constexpr qreal NODE_POINT_SIZE_FACTORY {0.16};
/*! @} */


class QPainter;

namespace Ld {

/*!
 * \brief PainterLd jest klasą odpowiedzialną za rysowanie symboli Ld.
 */
class PainterLd : public QObject
{
    QML_ELEMENT
public:
    PainterLd(QPainter *painter, QSizeF objectSize);

    void drawContact();
    void drawContactSlash();
    void drawCoil();
    void drawLine();
    void drawLineStart();
    void drawLineEnd();
    void drawNode(bool left, bool right, bool top, bool bottom);

    void fillColor(QColor color = {0,0,0,40});
    void drawFrame(qreal frameWidth = 2);
    void printCenterLetter(QChar letter);

private:
    void drawContactContour();
    void drawCoilContour();
    void drawVerticalPairLine(float x, float height);
    void drawVerticalLine(float x, float height);
    void drawSlashLine(float x, float height);
    void drawVerticalLine();
    void drawHorizontalPairLine(float x);
    void drawPairArc(float angle, float radiusX, float offsetX = 0);
    QRectF getCenteredRect(float width, float height, float offsetX = 0, float offsetY = 0);
    void drawHoryzontalLine();
    void drawLineToMiddle(float x, float y);
    void drawPointInMiddle(float size);

    QPainter *painter_;
    QSizeF objectSize_;


    /*!
     * \defgroup LocalParameters Lokalne parametry rysowania
     * \brief Parametry rysowania dla konkrotnego obiktu klasy LdPainter.
     *
     * Oblicone na podstawie wymiarów symboli w momencie wywołania konstruktora.
     * \see GlobalParameters
     * @{
     */
    qreal verticalLineX_;
    qreal verticalLineHeight_;
    qreal contactSlashOffsetX_;
    qreal contactSlashHeight_;
    qreal coilArcAngle_;
    qreal coilArcRadius_;
    qreal coilArcOffsetX_;
    /*! @} */
};



} // namespace Ld

#endif // LDPAINTER_H
