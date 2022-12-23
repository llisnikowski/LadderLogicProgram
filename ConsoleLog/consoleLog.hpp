#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <QQuickItem>
#include <QString>

class ConsoleLog : public QQuickItem
{
    Q_OBJECT
public:
    explicit ConsoleLog(QQuickItem *parent = nullptr);
    ~ConsoleLog();
    void addToLogs(QString message);

signals:
    void logTextChanged(QString text);

private:
    void Parent();
    void createQQuickItem();

    QQuickItem *qmlObject_;
};

#endif // CONSOLE_HPP
