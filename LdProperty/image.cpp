#include "image.hpp"


namespace LdProperty {

Image::Image(QQuickItem *parent)
    :Base{parent}, url_{}
{

}

Image &Image::operator=(const Image &image)
{
    if(this != &image){
        Base::operator=(image);
        setUrl(image.url_);
    }
    return *this;
}



QUrl Image::getUrl() const
{
    return url_;
}

void Image::setUrl(QUrl url)
{
    this->url_ = url;
    emit urlChanged();
}

} // namespace LdProperty



QDataStream &operator<<(QDataStream &stream, const LdProperty::Image &image)
{
    stream << static_cast<const LdProperty::Base&>(image) << image.getUrl();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, LdProperty::Image &image)
{
    QUrl value;
    stream >> static_cast<LdProperty::Base&>(image) >> value;
    image.setUrl(value);
    return stream;
}


