#ifndef DRAGNETWORKDATA_HPP
#define DRAGNETWORKDATA_HPP

#include "dragData.hpp"
#include "position.hpp"

class ContainerLd;
namespace Ld {
class Base;
} // namespace Ld


class DragNetworkData : public Ld::DragData
{
public:
    explicit DragNetworkData(QObject *parent = nullptr);
    explicit DragNetworkData(QObject *parent, QByteArray comp,
                             int id, Position position);
    explicit DragNetworkData(QObject *parent, QByteArray comp,
                             ContainerLd *containerLd,
                             Position position);

    void doAction(Qt::DropAction action) override;

    QByteArray getData() const override;
    bool setData(const QByteArray & data) override;

    void setLd(const Ld::Base &comp) override;
    Ld::Base *getLdObj() const;
    QByteArray getLd() const;
    int getId() const;
    void setId(int id);
    Position getPosition() const;
    void setPosition(Position position);
    void setContainer(ContainerLd *containerLd);

private:
    QByteArray comp_;
    ContainerLd *containerLd_;
    int id_;
    Position position_;
};

#endif // DRAGNETWORKDATA_HPP
