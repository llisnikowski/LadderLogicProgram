#ifndef DROPVALIDATOR_HPP
#define DROPVALIDATOR_HPP

#include <QObject>

namespace Ld {

/*!
 * \brief Klasa DropValidator jest klasą abstrakcyjną udostępniającą interfejs
 * dla klas będących obszarem przeciągania w mechnizmie
 * <a href="https://doc.qt.io/qt-6/dnd.html">
 *  Drag and Drop</a>.
 *
 *  \see DragData
 */
class DropValidator : public QObject
{
public:
    explicit DropValidator(QObject *parent = nullptr);

    /*!
     * \brief Funkcja sprawdzająca rezultat przeciągniecia obiektu.
     * \param dragArrayData: Dane przeciąganego obiektu.
     */
    virtual Qt::DropAction valid(const QByteArray &dragArrayData) = 0;
    /*!
     * \brief Funkcja wykonująca czynności po przeciągnieciu obiektu.
     * \param dragArrayData: Dane przeciąganiętego obiektu.
     */
    virtual void doAction(const QByteArray &dragArrayData) = 0;
};


} // namespace Ld

#endif // DROPVALIDATOR_HPP
