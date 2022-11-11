/*!
 * \file symbolsBar.hpp
 * \author Łukasz Liśnikowski
*/
#ifndef SYMBOLSBAR_H
#define SYMBOLSBAR_H

#include <QQuickItem>

namespace Ld {
class LdPainter;

/*!
 * \brief SymbolsBar jest klasą odpowiedzialną za utworzenie paska z symbolami Ld.
 */
class SymbolsBar : public QQuickItem
{
    Q_OBJECT
public:
    SymbolsBar();
    void setLdPainter(LdPainter *ldPainter);
    LdPainter *getLdPainter();

public slots:
    void setNewParentItem(QQuickItem *parentItem);

private:
    LdPainter *ldPainter_;
};


} // namespace Ld

#endif // SYMBOLSBAR_H
