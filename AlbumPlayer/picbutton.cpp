#include "picbutton.h"

PicButton::PicButton(QWidget *parent):
    QPushButton(parent)
{

}

void PicButton::setIcons(const QString &normal, const QString &hover, const QString &pressed)
{
    _normal = normal;
    _hover = hover;
    _pressed = pressed;

    QPixmap tmpPixmap;
    tmpPixmap.load(normal);
    this->resize(tmpPixmap.size());
    this->setIcon(tmpPixmap);
    this->setIconSize(tmpPixmap.size());
}

bool PicButton::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::Enter:
        setHoverIcon();
        break;
    case QEvent::Leave:
        setNormalIcon();
        break;
    case QEvent::MouseButtonPress:
        setPressedIcon();
        break;
    case QEvent::MouseButtonRelease:
        setHoverIcon();
        break;
    default:
        break;
    }

    return QPushButton::event(e);
}

void PicButton::setNormalIcon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_normal);
    this->setIcon(tmpPixmap);
}

void PicButton::setHoverIcon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_hover);
    this->setIcon(tmpPixmap);
}

void PicButton::setPressedIcon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_pressed);
    this->setIcon(tmpPixmap);
}
