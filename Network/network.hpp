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

    void setNr(int nr) {nr_ = nr;}
    int getNr() const {return nr_;}
    ContainerLd &getContainerLd(){return containerLd_;}

public slots:
    void updateHeight();

protected:
    void changedFactory() override;

signals:
    void changedHeight(int nr, int height);

private:
    int nr_;
    ContainerLd containerLd_;
};

#endif // NETWORK_HPP
