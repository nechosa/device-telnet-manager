#include "link.h"
#include "device.h"
#include <QDebug>


//--- Конструктор и деструктор класса ---
Link::Link(Field *work_field,Device * first, Device * last, QString theName,int theType,int theWidth,QString l_eth0,QString l_eth1,
         int x_eth0,int y_eth0,
         int x_eth1,int y_eth1
           ) :parent(work_field),
begining(first),
ending(last),
name(theName),
type(theType),
LineWidth(theWidth),
R1(0.98),G1(0.43),B1(0.43),
R2(0.925),G2(0.61),B2(0.61),
R1S(0.45),G1S(0.77),B1S(0.97),
R2S(0.64),G2S(0.85),B2S(0.97),
isSel(false),
active(false),
isActive(false),
eth0(l_eth0),
eth1(l_eth1),
dx1(10),
dy1(15)
{
    /*
        txt1 = new Text(parent,x_eth0,y_eth0,l_eth0);
         qDebug()<<"l_eth0"<<l_eth0<<"x_eth0 = "<<x_eth0<<"y_eth0 = "<<y_eth0;
        txt2 = new Text(parent,x_eth1,y_eth1,l_eth1);
         qDebug()<<"l_eth1"<<l_eth1<<"x_eth1 = "<<x_eth1<<"y_eth1 = "<<y_eth1;
         */

    if (x_eth0 && y_eth0 && x_eth1 && y_eth1)
    {
        txt1 = new Text(parent,x_eth0,y_eth0,l_eth0);
        txt2 = new Text(parent,x_eth1,y_eth1,l_eth1);
    }
    else
    {

    qDebug()<<"Link::Link";
                //txt1 = new Text(parent,100,100,"Example");
                 txt1 = new Text(parent,begining->x()+dx1+30,begining->y()+dy1-50,"192.168.0.1");
                 txt2 = new Text(parent,ending->x()+dx1+30,ending->y()+dy1-50,"172.16.22.37");
                  qDebug()<<"begining->x()+dx1"<<begining->x()+dx1+30;
                  qDebug()<<"begining->y()+dy1"<<begining->y()+dy1-50;
                 //txt1->paint();

     }
    this->begining->appendLink(this);
    this->ending->appendLink(this);

}
Link::~Link()
{

}
//-------------------------------------

void Link::setActive(bool t_active)
{
    // qDebug()<<"setActive";
    active = t_active;
    paint(0);
}
//устанавливает и возвращает цвет
void Link::setColor(int r1, int g1, int b1,int r2, int g2, int b2)
{
    R1 = GLfloat(1.*r1/255.); R2 = GLfloat(1.*r2/255.);
    G1 = GLfloat(1.*g1/255.); G2 = GLfloat(1.*g2/255.);
    B1 = GLfloat(1.*b1/255.); B2 = GLfloat(1.*b2/255.);
}
void Link::getColor(int &r1, int &g1,int &b1, int &r2,int &g2,int &b2)
{
    r1 = int(R1*255); r2 = int(R2*255);
    g1 = int(G1*255); g2 = int(G2*255);
    b1 = int(B1*255); b2 = int(B2*255);
}
void Link::setColorSelected(int r1, int g1, int b1,int r2, int g2 , int b2)
{
    R1S = GLfloat(1.*r1/255.); R2S = GLfloat(1.*r2/255.);
    G1S = GLfloat(1.*g1/255.); G2S = GLfloat(1.*g2/255.);
    B1S = GLfloat(1.*b1/255.); B2S = GLfloat(1.*b2/255.);
}
void Link::getColorSelected(int &r1, int &g1,int &b1, int &r2,int &g2,int &b2)
{
    r1 = int(R1S*255); r2 = int(R2S*255);
    g1 = int(G1S*255); g2 = int(G2S*255);
    b1 = int(B1S*255); b2 = int(B2S*255);
}

//устанавливает имя и тип
void Link::setName(QString n)
{  name =n; }
void Link::setType(int t)
{  type=t;  }

//возвращает имя и тип
QString Link::getName() const
{  return name; }
int Link::getType() const
{  return type; }

//установка и возврат толщины линии
void Link::setWidth(int w)
{  LineWidth=w; }
int Link::getWidth() const
{  return LineWidth; }

//установка признака активности
void Link::SetActive(bool activ)
{
    if(activ)
        this->setColor(106,239,106,160,245,160);
    else
        this->setColor(251,110,110,236,155,155);
}

//устанавливает и возвращает признак выделения
void Link::setIsSelected(bool fl)
{
    this->isSel = fl;
}
bool Link::isSelected() const
{
    return this->isSel;
}

