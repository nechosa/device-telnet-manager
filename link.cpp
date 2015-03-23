#include "link.h"

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

