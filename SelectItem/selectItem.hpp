#ifndef SELECTITEM_HPP
#define SELECTITEM_HPP

#include <QObject>

namespace Ld{
class Base;
} // namespace Ld


class SelectItem : public QObject
{
    Q_OBJECT
public:
    explicit SelectItem(QObject *parent = nullptr);

    void addItemToList(Ld::Base *item);
    void removeItemFromList(Ld::Base *item);
    void setItem(Ld::Base *item);

    Ld::Base *getSelectedItem();

public slots:
    void resetItem();

signals:
    void changedSelectItem(Ld::Base*);

private:
    Ld::Base *selectedItem_;

};

#endif // SELECTITEM_HPP
