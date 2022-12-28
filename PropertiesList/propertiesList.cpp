#include "propertiesList.hpp"
#include "Ld/base.hpp"
#include "comboboxField.hpp"
#include "multitextfield.hpp"
#include "textField.hpp"
#include "textWithComboboxField.hpp"
#include "daysOfWeekField.hpp"
#include <QQmlEngine>

PropertiesList::PropertiesList(QQuickItem *parent)
    : QQuickItem{parent}, item_{}, qmlObject_{}, propertiesList_{}
{
     QObject::connect(this, &QQuickItem::parentChanged, this, [this](QQuickItem *parent){
        if(!parent) return;
        setParentItem(parent);
        setSize(parent->size());
        createQmlObject();
     });
}

PropertiesList::~PropertiesList()
{
    clearPropertiesList();
}


void PropertiesList::createQmlObject()
{
    if(qmlObject_){
        delete qmlObject_;
        qmlObject_ = nullptr;
    }
    qmlObject_ = createQQuickItem("qrc:/PropertyList.qml");
    if(qmlObject_){
        qmlObject_->setParentItem(this);
    }
}

void PropertiesList::display(Ld::Base *item)
{
    if(!qmlObject_) return;
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


void PropertiesList::displayProperties()
{
    if(!qmlObject_) return;
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
        qmlObject->setParentItem(this);
    }
    return qmlObject;
}
