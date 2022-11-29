#ifndef DRAGNETWORKDATA_HPP
#define DRAGNETWORKDATA_HPP


#include "dragData.hpp"
#include <QPoint>

namespace Ld {
class Base;
} // namespace Ld


class DragNetworkData : public Ld::DragData
{
public:
    explicit DragNetworkData(QObject *parent = nullptr);
    explicit DragNetworkData(QObject *parent, QByteArray comp, int containerId,
                             QPoint position);

    QByteArray getData() const override;
    bool setData(const QByteArray & data) override;

    Ld::Base *getLdObj() const;
    QByteArray getLd() const;
    void setLd(const Ld::Base &comp);
    int getContainerId() const;
    void setContainerId(int id);
    QPoint getPosition() const;
    void setPosition(QPoint position);

private:
    QByteArray comp_;
    int containerId_;
    QPoint position_;
};

#endif // DRAGNETWORKDATA_HPP
