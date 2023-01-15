#ifndef DROPNETWORKVALIDATOR_HPP
#define DROPNETWORKVALIDATOR_HPP

#include "containerLd.hpp"
#include "dropValidator.hpp"
#include "position.hpp"

class Network;

class DropNetworkValidator : public Ld::DropValidator
{
public:
    explicit DropNetworkValidator(QObject *parent = nullptr);
    DropNetworkValidator(QObject *parent, ContainerLd *container,
                                  Position position);

    Qt::DropAction valid(const QByteArray &dragArrayData) override;
    void doAction(const QByteArray &dragArrayData) override;

    const ContainerLd *getContainer() const;
    void setContainer(ContainerLd *containerLd);
    Position getPosition() const;
    void setPosition(Position position);

private:
    ContainerLd *containerLd_;
    Position position_;

};

#endif // DNDNETWORKDATA_HPP
