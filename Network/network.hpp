#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "containerLd.hpp"
#include <QQuickItem>

namespace Ld{
class Factory;
}

class Network : public QQuickItem
{
    Q_OBJECT
public:
    explicit Network(int nr);
    Network(QQuickItem *parent = nullptr, int nr = 0);
    ~Network() = default;
    void setFactory(Ld::Factory *factory);
    Ld::Factory *getFactory();

    int getNr() const {return nr_;}

public slots:

private:
    int nr_;
    ContainerLd containerLd_;
    Ld::Factory * factory_;
};

#endif // NETWORK_HPP
