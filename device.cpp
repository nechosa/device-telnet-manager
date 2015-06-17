#include "device.h"
#include <QMenu>
#include <QAction>
#include "link.h"



/*************************************************************************************************************************************/
Device::Device(Field *work_field,int tmpX, int tmpY,DeviceType type,QString d_name, QString d_ipaddr):parent(work_field),
Name(d_name),
ipaddr(d_ipaddr),
R1(0.98),G1(0.43),B1(0.43),
R2(0.925),G2(0.61),B2(0.61),
R1S(0.45),G1S(0.77),B1S(0.97),
R2S(0.64),G2S(0.85),B2S(0.97),
R1L(0.937),G1L(1),B1L(0.53),
d_type(type),
linewidth(3),
//X(tmpX),    Y(tmpY),
H(64),W(64),
isSel(1),
link(0)
{
    QImage Commut = QImage(28,28,QImage::Format_ARGB32_Premultiplied);
    switch(d_type)
    {
    case COMPUTER:
        //Name = QString::fromLocal8Bit(C_COMPUTER);
        //ipaddr = QString::fromLocal8Bit("127.0.0.1");
        X =tmpX;
        Y = tmpY;
        Commut.load(IMAGE_COMP);
        break;
    case ROUTER:
        //Name = QString::fromLocal8Bit(C_ROUTER);
        //ipaddr = QString::fromLocal8Bit("127.0.0.1");
        X =tmpX;
        Y = tmpY;
        Commut.load(IMAGE_ROUTER);
        break;
    case RADIO:
        //Name = QString::fromLocal8Bit(C_RADIO);
        //ipaddr = QString::fromLocal8Bit("127.0.0.1");
        X =tmpX;
        Y = tmpY;
        Commut.load(IMAGE_RADIO);
        break;

    default:
        break;
    }

    this->setPix(Commut);
    H = Commut.height();
    W = Commut.width();
    qDebug()<<"H = "<<H;
    qDebug()<<"W = "<<W;
    edit = new Property();
    edit->setName(d_name);
    //edit->set
    paint();
}
Device::~Device()
{
}

Link * Device::getLink(int num) const
{
    if ((num>=0) && (num<this->links.size()))
        return links.at(num);
    else
        return 0;
}
void Device::appendLink(Link * newLink)
{
    if (newLink)
        this->links.append(newLink);
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


int Device::lineWigth() const
{
    return this->linewidth;
}
void Device::setLineWigth(int lw)
{
    this->linewidth = lw;
}

const DeviceType Device::getDeviceType() const
{
    return d_type;
}
void Device::setPix(QImage &px)
{
    pixx = QGLWidget::convertToGLFormat(px);
    PIXX = px;
}

QImage Device::pix() const
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
    //qDebug()<<" Device::paint";

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
    //    }
    int M = this->W*0.5;
    // M += 0.5*W*sin(animaStep/3000.);

    //æÏÎ ×ÎÕÔÒÉ ÕÓÔÒÏÊÓÔ×Á
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

    //òðåóãîëüíèê äëÿ âèçóàëèçàöèè ïðèçíàêà îøèáêè
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
    //ÏÔÒÉÓÏ×ËÁ ÐÏÌÑ ÐÏÄ ÐÉËÔÏÇÒÁÍÍÕ
    //######################################################
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GEQUAL,10.9f);
    switch(getDeviceType())
    {
    case COMPUTER:
        glRasterPos3d(W/2-pixx.width()/2-35,pixx.height()-20,0.01);
        glTranslatef(-35,-20,-0.525);
        glLineWidth(this->lineWigth());
        if (isSel)
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
            glPopAttrib();
        }
        glColor3f(0, 0, 0);
        //parent->renderText(-5,H+35,0.02,getIpaddr());
        parent->renderText(0,H+20,0.02,getName());

        break;
    case ROUTER:
        glRasterPos3d(W/2-pixx.width()/2-20,10+pixx.height(),0.01);
        glTranslatef(-20,10,-0.525);
        glLineWidth(this->lineWigth());
        if (isSel)
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
            glPopAttrib();
        }
        glColor3f(0, 0, 0);
        //parent->renderText(0,H+35,0.02,getIpaddr());
        parent->renderText(-10,H+20,0.02,getName());
        break;
        
    case RADIO:
        glRasterPos3d(W/2-pixx.width()/2-20,10+pixx.height(),0.01);
        glTranslatef(-20,10,-0.525);
        glLineWidth(this->lineWigth());
        if (isSel)
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
            glPopAttrib();
        }
        glColor3f(0, 0, 0);
        //parent->renderText(10,H+35,0.02,getIpaddr());
        parent->renderText(0,H+20,0.02,getName());
        break;

    default:
        break;
    }

    //glRasterPos3d(pixx.width()/2,pixx.height(),0.01);
    //glDrawPixels(pixx.width(), pixx.height(), GL_RGBA, GL_UNSIGNED_BYTE, pixx.bits());
    glDrawPixels(pixx.width(), pixx.height(), GL_RGBA, GL_UNSIGNED_BYTE, pixx.bits());
    glDisable(GL_ALPHA_TEST);
    //glTranslatef(0,0,0.025);
    //glColor3f(R1L,G1L,B1L);
    //glLineWidth(2);

    /// ë×ÁÄÒÁÔ
    /*
    glBegin(GL_LINE_LOOP);
    glVertex2f(W/2-pixx.width()/2,10);
    glVertex2f(W/2+pixx.width()/2,10);
    glVertex2f(W/2-pixx.width()/2+pixx.width(),10+pixx.height());
    glVertex2f(W/2-pixx.width()/2,10+pixx.height());
    glEnd();
    */


    //glTranslatef(0,0,-0.025);
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

    //òðåóãîëüíèê äëÿ âèçóàëèçàöèè ïðèçíàêà îøèáêè
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
    //ÏÔÒÉÓÏ×ËÁ ËÏÎÔÕÒÁ
    //######################################################
    //------ÐÒÉ ×ÙÄÅÌÅÎÉÉ ------


    //------ðÏÓÔÏÑÎÎÙÊ ËÏÎÔÕÒ ------

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
    //äÏÂÁ×ÌÅÎÉÅ ÔÅËÓÔÁ
    //######################################################

    //------------------------------------------------------
}

int Device::x() const
{
    return this->X;
}

int Device::y() const
{
    return this->Y;
}

QString Device::getName() const
{
    return this->Name;
}

QString Device::getIpaddr() const
{
    return this->ipaddr;
}
int Device::width() const
{
    return this->W;
}
int Device::height() const
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

