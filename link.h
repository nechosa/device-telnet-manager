#ifndef LINK_H
#define LINK_H

#include "device.h"

class Link
{
protected:
    GLfloat R1,G1,B1;//цвет градиентной заливки
    GLfloat R2,G2,B2;
    GLfloat R1S,G1S,B1S;//цвет градиентной заливки (при выделении)
    GLfloat R2S,G2S,B2S;

private:
    //имя и тип
    QString name;
    int type;
    //толщина линии
    int LineWidth;

public:

    bool isSel;//признак выделения компонента

    //начало и окончание связи
    Device * begining;
    Device * ending;

    //конструктор и деструктор класса
    Link(Device * first, Device * last, QString theName, int theType, int theWidth);
    virtual ~Link();

    //устанавливает и возвращает цвет
    virtual void setColor(int r1, int g1, int b1,int r2 = 255, int g2 = 255, int b2 = 255);
    virtual void getColor(int &r1, int &g1,int &b1, int &r2,int &g2,int &b2)  ;
    virtual void setColorSelected(int r1, int g1, int b1,int r2 = 255, int g2 = 255, int b2 = 255);
    virtual void getColorSelected(int &r1, int &g1,int &b1, int &r2,int &g2,int &b2)  ;


    //устанавливает и возвращает признак выделения
    virtual void setIsSelected(bool fl);
    virtual bool isSelected()  ;

    //рисование линии связи
    virtual void paint(int aniStep);

    //возвращает область в центре, которую можно использовать для выделения связи
    virtual QRect getCentralArea();

    //установка признака активности
    void SetActive(bool activ);

    //устанавливает имя и тип
    void setName(QString n);
    void setType(int t);

    //возвращает имя и тип
    QString getName();
    int getType();

    //установка и возврат толщины линии
    void setWidth(int w);
    int getWidth();
};

#endif // LINK_H
