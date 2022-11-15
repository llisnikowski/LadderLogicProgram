#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "containerLd.hpp"
#include <QQuickItem>

class Network : public QQuickItem
{
    Q_OBJECT
public:
    explicit Network(int nr);
    Network(QQuickItem *parent = nullptr, int nr = 0);

    int getNr() const {return nr_;}

private:
    int nr_;
    ContainerLd containerLd_;
};

#endif // NETWORK_HPP
