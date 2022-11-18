#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <QQuickItem>
#include "containerLd.hpp"
#include "factoryContainer.hpp"



class Network : public QQuickItem, public Ld::FactoryContainer
{
    Q_OBJECT
public:
    explicit Network(int nr);
    Network(QQuickItem *parent = nullptr, int nr = 0);
    ~Network() = default;

    int getNr() const {return nr_;}

protected:
    void changedFactory() override;

private:
    int nr_;
    ContainerLd containerLd_;
};

#endif // NETWORK_HPP
