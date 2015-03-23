#include "device.h"
#include <QMenu>
#include <QAction>

Device::Device(Field *work_field,int tmpX, int tmpY/*GLfloat tmpX, GLfloat tmpY*/,QString image,QString myName):parent(work_field),
//Device::Device(Field *parent,int tmpX, int tmpY):Field(parent),
///*GLfloat tmpX, GLfloat tmpY*/):parent(work_field),
//Field::Field(QWidget * parent):QGLWidget(parent),
R1(0.98),G1(0.43),B1(0.43),
R2(0.925),G2(0.61),B2(0.61),
R1S(0.45),G1S(0.77),B1S(0.97),
R2S(0.64),G2S(0.85),B2S(0.97),
R1L(0.937),G1L(1),B1L(0.53),
X(tmpX),    Y(tmpY),
H(64),W(64)
{
    Name = QString (myName);
    qDebug()<<" CREATE DEVICE";
    qDebug()<<" tmp_X1 = "<< tmpX<<" tmp_Y1 = "<<tmpY;
    /*
        work_field->tmpX = tmpX-work_field->shiftTranslateX;
        work_field->tmpY = tmpY-work_field->shiftTranslateY;
        */

    //qDebug()<<" tmpX = "<< tmpX-work_field->shiftTranslateX<<" tmpY = "<<tmpY-work_field->shiftTranslateY;
    /*
    QImage Device;
    switch (type)
    {
        case EnumType.Computer:
        Device = QImage(":/img/img/workstation_256.png");
        break;
        case EnumType.Router:
        Device = QImage(":/img/img/router-hi.png");
        break;
        default:
        break;
    }
    */
         //QImage Commut = QImage(":/img/img/workstation_256.png");
        QImage Commut = QImage(28,28,QImage::Format_ARGB32_Premultiplied);
        //Commut.load(":/img/img/router-th.png","PNG");
        Commut.load(image);
        this->setPix(Commut);
        H = Commut.height();
        W = Commut.width();
    paint();
}

