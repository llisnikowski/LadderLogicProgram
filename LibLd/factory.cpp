/*!
 * \file factory.cpp
 * \author Łukasz Liśnikowski
*/
#include "factory.hpp"
#include "line.hpp"
#include "contact.hpp"
#include "coil.hpp"
#include "painter.hpp"

/*!
 * \brief Konstructor Klasy Factory.
 * \param parent: Rodzic/Element nadrzędny.
 */
Ld::Factory::Factory(QObject *parent)
    :QObject{parent}, objectSize_{}, painter_{}
{
}

/*!
 * \brief Ustawia domyślny rozmiar do nowo tworzonych obiektów.
 *
 * \param painter: Rozmiar objektów.
 */
void Ld::Factory::setObjectSize(float objectSize) {
    objectSize_ = objectSize;
}

/*!
 * \brief Ld::Factory::getObjectSize
 * \return
 */
float Ld::Factory::getObjectSize() const {
    return objectSize_;
}

/*!
 * \brief Ustawia klase Painter która będzie przypisana do nowo tworzonych obiektów.
 *
 * Ustwawie również zmienną objectSize_ na podstawie klasy Painter.
 * \param painter: Wskaźnik do klasy Painter.
 */
void Ld::Factory::setPainter(Painter *painter)
{
    painter_ = painter;
    if(painter_){
        objectSize_ = painter->getCellSize();
    }
}

/*!
 * \brief Zwraca klase Painter przypisywaną do obiektów.
 * \return Wskaźnik do używanej klasy LdPainter.
 */
Ld::Painter *Ld::Factory::getPainter() {
    return painter_;
}

/*!
 * \brief Alokuje klase Ld::Line i zwraca wskaźnik.
 * \param parent: Rodzic/Element nadrzędny dla tworzonego obiektu.
 * \return
 * \warning Jeśli nie podaliśmy rodzica jako agument funkcji
 * i nie ustawiliśmy mu go, po zakończeniu pracy z obiektem należy go usunąć.
 */
Ld::Line *Ld::Factory::createLine(QQuickItem *parent) const
{
    return initObject(new Ld::Line{parent});
}

/*!
 * \brief Alokuje klase Ld::Contact i zwraca wskaźnik.
 * \param parent: Rodzic/Element nadrzędny dla tworzonego obiektu.
 * \return
 * \warning Jeśli nie podaliśmy rodzica jako agument funkcji
 * i nie ustawiliśmy mu go, po zakończeniu pracy z obiektem należy go usunąć.
 */
Ld::Contact *Ld::Factory::createContact(QQuickItem *parent) const
{
    return initObject(new Ld::Contact{parent});
}

/*!
 * \brief Alokuje klase Ld::Coil i zwraca wskaźnik.
 * \param parent: Rodzic/Element nadrzędny dla tworzonego obiektu.
 * \return
 * \warning Jeśli nie podaliśmy rodzica jako agument funkcji
 * i nie ustawiliśmy mu go, po zakończeniu pracy z obiektem należy go usunąć.
 */
Ld::Coil *Ld::Factory::createCoil(QQuickItem *parent) const
{
    return initObject(new Ld::Coil{parent});
}

/*!
 * \brief Ustawia obiektowi właściwości wspólne dla wszystkich typów.
 * \tparam T: Typ obiektu.
 * \param obj: Obiekt.
 * \return Wskaźnik do wcześniej przekazanego obiektu.
 */
template <typename T>
T *Ld::Factory::initObject(T *obj) const
{
    obj->setSize({objectSize_, objectSize_});
    obj->setPainter(painter_);
    return obj;
}

