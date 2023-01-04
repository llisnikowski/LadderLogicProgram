#ifndef DRAGPDATA_HPP
#define DRAGPDATA_HPP

#include <QObject>

namespace Ld {
class Base;

/*!
 * \brief Klasa DragData jest klasą abstrakcyjną udostępniającą interfejs
 * dla klas przechowujących dane dla obiektów przenoszonych mechnizmem
 * <a href="https://doc.qt.io/qt-6/dnd.html">
 *  Drag and Drop</a>.
 *
 *  \see DropValidator
 */
class DragData : public QObject
{
    Q_OBJECT
public:
    explicit DragData(QObject *parent = nullptr);

    /*!
     * \brief Funkcja wykonująca czynności po przeciągnieciu obiektu.
     * \param action: Rezultat przeciągnięcia.
     */
    virtual void doAction(Qt::DropAction action) = 0;

    /*!
     * \brief Funkcja generująca i zwracająca dane przeciąganego obiektu.
     */
    virtual QByteArray getData() const = 0;
    /*!
     * \brief Funkcja odtwarzająca obiekt za pomocą tablicy bajtów.
     */
    virtual bool setData(const QByteArray & data) = 0;
    /*!
     * \brief Funkcja ustawiająca obiekt Ld.
     */
    virtual void setLd(const Ld::Base &){};

};


} // namespace Ld

#endif // DRAGANDDROPDATA_HPP
