#ifndef DRAGPDATA_HPP
#define DRAGPDATA_HPP

#include <QObject>

namespace Ld {
class Base;

class DragData : public QObject
{
    Q_OBJECT
public:
    explicit DragData(QObject *parent = nullptr);

    virtual void doAction(Qt::DropAction action) = 0;

    virtual QByteArray getData() const = 0;
    virtual bool setData(const QByteArray & data) = 0;
    virtual void setLd(const Ld::Base &comp){};

};


} // namespace Ld

#endif // DRAGANDDROPDATA_HPP