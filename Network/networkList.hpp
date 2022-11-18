#ifndef NETWORKLIST_HPP
#define NETWORKLIST_HPP

#include <QQuickItem>
#include <QVector>
#include "network.hpp"
#include "factoryContainer.hpp"


namespace Ld{
class Factory;
}

class NetworkList : public QQuickItem, public Ld::FactoryContainer
{
    Q_OBJECT
public:
    explicit NetworkList(QQuickItem *parent = nullptr);

public slots:
    void joinToParent(QQuickItem *parent);

protected:
    void changedFactory() override;

private:
    QVector<Network*> networks_;
};

#endif // NETWORKLIST_HPP
