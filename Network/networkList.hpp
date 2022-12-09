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

public slots:
    void joinToParent(QQuickItem *parent);
    void addNewNetwork(ContainerLd *container);
    void updateHeight(int nr, int height);

private:
    QVector<Network*> networks_;
};

#endif // NETWORKLIST_HPP
