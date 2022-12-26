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

private:
    void addNewNetwork();
    void updateHeight(int nr, int height);

    QVector<Network*> networks_;
};

#endif // NETWORKLIST_HPP
