/*!
 * \file factoryContainer.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/
#ifndef FACTORYCONTAINER_HPP
#define FACTORYCONTAINER_HPP

namespace Ld{

class Factory;

/*!
 * \brief FactoryContainer to klasa przechowująca wskaźnik do obiektu klasy
 * Factory.
 *
 * Głównym przeznaczeniem klasy jest bycie klasą bazową dla innych klas.
 */
class FactoryContainer
{
public:
    FactoryContainer();
    /*!
    * \brief Domyślny destruktor klasy FactoryContainer.
    */
    virtual ~FactoryContainer() = default;

    void setFactory(Factory *factory);
    Factory *getFactory();

protected:
    virtual void changedFactory();
    /*!
     * \brief Wskaźnik na klasę Factory.
     */
    Factory *factory_;
};

} // namespace Ld

#endif // FACTORYCONTAINER_HPP
