#ifndef PICBUTTON_H
#define PICBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QEvent>

class PicButton : public QPushButton
{
    Q_OBJECT
public:
    PicButton(QWidget *parent = nullptr);
    void setIcons(const QString& normal,const QString& hover,const QString& pressed);

protected:
    bool event(QEvent *e) override;

private:
    void setNormalIcon();
    void setHoverIcon();
    void setPressedIcon();
    QString _normal;
    QString _hover;
    QString _pressed;
};

#endif // PICBUTTON_H
