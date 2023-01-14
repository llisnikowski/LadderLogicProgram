#ifndef PROPERTYBAR_HPP
#define PROPERTYBAR_HPP

#include <QQuickItem>
#include <QVector>

namespace Ld {
class Base;
} // namespace Ld


class PropertiesList : public QQuickItem
{
    Q_OBJECT
public:
    explicit PropertiesList(QQuickItem *parent = nullptr);
    ~PropertiesList();

    void display(Ld::Base *item);
    void clear();

public slots:
    void setContainerParent(QQuickItem *parent);

private:
    void displayProperties();
    void clearPropertiesList();
    QQuickItem *createQQuickItem(const QString &filename,
                                 QVariantMap initProperties = {});

signals:
    void addPropertyItem(QQuickItem*);
    void clearPropertyItems();

private:
    Ld::Base *item_;
    QQuickItem *container_;
    QVector<QQuickItem*> propertiesList_;
};

#endif // PROPERTYBAR_HPP
