#ifndef DEVICE_H
#define DEVICE_H

#include "field.h"
#include <QImage>
#include <GL/gl.h>

class Field;

enum EnumType
{
    Computer = 1,
    Router = 2
};

// ЛМБУУ ЬМЕНЕОФБ ОБ ЗТБЖЙЮЕУЛПК НОЕНПУИЕНЕ
class Device//: public Field
{

   // Q_OBJECT


    bool eventFilter(QObject * obj, QEvent * evnt);

    protected:

   Field * parent; // ТБВПЮЕЕ РПМЕ

    int X,Y; //ЛППТДЙОБФЩ ОБ НОЕНПУИЕНЕ
    QString Name;
    int H,W; //ЧЩУПФБ Й ЫЙТЙОБ ОБ НОЕНПУИЕНЕ

    QImage pixx,PIXX; // ХУМПЧОЩК ЪОБЛ

    GLfloat R1,G1,B1;
    GLfloat R2,G2,B2;

    GLfloat R1S,G1S,B1S;
    GLfloat R2S,G2S,B2S;
    GLfloat R1L,G1L,B1L;

    //int X,Y; // ЛППТДЙОБФЩ ОБ НОЕНПУИЕНЕ
   /* int heigth,width; // ЧЩУПФБ Й ЫЙТЙОБ ОБ НОЕНПУИЕНЕ
    int linewidth; // ФПМЭЙОБ МЙОЙЙ
    */
/*
    QString name;
    QString ip_addr;//QURL
    QString comment;
    */

public:
    Device(Field *work_field,int tmpX, int tmpY/*GLfloat tmpX, GLfloat tmpY*/,QString image, QString myName);

    virtual ~Device();
    bool isSel;//признак выделения компонента
    /*
    bool isSelected;
    bool isActive;

    //ХУФБОБЧМЙЧБЕФ Й ЧПЪЧТБЭБЕФ ТБЪНЕТ
    virtual void resize(int w, int h);
    virtual int getWidth();
    virtual int getHeigth();

    //ХУФБОБЧМЙЧБЕФ ЛППТДЙОБФЩ ЧОЙФТЙ ВМПЛБ НОЕНПУИЕНЩ
    */
    virtual void move(int x, int y);


      virtual int x();
      virtual int y();
       virtual QString getName();

    virtual int width();
    virtual int height();
/*
    //ХУФБОБЧМЙЧБЕФ Й ЧПЪЧТБЭБЕФ ФПМЭЙОХ МЙОЙЙ
    virtual line_width;
    virtual void setLineWidth(int line_width);

    //ХУФБОБЧМЙЧБЕФ Й ЧПЪЧТБЭБЕФ ХУМПЧОЩК ЪОБЛ
    virtual void setPix(QImage &px);
    virtual QImage pix();
    */
    virtual void setIsSelected(bool fl);
    virtual bool getIsSelected();

    virtual void contextMenuEvent(QContextMenuEvent *e);
    virtual void mousePressEvent(QMouseEvent *event);

    virtual void setPix(QImage &px);
    virtual QImage pix();
    virtual void paint();


};


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


    //устанавливает и возвращает признак выделени

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

#endif // DEVICE_H
