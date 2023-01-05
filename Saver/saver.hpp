#ifndef SAVER_HPP
#define SAVER_HPP

#include "networkList.hpp"
#include <QObject>

class Saver : public QObject
{
    Q_OBJECT
public:
    explicit Saver(QObject *parent = nullptr);

    bool save();
    bool load();

    void setFile(QString filename);
    void setNetworkList(NetworkList *networkList);

signals:

private:
    QString fileName_;
    NetworkList *networkList_;
};

#endif // SAVER_HPP
