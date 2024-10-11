#ifndef PICSTATEBUTTON_H
#define PICSTATEBUTTON_H

#include <QPushButton>

class PicStateButton : public QPushButton
{
    Q_OBJECT
public:
    PicStateButton(QWidget* parent = nullptr);
    void setIcons(const QString& normal,const QString& hover,const QString& pressed,
                  const QString& normal_2,const QString& hover_2,const QString& pressed_2);

protected:
    bool event(QEvent* e) override;

private:
    QString _normal;
    QString _normal_2;
    QString _hover;
    QString _hover_2;
    QString _pressed;
    QString _pressed_2;
    int _curState;
    void setNormalIcon();
    void setHoverIcon();
    void setPressedIcon();

    void setNormal2Icon();
    void setHover2Icon();
    void setPressed2Icon();

public slots:
    void slotStart();
    void slotStop();
};

#endif // PICSTATEBUTTON_H
