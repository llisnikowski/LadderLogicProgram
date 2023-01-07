#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <QQuickItem>
#include "containerLd.hpp"


class Network : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int nr READ getNr WRITE setNr NOTIFY nrChanged)
    Q_PROPERTY(QString desctiption READ getDesctiption WRITE setDesctiption NOTIFY desctiptionChanged)
public:
    explicit Network(int nr);
    Network(QQuickItem *parent = nullptr, int nr = 0);
    ~Network() = default;

    void setNr(int nr) {nr_ = nr; emit nrChanged();}
    int getNr() const {return nr_;}
    ContainerLd &getContainerLd(){return containerLd_;}
    void updateHeight();

    const QString &getDesctiption() const;
    void setDesctiption(const QString desc);

    friend QDataStream &operator<<(QDataStream &stream, Network &network);
    friend QDataStream &operator>>(QDataStream &stream, Network &network);

public slots:
    void triggerDeletion();

signals:
    void changedHeight(int nr, int height);
    void nrChanged();
    void deletionTriggering();
    void desctiptionChanged();

private:
    void createLabel();

    int nr_;
    ContainerLd containerLd_;
    QQuickItem *label_;
    QString description_;
};

QDataStream &operator<<(QDataStream &stream, Network &network);
QDataStream &operator>>(QDataStream &stream, Network &network);

#endif // NETWORK_HPP
