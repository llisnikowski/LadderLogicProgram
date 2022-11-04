#ifndef COMPONENTLD_HPP
#define COMPONENTLD_HPP

#include <QQuickPaintedItem>

namespace Ld{

class ComponentLd : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit ComponentLd(QQuickItem *parent = nullptr);

signals:

};

} // namespace Ld

#endif // COMPONENTLD_HPP