void Link::paintPoint(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLfloat KS,int R)
{
    /*
    GLfloat S = 25;
    GLfloat alph = (x2>x1) ? asin((y2-y1)/sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))) :
                   3.1415-asin((y2-y1)/sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
    glPushMatrix();
    glTranslatef(x1+(x2-x1)*KS,y1+(y2-y1)*KS,0);
    glRotatef(alph*180/3.1415,0,0,1);

    GLfloat tx1 = 0;
    GLfloat ty1 = 0;

    GLint circle_points = 100;
    GLfloat angle;
    glColor3f(0.0,1.0,0.0);

    if (this->active)
    {
        glColor3f(0.0,1.0,0.0);
        //glColor3f(0.0,1.0,0.0);  //green
    }
    else
    {
        glColor3f(1.0,0.0,0.0);  // red
    }


    glBegin(GL_POLYGON);
    for (int i=0;i<circle_points;i++)
    {
        angle = 2*3.14*i/circle_points;
        glVertex2f(tx1+R*cos(angle),ty1+R*sin(angle));
    }
    glEnd();
    glTranslatef(0,0,0.1);
    glPopMatrix();
    */
}
void Link::paint(int aniStep)
{
    //glColor3f(0.0,0.0,0.0);
    //qDebug()<<"Link::paint";
    //aniStep /=100;
    //this->begining->link++;
    //this->ending->link++;
    GLfloat x1 = this->begining->x()/*+this->begining->width()*/;//+0.29*this->begining->height();
    GLfloat y1 = this->begining->y()/*+2*this->begining->link*//*this->begining->height()*/;
    GLfloat x2 = this->ending->x();//-this->ending->height()*0.29;
    GLfloat y2 = this->ending->y()/*+2*this5->ending->link/*+this->ending->height()*0.5*/;
    GLfloat theLength = lengthXY(x1,y1,x2,y2);
           // sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
    GLfloat r1 = R1;
    GLfloat r2 = R2;
    GLfloat g1 = G1;
    GLfloat g2 = G2;
    GLfloat b1 = B1;
    GLfloat b2 = B2;

    glLineWidth(LineWidth);
    int N = int(theLength/50);
    if (isSel)
    {
        glLineWidth(7);
        r1 = R1S;
        r2 = R2S;
        g1 = G1S;
        g2 = G2S;
        b1 = B1S;
        b2 = B2S;
    }
    //glColor3f(r1,g1,b1);
    //glColor3f(0.0,0.0,1.0);
    glColor3f(0.0,0.0,0.0);  //black

    /*
        if ((this->begining->isSel)&&(this->ending->isSel))
    {
          glColor3f(0.0,1.0,0.0);  //green
    }
        */


    if ((this->active)||((this->begining->isSel)&&(this->ending->isSel)))
    {
        glColor3f(0.0,0.9,0.0);
        isActive = true;
        //glColor3f(0.0,1.0,0.0);  //green
    }
    else
    {
        isActive = false;

        glColor3f(0.0,0.0,0.0);  // red
    }

    //glLineStipple(2,0x00FF);
    if (this->getType())
    {
     glEnable(GL_LINE_STIPPLE);
     glLineWidth(3);
     glLineStipple(2,0x0C0C);
    }

    glBegin(GL_LINE);
    //float sc = (aniStep % 10)/5.0;
    float sc = 0;
    glVertex2f(x1,y1);

    /*
    qDebug()<<"x1"<<x1<<"y1"<<y1;
    qDebug()<<"x2"<<x2<<"y2"<<y2;
    */
    glVertex2f(x2,y2);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    //paintPoint(x1,y1,x2,y2,0.2,5);
    //paintPoint(x1,y1,x2,y2,0.8,5);
    glColor3f(r1,g1,b1);
    GLfloat R1 = 55;

    glColor3f(0.0,1.0,0.0);  //green
     R1 = 55;
    /*
    switch(this->begining->getDeviceType())
    {
    case COMPUTER:
        R1 = 70;
        break;
    case ROUTER:
        R1 = 55;
        break;
    case RADIO:
        R1 = 55;
        break;

    default:
        break;
    }
    */

    switch(this->begining->getDeviceType())
            qDebug()<<"theLength"<<theLength;

        if (!this->getType())
    {
    if (theLength>130)
    {
        /*
        GLfloat x11 = x1+(x2-x1)*R1/theLength;
        GLfloat y11 = y1+(y2-y1)*R1/theLength;
        */

        GLfloat x11 = xy(x1,x2,R1,theLength);
        GLfloat y11 = xy(y1,y2,R1,theLength);

        drawCircle(x11,y11,5,100);
        glColor3f(0.0,0.0,0.0);  //black

        //parent->renderText(x11+10,y11+15,0.02,eth1);
        //txt1->move(x11+10,y11+15);
        /*
        txt1->move(x11-dx1,y11-dy1);
        */
        /*
        GLfloat dx1 =  txt1->x() - x11;
        GLfloat dxy1 =  txt1->y() - y11;
       */
        txt1->paint();
        txt2->paint();
        //qDebug()<<"dx1"<<dx1<<"dxy"<<dxy1;

       // txt1->move(x11+dx1,y11+dxy1);
        /*
         qDebug()<<"x11-dx1"<<x11<<"txt1->x()"<<txt1->x();
         qDebug()<<"y11-dy1"<<y11<<"txt1->y()"<<txt1->y();
         */


        glColor3f(0.0,1.0,0.0);  //green
        GLfloat x21 = xy(x2,x1,R1,theLength);
        GLfloat y21 = xy(y2,y1,R1,theLength);
        drawCircle(x21,y21,5,100);
        //func(x21);
        glColor3f(0.0,0.0,0.0);  //black
       // parent->renderText(x21-80,y21+25,0.02,eth0);

    }
}
    glTranslatef(0,0,0.1);
    glPopMatrix();
    //glTexParameteri(GL_TEXTURE2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);


}
//-----------------------------------------------------

//возвращает область в центре, которую можно использовать для выделения связи
QRect Link::getCentralArea() const
{
    GLfloat x1 = this->begining->x()+this->begining->width()*0.5;//+0.29*this->begining->height();
    GLfloat y1 = this->begining->y()+this->begining->height()*0.5;
    GLfloat x2 = this->ending->x()+this->ending->width()*0.5;//-this->ending->height()*0.29;
    GLfloat y2 = this->ending->y()+this->ending->height()*0.5;
    int xc = int(0.5*(x1+x2));
    int yc = int(0.5*(y1+y2));
    return QRect(xc-20, yc-20, 40, 40);
}
//-----------------------------------------------------

