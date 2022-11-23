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

    QByteArray getData() const override;
    void setData(const QByteArray & data) override;

    QByteArray getLd() const;
    void setLd(const Ld::Base &comp);
    int getNetworkId() const;
    void setNetworkId(int id);
    QPoint getPosition() const;
    void setPosition(QPoint position);

private:
    QByteArray comp_;
    int networkId_;
    QPoint position_;
};

#endif // DRAGNETWORKDATA_HPP
