#include "text.h"
#include <QDebug>

Text::Text(Field *work_field,int tmpX, int tmpY,QString t_text):parent(work_field),
text(t_text),
X(tmpX),
Y(tmpY),
R1(0.98),G1(0.43),B1(0.43),
R2(0.925),G2(0.61),B2(0.61),
R1S(0.45),G1S(0.77),B1S(0.97),
R2S(0.64),G2S(0.85),B2S(0.97),
R1L(0.937),G1L(1),B1L(0.53),
H(10),W(110),
visible(true)
{

}

Text::~Text()
{
}

void Text::move(int x, int y)
{
    qDebug()<<"Move X = "<<x<<"Y = "<<y;
    this->X = x;
    this->Y = y;
    paint();
}

void Text::paint()
{

    GLfloat r1 = R1;
    GLfloat g1 = G1;
    GLfloat b1 = B1;
    GLfloat r2 = R2;
    GLfloat g2 = G2;
    GLfloat b2 = B2;
    glLineWidth(4);
    if (this->isSel)
    {
        r1 = R1S;
        g1 = G1S;
        b1 = B1S;
        r2 = R2S;
        g2 = G2S;
        b2 = B2S;
        glLineWidth(10);
    }
    /*
    int M = this->W*0.5;
    glAlphaFunc(GL_GEQUAL,10.9f);
    glRasterPos3d(W/2-W/2-20,10+H,0.01);
    glTranslatef(-20,10,-0.525);
    glLineWidth(this->getLineWigth());
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
*/
    /*
    W = 11*dt
    H =  dt
         */
   // qDebug()<<"x()-W/2"<<x()-W/2<<"y()-H/2"<<y()-H/2;
    glColor3f(0, 0, 0);
     glTranslatef(x()-W/2,y()-H/2,0);
    //parent->renderText(x(),y(),0.02,getText());
     if (this->isVisible())
        parent->renderText(0,0,0.02,getText());
    //glLineWidth(2);
     double dt = 10;
/************************************
        glBegin(GL_LINE_LOOP);
         //glVertex2f(0,0);
         glVertex2f(-dt,-2*dt);
         glVertex2f(12*dt,-2*dt);
          glVertex2f(+12*dt,+dt);
        glVertex2f(-dt,+dt);
    *****************************/



        /*glVertex2f(x()-dt,y()-2*dt);
        glVertex2f(x()+12*dt,y()-2*dt);
        glVertex2f(x()+12*dt,y()+dt);
        glVertex2f(x()-dt,y()+dt);
        */
    glEnd();
glTranslatef(-(x()-W/2),-(y()-H/2),0);
    /*
    glTranslatef(x(),y(),-0.525);
    double dt = 5;
    glLineWidth(this->getLineWigth());
    glBegin(GL_LINE_LOOP);
        glVertex2f(-dt,-dt);
        glVertex2f(W+dt,-dt);
        glVertex2f(W+dt,H+dt);
        glVertex2f(-dt,H+dt);
    glEnd();
    */
}

int Text::x() const
{
    return this->X;
}

int Text::y() const
{
    return this->Y;
}

/*
void Text::setCoord(int x,int y)
{
    this->Y = y;
    this->X = x;
}
*/

QString Text::getText() const
{
    return this->text;
}
int Text::width() const
{
    return this->W;
}
int Text::height() const
{
    return this->H;
}

void Text::setIsSelected(bool flag)
{
    this->isSel = flag;
}
bool Text::getIsSelected()
{
    return this->isSel;
}

void Text::setVisible(bool t_visible)
{
   this->visible = t_visible;

}
bool Text::isVisible()
{
    return this->visible;
}

int Text::getLineWigth() const
{
    return this->linewidth;
}
void Text::setLineWigth(int lw)
{
    this->linewidth = lw;
}

