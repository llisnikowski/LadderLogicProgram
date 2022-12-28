#include "consoleLog.hpp"
#include <QDateTime>
#include <QQmlEngine>


ConsoleLog::ConsoleLog(QQuickItem *parent)
    :QQuickItem{parent}, LogInterface{}, qmlObject_{}
{
    if(parent){
        createQQuickItem();
    }
    connect(this, &QQuickItem::parentChanged, this, [this](){
        if(!this->parentItem()) return;
        createQQuickItem();
        qmlObject_->setSize(parentItem()->size());
        connect(this->parentItem(), &QQuickItem::widthChanged, [this](){
            qmlObject_->setWidth(this->parentItem()->width());
        });
        connect(this->parentItem(), &QQuickItem::heightChanged, [this](){
            qmlObject_->setHeight(this->parentItem()->height());
        });
    });
}

ConsoleLog::~ConsoleLog()
{
    if(qmlObject_){
        delete qmlObject_;
        qmlObject_ = nullptr;
    }
}


void ConsoleLog::addToLogs(QString message)
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
    emit logTextChanged(currentDateTime + "\t" + message + "\n");
 }

void ConsoleLog::createQQuickItem()
{
    if(QCoreApplication::startingUp()) return;

    if(qmlObject_){
        delete qmlObject_;
        qmlObject_ = nullptr;
    }

    QQmlEngine *engine = new QQmlEngine{this};
    QQmlComponent component(engine, QUrl("qrc:/ConsoleLog.qml"),
                            QQmlComponent::PreferSynchronous, this);
    qmlObject_ = qobject_cast<QQuickItem *>
        (component.createWithInitialProperties({{"rootModel", QVariant::fromValue(this)}}));
    if(qmlObject_){
        qmlObject_->setParentItem(this);
    }
}
