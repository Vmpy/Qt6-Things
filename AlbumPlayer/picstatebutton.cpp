#include "picstatebutton.h"
#include "const.h"
#include <QEvent>

PicStateButton::PicStateButton(QWidget *parent):
    QPushButton(parent)
{

}

void PicStateButton::setIcons(const QString &normal, const QString &hover, const QString &pressed,
                              const QString &normal_2, const QString &hover_2, const QString &pressed_2)
{
    _normal = normal;
    _hover = hover;
    _pressed = pressed;
    _normal_2 = normal_2;
    _hover_2 = hover_2;
    _pressed_2 = pressed_2;

    QPixmap tmpPixmap;
    tmpPixmap.load(normal);
    this->resize(tmpPixmap.size());
    this->setIcon(tmpPixmap);
    this->setIconSize(tmpPixmap.size());
    _curState = PicBtnState::PicBtnStateNormal;
}

bool PicStateButton::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::Enter:
        if(_curState < PicBtnState::PicBtnState2Normal)
        {
            setHoverIcon();
        }
        else
        {
            setHover2Icon();
        }
        break;
    case QEvent::Leave:
        if(_curState < PicBtnState::PicBtnState2Normal)
        {
            setNormalIcon();
        }
        else
        {
            setNormal2Icon();
        }
        break;
    case QEvent::MouseButtonPress:
        if(_curState < PicBtnState::PicBtnState2Normal)
        {
            setPressedIcon();
        }
        else
        {
            setPressed2Icon();
        }
        break;
    case QEvent::MouseButtonRelease:
        if(_curState < PicBtnState::PicBtnState2Normal)
        {
            setHover2Icon();
        }
        else
        {
            setHoverIcon();
        }
        break;

    default:
        break;
    }

    return QPushButton::event(e);
}

void PicStateButton::setNormalIcon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_normal);
    this->setIcon(tmpPixmap);
    _curState = PicBtnState::PicBtnStateNormal;
}

void PicStateButton::setHoverIcon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_hover);
    this->setIcon(tmpPixmap);
    _curState = PicBtnState::PicBtnStateHover;
}

void PicStateButton::setPressedIcon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_pressed);
    this->setIcon(tmpPixmap);
    _curState = PicBtnState::PicBtnStatePressed;
}

void PicStateButton::setNormal2Icon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_normal_2);
    this->setIcon(tmpPixmap);
    _curState = PicBtnState::PicBtnState2Normal;
}

void PicStateButton::setHover2Icon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_hover_2);
    this->setIcon(tmpPixmap);
    _curState = PicBtnState::PicBtnState2Hover;
}

void PicStateButton::setPressed2Icon()
{
    QPixmap tmpPixmap;
    tmpPixmap.load(_pressed_2);
    this->setIcon(tmpPixmap);
    _curState = PicBtnState::PicBtnState2Pressed;
}

void PicStateButton::slotStart()
{
    setNormal2Icon();
}

void PicStateButton::slotStop()
{
    setNormalIcon();
}