Device::~Device()
    {
    }

    bool Device::eventFilter(QObject * obj, QEvent * evnt)
    {
        QMouseEvent * me = dynamic_cast<QMouseEvent *>(evnt);
        if (me)
        {
            qDebug()<<" tmpXXX = "<< me->pos().x()<<" tmpYYY = "<<me->pos().y();

            /*
        work_field->tmpX = me->pos().x()-work_field->shiftTranslateX;
        work_field->tmpY = me->pos().y()-work_field->shiftTranslateY;
        */
            // qDebug()<<" tmpX = "<< me->pos().x()-work_field->shiftTranslateX<<" tmpY = "<<me->pos().y()-work_field->shiftTranslateY;

        }
    }

    void Device::setPix(QImage &px)
    {
        pixx = QGLWidget::convertToGLFormat(px);
        PIXX = px;
    }

    QImage Device::pix()
    {
        return PIXX;
    }

    void Device::move(int x, int y)
{
    this->X = x;
    this->Y = y;
}

    void Device::paint()
    {
        qDebug()<<" paint";

        /*
    if(ObjType==1)
    {
        W=130;H=110;
        QImage hub = QImage(":/img/img/hub.png");
        this->setPix(hub);
    }
    if(ObjType==2)
    {
        W=130;H=110;
        QImage Commut = QImage(":/img/img/commut.png");
        this->setPix(Commut);
    }
    if(ObjType==3)
    {
        W=130;H=150;
        QImage Kompl = QImage(":/img/img/komplex.png");
        this->setPix(Kompl);
    }
    if(ObjType==4)
    {
        W=130;H=150;
        QImage Sys = QImage(":/img/img/systema.png");
        this->setPix(Sys);
    }
    */
        //------------------------------------------------------

        //######################################################
        //здесь отрисовка самого узла с анимацией
        //######################################################

    GLfloat r1 = R1;
    GLfloat g1 = G1;
    GLfloat b1 = B1;
    GLfloat r2 = R2;
    GLfloat g2 = G2;
    GLfloat b2 = B2;
    /*
    if (this->isSel)
    {
        */
        r1 = R1S;
        g1 = G1S;
        b1 = B1S;
        r2 = R2S;
        g2 = G2S;
        b2 = B2S;
    //}
    int M = this->W*0.5;
   // M += 0.5*W*sin(animaStep/3000.);
/*
    glBegin(GL_POLYGON);
        glColor3f(r1,g1,b1);
        glVertex3f(0,0,0);
        glColor3f(r2,g2,b2);
        glVertex3f(M,0,0);
        glVertex3f(M,H,0);
        glColor3f(r1,g1,b1);
        glVertex3f(0,H,0);
    glEnd();
    */
/*
    glBegin(GL_POLYGON);
        glColor3f(r1,g1,b1);
        glVertex3f(W,0,0);
        glColor3f(r2,g2,b2);
        glVertex3f(M,0,0);
        glVertex3f(M,H,0);
        glColor3f(r1,g1,b1);
        glVertex3f(W,H,0);
    glEnd();
*/
    /**/
    //------------------------------------------------------

    //треугольник для визуализации признака ошибки
    //    glBegin(GL_POLYGON);
    //        if (this->isError)
    //            glColor3f(1.,0.,0.);
    //        else
    //            glColor3f(0.,1.,0.);
    //        glVertex2f(W*0.5,40);
    //        glColor3f(1.,1.,1.);
    //        glVertex2f(W*0.5-20,70);
    //        glVertex2f(W*0.5+20,70);
    //    glEnd();

    //######################################################
    //ПФТЙУПЧЛБ РПМС РПД РЙЛФПЗТБННХ
    //######################################################
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL,10.9f);
    glRasterPos3d(W/2-pixx.width()/2,10+pixx.height(),0.01);
    //glRasterPos3d(pixx.width()/2,pixx.height(),0.01);
    //glDrawPixels(pixx.width(), pixx.height(), GL_RGBA, GL_UNSIGNED_BYTE, pixx.bits());
    glDrawPixels(pixx.width(), pixx.height(), GL_RGBA, GL_UNSIGNED_BYTE, pixx.bits());
     glDisable(GL_ALPHA_TEST);
    //glTranslatef(0,0,0.025);
    //glColor3f(R1L,G1L,B1L);
    //glLineWidth(2);

    glBegin(GL_LINE_LOOP);
        glVertex2f(W/2-pixx.width()/2,10);
        glVertex2f(W/2+pixx.width()/2,10);
        glVertex2f(W/2-pixx.width()/2+pixx.width(),10+pixx.height());
        glVertex2f(W/2-pixx.width()/2,10+pixx.height());
    glEnd();


   // glTranslatef(0,0,-0.025);
    //------------------------------------------------------

    //    if (theSign)
    //    {
    //        glPushMatrix();
    //        glTranslatef(W-pixx.width()+3,23,0.3);
    //             this->theSign->paint(animaStep);
    //        glPopMatrix();
    //    }
    //    else
    //    {
    //        glRasterPos3d(W-10-pixx2.width(),10+pixx2.height(),0.01);
    //        glDrawPixels(pixx2.width(), pixx2.height(), GL_RGBA, GL_UNSIGNED_BYTE, pixx2.bits());
    //    }
    //    glTranslatef(0,0,0.025);
    //    glBegin(GL_LINE_LOOP);
    //        glVertex2f(W-10,10);
    //        glVertex2f(W-10-pixx2.width(),10);
    //        glVertex2f(W-10-pixx2.width(),10+pixx2.height());
    //        glVertex2f(W-10,10+pixx2.height());
    //    glEnd();

    //треугольник для визуализации признака ошибки
    //    glBegin(GL_LINE_LOOP);
    //        glVertex2f(W*0.5,40);
    //        glVertex2f(W*0.5-20,70);
    //        glVertex2f(W*0.5+20,70);
    //    glEnd();

    //    glBegin(GL_POLYGON);
    //        glColor3f(r1,g1,b1);
    //        glVertex3f(W,0.35*H,0);
    //        glVertex3f(W,0.65*H,0);
    //        glColor3f(r2,g2,b2);
    //        glVertex3f(W+0.3*H,0.5*H,0);
    //    glEnd();
    //    glBegin(GL_POLYGON);
    //        glColor3f(r1,g1,b1);
    //        glVertex3f(-0.3*H,0.35*H,0);
    //        glVertex3f(-0.3*H,0.65*H,0);
    //        glColor3f(r2,g2,b2);
    //        glVertex3f(0,0.65*H,0);
    //        glVertex3f(0,0.35*H,0);
    //    glEnd();

    //    GLfloat L = W-140;
    //    glColor3f(1.,1.,0);
    //    if (this->isLeft)
    //    {
    //    glBegin(GL_POLYGON);
    //        glVertex2f(70,10);
    //        glVertex2f(70,30);
    //        glVertex2f(70+L*0.5,30);
    //        glVertex2f(70+L*0.5,10);
    //    glEnd();
    //    }
    //    if (this->isRight)
    //    {
    //    glBegin(GL_POLYGON);
    //        glVertex2f(70+L*0.5,10);
    //        glVertex2f(70+L*0.5,30);
    //        glVertex2f(70+L,30);
    //        glVertex2f(70+L,10);
    //    glEnd();
    //    }


    //######################################################
    //ПФТЙУПЧЛБ ЛПОФХТБ
    //######################################################
    //------РТЙ ЧЩДЕМЕОЙЙ ------
    //glLineWidth(this->LineWidth);
    /*if (isSel)
    {
            double dt = 5;
            glColor3f(0.1, 0., 0.5);
            glPushAttrib(GL_LINE_STIPPLE);
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(1,0xF0F0);
            glBegin(GL_LINE_LOOP);
                glVertex2f(-dt,-dt);
                glVertex2f(W+dt,-dt);
                glVertex2f(W+dt,H+dt);
                glVertex2f(-dt,H+dt);
            glEnd();
//            dt = 10;
//            glColor3f(R1L, G1L, B1L);
//            glLineStipple(1,0x0F0F);
//            glBegin(GL_LINE_LOOP);
//                glVertex2f(-dt,-dt);
//                glVertex2f(W+dt,-dt);
//                glVertex2f(W+dt,H+dt);
//                glVertex2f(-dt,H+dt);
//            glEnd();
           glPopAttrib();
//            glLineWidth(this->LineWidth+1);
    }
//------рПУФПСООЩК ЛПОФХТ ------
    */
    /*
    glColor3f(R1L, G1L, B1L);
    glPushMatrix();
    glTranslatef(0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0,0);
    glVertex2f(W,0);
    glVertex2f(W,H);
    glVertex2f(0,H);
    glEnd();
    */
    //------------------------------------------------------


    //    glBegin(GL_LINE_LOOP);
    //        glVertex3f(W,0.35*H,0);
    //        glVertex3f(W,0.65*H,0);
    //        glVertex3f(W+0.3*H,0.5*H,0);
    //    glEnd();
    //    glBegin(GL_LINE_LOOP);
    //        glVertex3f(-0.3*H,0.35*H,0);
    //        glVertex3f(-0.3*H,0.65*H,0);
    //        glVertex3f(0,0.65*H,0);
    //        glVertex3f(0,0.35*H,0);
    //    glEnd();
    //    glLineWidth(2);

    //    glBegin(GL_LINE_LOOP);
    //        glVertex2f(70,10);
    //        glVertex2f(70,30);
    //        glVertex2f(70+L*0.5,30);
    //        glVertex2f(70+L*0.5,10);
    //    glEnd();
    //    glBegin(GL_LINE_LOOP);
    //        glVertex2f(70+L*0.5,10);
    //        glVertex2f(70+L*0.5,30);
    //        glVertex2f(70+L,30);
    //        glVertex2f(70+L,10);
    //    glEnd();
    //    glPopMatrix();

    //######################################################
    //дПВБЧМЕОЙЕ ФЕЛУФБ
    //######################################################
    //glColor3f(0, 0, 0);
    //parent->renderText(10,H-5,0.02,"NET ADDR");
    //parent->renderText(10,H-25,0.02,"NAME");
    //------------------------------------------------------
}

    int Device::x()
    {
        return this->X;
    }

        int Device::y()
    {
        return this->Y;
    }

         QString Device::getName()
        {
             return this->Name;
        }
    int Device::width()
    {
        return this->W;
    }
        int Device::height()
    {
        return this->H;
    }

 void Device::contextMenuEvent(QContextMenuEvent *e)
{
     qDebug()<<"contextMenuEvent 1111";
     //QMenu *menu1 = new QMenu("&Menu");
     /*QAction *action1 = new QAction(QString::fromLocal8Bit("Device 0 "), this);
     menu.addAction(action1);
     menu.addSeparator();
      QAction *action2 = new QAction(QString::fromLocal8Bit("Device 1"), this);
      action2->setIcon(QIcon(":/img/img/workstation_256.png"));
      menu.addAction(action2);
      // menu.addAction();
      */
      //menu1.exec(e->globalPos());
}
 void Device::mousePressEvent(QMouseEvent *event)
 {
     if (event->button()==Qt::RightButton)
        {
         qDebug()<<"Device mousePressEvent";

         /*
            QMenu *menu1 = new QMenu(this);
            /*
            QAction *action1 = new QAction(QString::fromLocal8Bit("Device 0 "), this);
            menu1->addAction(action1);



            menu1->addSeparator();

            menu1->exec(event->globalPos());
        /*
        QAction *action2 = new QAction(QString::fromLocal8Bit("Device 1"), this);
      action2->setIcon(QIcon(":/img/img/workstation_256.png"));
      menu1.addAction(action2);*/
      //menu1.exec(event->globalPos());
         }
 }

 void Device::setIsSelected(bool fl)
{
    this->isSel = fl;
}
bool Device::getIsSelected()
{
    return this->isSel;
}


 /**********************************************************************************************************************/

 //--- Конструктор и деструктор класса ---
