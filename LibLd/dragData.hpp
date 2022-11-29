#ifndef DRAGPDATA_HPP
#define DRAGPDATA_HPP

#include <QObject>

namespace Ld {


class DragData : public QObject
{
    Q_OBJECT
public:
    explicit DragData(QObject *parent = nullptr);

    virtual QByteArray getData() const = 0;
    virtual bool setData(const QByteArray & data) = 0;

};


} // namespace Ld

#endif // DRAGANDDROPDATA_HPP
