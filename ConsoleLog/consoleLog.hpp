#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <QQuickItem>
#include <QString>
#include "logInterface.hpp"

/*!
 * \brief ConsoleLog jest klasą udostępniającą okno konsoli.
 */
class ConsoleLog : public QQuickItem, public LogInterface
{
    Q_OBJECT
public:
    explicit ConsoleLog(QQuickItem *parent = nullptr);
    ~ConsoleLog();

public slots:
    void addToLogs(QString message) override;

signals:
    void logTextChanged(QString text);

private:
    void createQQuickItem();

    /*!
     * \brief qmlObject_ jest wskaźnikiem przechowującym graficzny
     * obiekt konsoli.
     */
    QQuickItem *qmlObject_;
};

#endif // CONSOLE_HPP
