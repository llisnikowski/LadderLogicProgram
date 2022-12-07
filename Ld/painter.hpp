/*!
 * \file lPainter.hpp
 * \author Łukasz Liśnikowski
*/
#ifndef LDPAINTER_H
#define LDPAINTER_H

#include <QObject>
#include <QQmlEngine>
#include <QSizeF>

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
    enum flags{
        noFlags = 0x00,
        dropping = 0x01,
        select = 0x02,
    };


    Painter(float penSize);

    /*!
     * \brief Zwraca grubość pędzla.
     * \return Grubość pędzla w pixelach.
     */
    float getPenSize() const {return penSize_;}

    void drawContact(QPainter *painter, QSizeF objectSize, int flags = noFlags);
    void drawCoil(QPainter *painter, QSizeF objectSize, int flags = noFlags);
    void drawLine(QPainter *painter, QSizeF objectSize, int flags = noFlags);
    void drawNode(QPainter *painter, QSizeF objectSize, int flags = noFlags);

private:
    void drawFlags(QPainter &painter, int flags);
    void drawContactContour(QPainter &painter);
    void drawCoilContour(QPainter &painter);
    void drawVerticalPairLine(QPainter &painter, float x, float height);
    void drawVerticalLine(QPainter &painter, float x, float height);
    void drawVerticalLine(QPainter &painter);
    void drawHorizontalPairLine(QPainter &painter, float x);
    void drawPairArc(QPainter &painter, float angle, float radiusX, float offsetX = 0);
    QRectF getCenteredRect(float width, float height, float offsetX = 0, float offsetY = 0);
    void drawHoryzontalLine(QPainter &painter);
    void drawDrop(QPainter &painter);
    void drawSelect(QPainter &painter);


    /*!
     * \brief Ddomyślną szerokość symbolów w pixelach.
     */
    QSizeF objectSize_;
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
    float verticalLineX_;
    float verticalLineHeight_;
    float coilArcAngle_;
    float coilArcRadius_;
    float coilArcOffsetX_;
    /*! @} */
};



} // namespace Ld

#endif // LDPAINTER_H
