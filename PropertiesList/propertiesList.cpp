#include "propertiesList.hpp"
#include "Ld/base.hpp"
#include "comboboxField.hpp"
#include "multitextfield.hpp"
#include "textField.hpp"
#include "textWithComboboxField.hpp"
#include "daysOfWeekField.hpp"
#include <QQmlEngine>

PropertiesList::PropertiesList(QObject *parent)
    : QObject{parent}, item_{}, container_{}, propertiesList_{}
{
}

PropertiesList::~PropertiesList()
{
    clearPropertiesList();
}

void PropertiesList::display(Ld::Base *item)
{
    if(!container_) return;
    clear();
    if(item){
        item_ = item;
        QObject::connect(item, &QObject::destroyed, this,
                         &PropertiesList::clear);
        displayProperties();
    }
}

void PropertiesList::clear()
{
    clearPropertiesList();
    if(item_){
        QObject::disconnect(item_, nullptr, this, nullptr);
        item_ = nullptr;
    }
}

void PropertiesList::setContainerParent(QQuickItem *parent)
{
    if(container_){
        delete container_;
        container_ = nullptr;
    }
    container_ = createQQuickItem("qrc:/PropertiesList.qml",
                                  {{"rootModel", QVariant::fromValue(this)}});
    if(container_){
        container_->setParentItem(parent);
    }
}


void PropertiesList::displayProperties()
{
    if(!container_) return;
    clearPropertiesList();

    auto list = item_->getPropertiesList();
    for(auto property : list){
        if(qobject_cast<LdProperty::TextWithComboboxField*>(property)){
            auto obj = createQQuickItem("qrc:/textWithComboboxFieldProperty.qml",
                        {{"rootModel", QVariant::fromValue(property)}});
            propertiesList_.append(obj);
            emit addPropertyItem(obj);
        }
        else if(qobject_cast<LdProperty::TextField*>(property)){
            auto obj = createQQuickItem("qrc:/textFieldProperty.qml",
                        {{"rootModel", QVariant::fromValue(property)}});
            propertiesList_.append(obj);
            emit addPropertyItem(obj);
        }
        else if(qobject_cast<LdProperty::ComboboxField*>(property)){
            auto obj = createQQuickItem("qrc:/comboboxProperty.qml",
                        {{"rootModel", QVariant::fromValue(property)}});
            propertiesList_.append(obj);
            emit addPropertyItem(obj);
        }
        else if(qobject_cast<LdProperty::DaysOfWeekField*>(property)){
            auto obj = createQQuickItem("qrc:/daysOfWeekFieldProperty.qml",
                        {{"rootModel", QVariant::fromValue(property)}});
            propertiesList_.append(obj);
            emit addPropertyItem(obj);
        }
        else if(qobject_cast<LdProperty::MultitextField*>(property)){
            auto obj = createQQuickItem("qrc:/multitextFieldProperty.qml",
                        {{"rootModel", QVariant::fromValue(property)}});
            propertiesList_.append(obj);
            emit addPropertyItem(obj);
        }
    }
}

void PropertiesList::clearPropertiesList()
{
    for(auto property : propertiesList_){
        if(property != nullptr)
            delete property;
    }
    propertiesList_.clear();
}

QQuickItem *PropertiesList::createQQuickItem(const QString &name,
                                             QVariantMap initProperties)
{
    if(QCoreApplication::startingUp()) return nullptr;

    QQmlEngine *engine = new QQmlEngine{this};
    QQmlComponent component(engine, QUrl(name),
                            QQmlComponent::PreferSynchronous, this);
    QQuickItem *qmlObject = qobject_cast<QQuickItem *>
                    (component.createWithInitialProperties(initProperties));
    if(qmlObject){
        qmlObject->setParentItem(container_);
    }
    return qmlObject;
}
