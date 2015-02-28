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

// класс элемента на графической мнемосхеме
class Device//: public Field
{

   // Q_OBJECT


    bool eventFilter(QObject * obj, QEvent * evnt);

    protected:

   Field * parent; // рабочее поле

    int X,Y; //координаты на мнемосхеме
    QString Name;
    int H,W; //высота и ширина на мнемосхеме

    QImage pixx,PIXX; // условный знак

    GLfloat R1,G1,B1;
    GLfloat R2,G2,B2;

    GLfloat R1S,G1S,B1S;
    GLfloat R2S,G2S,B2S;
    GLfloat R1L,G1L,B1L;

    //int X,Y; // координаты на мнемосхеме
   /* int heigth,width; // высота и ширина на мнемосхеме
    int linewidth; // толщина линии
    */
/*
    QString name;
    QString ip_addr;//QURL
    QString comment;
    */

public:
    Device(Field *work_field,int tmpX, int tmpY/*GLfloat tmpX, GLfloat tmpY*/,QString image, QString myName);

    virtual ~Device();
    /*
    bool isSelected;
    bool isActive;

    //устанавливает и возвращает размер
    virtual void resize(int w, int h);
    virtual int getWidth();
    virtual int getHeigth();

    //устанавливает координаты внитри блока мнемосхемы
    virtual void move(int x, int y);
    */
      virtual int x();
      virtual int y();
       virtual QString getName();

    virtual int width();
    virtual int height();
/*
    //устанавливает и возвращает толщину линии
    virtual line_width;
    virtual void setLineWidth(int line_width);

    //устанавливает и возвращает условный знак
    virtual void setPix(QImage &px);
    virtual QImage pix();
    */

    virtual void contextMenuEvent(QContextMenuEvent *e);
    virtual void mousePressEvent(QMouseEvent *event);

    virtual void setPix(QImage &px);
    virtual QImage pix();
    virtual void paint();


};

#endif // DEVICE_H
