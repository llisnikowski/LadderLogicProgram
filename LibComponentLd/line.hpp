/*!
 * \file line.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/


#ifndef LINE_HPP
#define LINE_HPP

#include "componentLd.hpp"

namespace Ld {

/*!
 * \brief Klasa Coil udostępnia symbol linii z języka LD.
 */
class Line : public ComponentLd
{
    Q_OBJECT
public:
    explicit Line(QQuickItem *parent = nullptr);
};


} //namespace Ld

#endif // LINE_HPP
