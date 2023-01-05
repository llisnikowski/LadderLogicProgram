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
    ~NetworkList();

    void clearList();

    Network *getNetwork(int i);
    Network *operator[](int i);
    int count() const;

    void addNewNetwork();

    friend QDataStream &operator<<(QDataStream &stream, NetworkList &networkList);
    friend QDataStream &operator>>(QDataStream &stream, NetworkList &networkList);

private:
    void updateHeight(int nr);

    QVector<Network*> networks_;
};


QDataStream &operator<<(QDataStream &stream, NetworkList &networkList);
QDataStream &operator>>(QDataStream &stream, NetworkList &networkList);

#endif // NETWORKLIST_HPP
