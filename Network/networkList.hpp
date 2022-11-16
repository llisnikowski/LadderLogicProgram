#ifndef NETWORKLIST_HPP
#define NETWORKLIST_HPP

#include <QQuickItem>
#include <QVector>
#include "network.hpp"


namespace Ld{
class Factory;
}

class NetworkList : public QQuickItem
{
    Q_OBJECT
public:
    explicit NetworkList(QQuickItem *parent = nullptr);
    void setFactory(Ld::Factory *factory);
    Ld::Factory *getFactory();

public slots:
    void joinToParent(QQuickItem *parent);

private:
    QVector<Network*> networks_;
    Ld::Factory * factory_;
};

#endif // NETWORKLIST_HPP
