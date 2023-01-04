#ifndef LOGINTERFACE_HPP
#define LOGINTERFACE_HPP

#include <QObject>
#include <QString>

/*!
 * \brief LogInterface jest klasą udostępniającą interfejs dla wyświetlania tekstu.
 */
class LogInterface
{
public:
    virtual ~LogInterface() = default;

    /*!
     * \brief addToLogs jest metodą czysto wirtualną odbierającą tekst,
     *  udostępnioną przez interfejs.
     * \param message: tekst do wyświetlenia.
     */
    virtual void addToLogs(QString message) = 0;
};

#endif // LOGINTERFEJS_HPP
