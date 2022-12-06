#ifndef DRAGNETWORKDATA_HPP
#define DRAGNETWORKDATA_HPP

#include "dragData.hpp"
#include <QPoint>

class ContainerLd;
namespace Ld {
class Base;
} // namespace Ld


class DragNetworkData : public Ld::DragData
{
public:
    explicit DragNetworkData(QObject *parent = nullptr);
    explicit DragNetworkData(QObject *parent, QByteArray comp,
                             int id, QPoint position);
    explicit DragNetworkData(QObject *parent, QByteArray comp,
                             ContainerLd *containerLd,
                             QPoint position);

    void doAction(Qt::DropAction action) override;

    QByteArray getData() const override;
    bool setData(const QByteArray & data) override;

    void setLd(const Ld::Base &comp) override;
    Ld::Base *getLdObj() const;
    QByteArray getLd() const;
    int getId() const;
    void setId(int id);
    QPoint getPosition() const;
    void setPosition(QPoint position);
    void setContainer(ContainerLd *containerLd);

private:
    QByteArray comp_;
    ContainerLd *containerLd_;
    int id_;
    QPoint position_;
};

#endif // DRAGNETWORKDATA_HPP
