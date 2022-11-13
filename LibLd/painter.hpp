/*!
 * \file ldPainter.hpp
 * \author Łukasz Liśnikowski
*/
#ifndef LDPAINTER_H
#define LDPAINTER_H

#include <QObject>
#include <QQmlEngine>

/*!
 * \defgroup GlobalParameters Globalne parametry rysowania
 * \brief Parametry rysowania dla całej klasy.
 * \see LocalParameters
 * @{
 */
constexpr float CONTACT_V_LINE_X_FACTORY {0.35};
constexpr float CONTACT_VL_LINE_HEIGHT_FACTORY {0.25};
constexpr float CONTACT_V_LINE_HEIGHT_FACTORY {0.25};
constexpr float COIL_ARC_ANGLE {90};
constexpr float COIL_ARC_RADIOUS_FACTORY {0.2};
constexpr float COIL_ARC_OFFSET_FACTORY {0.02};
/*! @} */


class QPainter;

namespace Ld {

/*!
 * \brief LdPainter jest klasą odpowiedzialną za rysowanie symboli Ld.
 */
class Painter : public QObject
{
    QML_ELEMENT
public:
    Painter(float cellSize, float penSize);

    /*!
     * \brief Zwraca domyślną szerokość symbolów.
     * \return Szerokość symbolów w pixelach.
     */
    float getCellSize() const {return cellSize_;}
    /*!
     * \brief Zwraca grubość pędzla.
     * \return Grubość pędzla w pixelach.
     */
    float getPenSize() const {return penSize_;}

    void drawContact(QPainter &painter);
    void drawCoil(QPainter &painter);

private:
    void drawContactContour(QPainter &painter);
    void drawCoilContour(QPainter &painter);
    void drawVerticalPairLine(QPainter &painter, float x, float height);
    void drawVerticalLine(QPainter &painter, float x, float height);
    void drawHorizontalPairLine(QPainter &painter, float x);
    void drawPairArc(QPainter &painter, float angle, float radiusX, float offsetX = 0);
    QRectF getCenteredRect(float width, float height, float offsetX = 0, float offsetY = 0);

    /*!
     * \brief Ddomyślną szerokość symbolów w pixelach.
     */
    float cellSize_;
    /*!
     * \brief Grubość pędzla w pixelach.
     */
    float penSize_;

    /*!
     * \defgroup LocalParameters Lokalne parametry rysowania
     * \brief Parametry rysowania dla konkrotnego obiktu klasy LdPainter.
     *
     * Oblicone na podstawie wymiarów symboli w momencie wywołania konstruktora.
     * \see GlobalParameters
     * @{
     */
    const float verticalLineX_;
    const float verticalLineHeight_;
    const float coilArcAngle_;
    const float coilArcRadius_;
    const float coilArcOffsetX_;
    /*! @} */
};



} // namespace Ld

#endif // LDPAINTER_H
