#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <QQuickItem>
#include <QString>
#include "logInterface.hpp"

class ConsoleLog : public QQuickItem, public LogInterface
{
    Q_OBJECT
public:
    explicit ConsoleLog(QQuickItem *parent = nullptr);
    ~ConsoleLog();
    void addToLogs(QString message) override;

signals:
    void logTextChanged(QString text);

private:
    void Parent();
    void createQQuickItem();

    QQuickItem *qmlObject_;
};

#endif // CONSOLE_HPP
