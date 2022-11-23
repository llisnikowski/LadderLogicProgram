#ifndef DROPNETWORKVALIDATOR_HPP
#define DROPNETWORKVALIDATOR_HPP

#include "containerLd.hpp"
#include "dropValidator.hpp"
#include <QPoint>

class Network;

class DropNetworkValidator : public Ld::DropValidator
{
public:
    explicit DropNetworkValidator(QObject *parent = nullptr);

    Qt::DropAction valid(const QByteArray & dragArrayData) override;

    const ContainerLd *getContainer() const;
    void setContainer(const ContainerLd *containerLd);
    QPoint getPosition() const;
    void setPosition(QPoint position);

private:
    const ContainerLd *containerLd_;
    QPoint position_;

};

#endif // DNDNETWORKDATA_HPP
