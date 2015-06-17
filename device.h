#ifndef DEVICE_H
#define DEVICE_H

#include "field.h"
#include "property.h"
#include "const.h"
#include "link.h"
#include <QImage>
#include <GL/gl.h>

class Field;

template <typename T>
        inline T lengthXY(const T& x1,const T& y1,const T& x2,const T& y2)
{
    //Вычисляет длину линии по координатам
    return  (sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1)));
}

  // GLfloat y11 = y1+(y2-y1)*R1/theLength;

template <typename T>
        inline T xy (const T& x,const T& x1,const T& R,const T& length)
{
    //  Вычисляет координату на линии c радиусом R
    return  (x+(x1-x)*R/length);
}

template <typename T1,typename T2>
        inline bool drawCircle (const T1& x,const T1& y,const T2& R,const T2& points)
{

    //  Вычисляет координату на линии c радиусом R
        GLfloat angle;
        glBegin(GL_POLYGON);
        for (int i=0;i<points;i++)
        {
            angle = 2*3.14*i/points;
            glVertex2f(x+R*cos(angle),y+R*sin(angle));
        }
        glEnd();

    return 0;
}

template <typename T>
        inline void func (const T& x)
{
    //  Вычисляет координату на линии c радиусом R
    x+1;

}
class Link;
// класс элемента на графической мнемосхеме

class Device//: public Field
{

    // Q_OBJECT

private:
    const DeviceType d_type;
    QList <Link *> links;
    bool eventFilter(QObject * obj, QEvent * evnt);

protected:

    Field * parent; // рабочее поле

    int X,Y; //координаты на мнемосхеме


    //int dxk1,dyk1; //координаты точки
    //typedef T *center;

    //int numberLinks;

    QString Name;
    QString ipaddr;

    int H,W; //высота и ширина на мнемосхеме

    QImage pixx,PIXX; // условный знак

    GLfloat R1,G1,B1;
    GLfloat R2,G2,B2;

    GLfloat R1S,G1S,B1S;
    GLfloat R2S,G2S,B2S;
    GLfloat R1L,G1L,B1L;
    //int link;

    //int X,Y; // координаты на мнемосхеме
    /* int heigth,width; // высота и ширина на мнемосхеме*/
    int linewidth; // толщина линии

    /*
    QString name;
    QString ip_addr;//QURL
    QString comment;
    */

public:
    Device(Field *work_field,int tmpX, int tmpY/*GLfloat tmpX, GLfloat tmpY*/,QString image, QString myName);
    //Device(Field *work_field,int tmpX, int tmpY,DeviceType type);
    Device(Field *work_field,int tmpX, int tmpY,DeviceType type ,QString d_name, QString d_ipaddr);


    virtual ~Device();
    const DeviceType getDeviceType() const;

    bool isSel;//ОПХГМЮЙ БШДЕКЕМХЪ ЙНЛОНМЕМРЮ

    int lineWigth() const;
    void setLineWigth(int lw);
    Property * edit;
    /*
    bool isSelected;
    bool isActive;

    //устанавливает и возвращает размер
    virtual void resize(int w, int h);
    virtual int getWidth();
    virtual int getHeigth();

    //устанавливает координаты внитри блока мнемосхемы
    */
    virtual void move(int x, int y);

    int link;
    virtual int x() const;
    //virtual int getx();
    virtual int y() const;
    QString getName() const;
    QString getIpaddr() const;

    virtual int width() const;
    virtual int height() const;
    /*
    //устанавливает и возвращает толщину линии
    virtual line_width;
    virtual void setLineWidth(int line_width);

    //устанавливает и возвращает условный знак
    virtual void setPix(QImage &px);
    virtual QImage pix();
    */
    virtual void setIsSelected(bool fl);
    virtual bool getIsSelected();

    virtual void contextMenuEvent(QContextMenuEvent *e);
    virtual void mousePressEvent(QMouseEvent *event);

    virtual void setPix(QImage &px);
    virtual QImage pix() const;
    virtual void paint();
    void appendLink(Link * newLink);
    Link * getLink(int num) const;


};




#endif // DEVICE_H
