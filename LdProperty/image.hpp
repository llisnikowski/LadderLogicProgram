#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <base.hpp>
#include <QUrl>

namespace LdProperty {

class Image : public Base
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ getUrl WRITE setUrl NOTIFY urlChanged)
public:
    Image(QQuickItem *parent = nullptr);
    Image &operator=(const Image &image);

    QUrl getUrl() const;
    void setUrl(QUrl url);

signals:
    void urlChanged();

protected:
    QUrl url_;
};

} // namespace LdProperty



QDataStream & operator<<(QDataStream &stream, const LdProperty::Image &image);
QDataStream & operator>>(QDataStream &stream, LdProperty::Image &image);


#endif // IMAGE_HPP