Link::Link(Device * first, Device * last, QString theName,int theType,int theWidth) :
    begining(first),
    ending(last),
    name(theName),
    type(theType),
    LineWidth(theWidth),
    R1(0.98),G1(0.43),B1(0.43),
    R2(0.925),G2(0.61),B2(0.61),
    R1S(0.45),G1S(0.77),B1S(0.97),
    R2S(0.64),G2S(0.85),B2S(0.97),
    isSel(false)
{
    qDebug()<<"Link::Link";
}
Link::~Link()
{

}
//-------------------------------------

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
QString Link::getName()
{  return name; }
int Link::getType()
{  return type; }

//установка и возврат толщины линии
void Link::setWidth(int w)
{  LineWidth=w; }
int Link::getWidth()
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
bool Link::isSelected()
{
    return this->isSel;
}

//рисование линии связи
void Link::paint(int aniStep)
{
    qDebug()<<"Link::paint";
    aniStep /=100;
    GLfloat x1 = this->begining->x()+this->begining->width();//+0.29*this->begining->height();
    GLfloat y1 = this->begining->y()+this->begining->height()*0.5;
    GLfloat x2 = this->ending->x();//-this->ending->height()*0.29;
    GLfloat y2 = this->ending->y()+this->ending->height()*0.5;
    GLfloat theLength = sqrt((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
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
    glColor3f(r1,g1,b1);
    glBegin(GL_LINE_STRIP);
    float sc = (aniStep % 10)/5.0;
    glVertex2f(x1,y1);
    for (int i=1;i<N-1;i++)
    {
         if (i % 2)
              glColor3f(r2,g2,b2);
         else
              glColor3f(r1,g1,b1);
         GLfloat xx = x1+(x2-x1)*(i+sc)/N;
         GLfloat yy = y1+(y2-y1)*(i+sc)/N;
         glVertex2f(xx,yy);
    }
    glVertex2f(x2,y2);
    glEnd();

    GLfloat S = 25;
    GLfloat KS = 0.5;
    GLfloat alph = (x2>x1) ? asin((y2-y1)/sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))) :
                   3.1415-asin((y2-y1)/sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
    glPushMatrix();
    glTranslatef(x1+(x2-x1)*KS,y1+(y2-y1)*KS,0);
    glRotatef(alph*180/3.1415,0,0,1);
    GLfloat tx1 = 0;
    GLfloat ty1 = 0;
    GLfloat tx2 = tx1-S;
    GLfloat ty2 = -S*0.36;
    GLfloat tx3 = tx1-S;
    GLfloat ty3 = S*0.36;
    glColor3f(r1,g1,b1);
    glTranslatef(0,0,0.1);
    glBegin(GL_POLYGON);
        glVertex2f(tx1,ty1);
        glVertex2f(tx2,ty2);
        glVertex2f(tx3,ty3);
    glEnd();
    glTranslatef(0,0,0.1);
    int rr, gg, bb;
    //this->begining->getColorLine(rr,gg,bb);

    glColor3f(rr/255.,gg/255.,bb/255.);
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
        glVertex2f(tx1,ty1);
        glVertex2f(tx2,ty2);
        glVertex2f(tx3,ty3);
    glEnd();
    glPopMatrix();

}
//-----------------------------------------------------

//возвращает область в центре, которую можно использовать для выделения связи
QRect Link::getCentralArea()
{
    GLfloat x1 = this->begining->x()+this->begining->width();//+0.29*this->begining->height();
    GLfloat y1 = this->begining->y()+this->begining->height()*0.5;
    GLfloat x2 = this->ending->x();//-this->ending->height()*0.29;
    GLfloat y2 = this->ending->y()+this->ending->height()*0.5;
    int xc = int(0.5*(x1+x2));
    int yc = int(0.5*(y1+y2));
    return QRect(xc-20, yc-20, 40, 40);
}
//-----------------------------------------------------

