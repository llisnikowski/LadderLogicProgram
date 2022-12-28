#ifndef LOGINTERFACE_HPP
#define LOGINTERFACE_HPP

#include <QObject>
#include <QString>

class LogInterface
{
public:
    virtual ~LogInterface() = default;

    virtual void addToLogs(QString message) = 0;
};

#endif // LOGINTERFEJS_HPP
