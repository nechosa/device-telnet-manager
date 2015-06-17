#include "field.h"
#include <QDebug>
#include <QApplication>
#include <QMenu>
#include <QAction>
#include "presentertelnet.h"
#include "telnetform.h"
#include "device.h"
#include <QList>
#include <QListIterator>

template <typename T1,typename T2>
        inline bool isAreaDevice(const T1& x,const T1& y,const T2* dev)
{
    //условие  попадания в область
    return  ((x>dev->x()-dev->width()/2)&&(x<dev->x()+dev->width()/2)
             &&(y>dev->y()-dev->height()/2)&&(y<dev->y()+dev->height()/2));
}

template <typename T1,typename T2>
        inline void setActiveRoute(const QList <T1> route,const T2& active)
{
    QListIterator <T1> it(route);
    while (it.hasNext())
    {
        it.next()->setActive(active);
    }
}

template <typename T1,typename T2>
        inline void setInform(const QList <T1> links,const T2 active)
{
    QListIterator <T1> it(links);
    while (it.hasNext())
    {
         T1 link = it.next();
         link->txt1->setVisible(active);
         link->txt2->setVisible(active);
        //it.next()->setActive(active);
        //it.next()->txt1->set(active);
    }
}
template <typename T1,typename T2>
        inline void append( T1 links, T2 &route)
{
    for (int i=links.size()-1;(i>=0);i--)
    {
        if (links.at(i)->isActive)
        {
            route.append(links.at(i));
        }
    }

}

template <typename T1,typename T2>
        inline void setSelect(const QList <T1> items,const T2& issel)
{
    QListIterator <T1> it(items);
    while (it.hasNext())
    {
        T1 dev = it.next(); 
        if (isAreaDevice(tmpX,tmpY,dev))
        {
            dev->setIsSelected(active);
        }
        it.next()->setActive(active);
    }
}

template <typename T1,typename T2,typename T3>
        inline void menuExec(const T1 dev,const T2 me,const T3 the)
{
    /*
                    qDebug()<<"this->tmpX"<<this->tmpX<<"this->tmpY"<<this->tmpY;
                    qDebug()<<"dev->width()"<<dev->width()<<"dev->height()"<<dev->height();
                    */
    dev->setIsSelected(true);
    QMenu menu(the);
    QAction *action1 = new QAction(QString::fromLocal8Bit("Редактировать"), the);
    menu.addAction(action1);
    QObject::connect(action1,SIGNAL(triggered()),the,SLOT(createProperty()));
    QAction *action2 = new QAction(QString::fromLocal8Bit("Удалить"), the);
    action2->setIcon(QIcon(":/img/img/workstation_256.png"));
    menu.addAction(action2);
    menu.addSeparator();
    QAction *action3 = new QAction(QString::fromLocal8Bit("Консоль"), the);
    //action3->setIcon(QIcon(":/img/img/workstation_256.png"));
        QObject::connect(action3,SIGNAL(triggered()),the,SLOT(createTerminal()));
    //menu.addSeparator();
    menu.addAction(action3);

    // menu.addAction();
    menu.exec(me->globalPos());
}

template <typename T1,typename T2,typename T3,typename T4>
        inline void contextMenu(const QList <T1> items,const T2 tmpX,const T2 tmpY,const T3 me,const T4 the)
{
    QListIterator <T1> it(items);
    while (it.hasNext())
    {
        T1 dev = it.next();
        if (isAreaDevice(tmpX,tmpY,dev))
        {
            menuExec(dev,me,the);
        }
        //it.next()->setActive(active);
    }
}

template <typename T1,typename T2,typename T3>
        inline void setSelect(const QList <T1> items,const T2 issel,const T3 tmpX,const T3 tmpY)
{
    QListIterator <T1> it(items);
    while (it.hasNext())
    {
        T1 dev = it.next();
        if (isAreaDevice(tmpX,tmpY,dev))
        {
            dev->setIsSelected(issel);
        }

    }
}

Field::Field(QWidget * parent):QGLWidget(QGLFormat(QGL::SampleBuffers),parent),
R1(0.831),G1(0.815),B1(0.784),
R2(0.87),G2(0.855),B2(0.824),
flagAddLinkRegime(true),
tmpBeg(-1),
tmpText(-1),
tmpEnd(-1),
tmpX(0),
tmpY(0),
blockX(0),
blockY(0),
shiftX(0),
shiftY(0),
shiftTranslateX(0),
shiftTranslateY(0),
shiftMode(false),
selectMode(false),
additionSelectionMode(false)
{
    this->items.clear();
    this->links.clear();
    
    this->setAutoBufferSwap(true);
    this->installEventFilter(this);
    QObject::connect(this,SIGNAL(newLinkAdded(int,int)),this,SLOT(SlotAddChannel(int,int)));
}

Field::~Field()
{
    
}

void Field::setcheckDevice(DeviceType create_new_dev)
{
    create_dev = create_new_dev;
}

//устанавливает и возвращает цвет заливки рабочего поля
void Field::setColor(int r1, int g1, int b1, int r2, int g2, int b2)
{
    R1 = GLfloat(1.*r1/255.); R2 = GLfloat(1.*r2/255.);
    G1 = GLfloat(1.*g1/255.); G2 = GLfloat(1.*g2/255.);
    B1 = GLfloat(1.*b1/255.); B2 = GLfloat(1.*b2/255.);
}
void Field::getColor(int &r1, int &g1, int &b1, int &r2, int &g2, int &b2)
{
    r1 = int(R1*255); r2 = int(R2*255);
    g1 = int(G1*255); g2 = int(G2*255);
    b1 = int(B1*255); b2 = int(B2*255);
}
//---------------------------------------

//стандартные функции OpenGL
void Field::initializeGL()
{
    glDisable(GL_DEPTH_TEST);
    glClearColor(1,1,1,1);
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//по изменению размера рабочего поля
void Field::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    this->updateGL();
}

//Главная функция отрисовки рабочего поля
void Field::paintGL()
{
    if (!this->isVisible())
        return;
    this->makeCurrent();
    int w = this->QWidget::width();
    int h = this->QWidget::height();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0,w,h,0,-1000,1000);
    QRect selArea(this->selectedArea);
    //glColor3f(0.0,1.0,0.0);
    selArea.moveTopLeft(QPoint(selectedArea.left()-this->shiftTranslateX, selectedArea.top()-this->shiftTranslateY));
    int M = w*0.5;
    /****************************Начало рабочего поля ********************************/
    glBegin(GL_POLYGON);
    glColor3f(R1,G1,B1);
    glVertex3f(0,0,0);
    glColor3f(R2,G2,B2);
    glVertex3f(M,0,0);
    glVertex3f(M,h,0);
    glColor3f(R1,G1,B1);
    glVertex3f(0,h,0);
    glEnd();
    
    
    glBegin(GL_POLYGON);
    glColor3f(R1,G1,B1);
    glVertex3f(w,0,0);
    glColor3f(R2,G2,B2);
    glVertex3f(M,0,0);
    glVertex3f(M,h,0);
    glColor3f(R1,G1,B1);
    glVertex3f(w,h,0);
    glEnd();
    
    
    glLineWidth(2);
    glTranslatef(0,0,1);
    glBegin(GL_LINE_STRIP);
    glColor3f(R1,G1,B1);
    glVertex3f(M,3,0);
    glColor3f(R2,G2,B2);
    glVertex3f(3,3,0);
    glVertex3f(3,h-3,0);
    glColor3f(R1,G1,B1);
    glVertex3f(M,h-3,0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(R1,G1,B1);
    glVertex3f(M,3,0);
    glColor3f(R2,G2,B2);
    glVertex3f(w-3,3,0);
    glVertex3f(w-3,h-3,0);
    glColor3f(R1,G1,B1);
    glVertex3f(M,h-3,0);
    glEnd();
    /****************************Конец рабочего поля ********************************/
    if (!wallpaperGL.isNull())
    {
        GLfloat yImg = h;
        GLfloat xImg = 0;
        bool isFirst = true;
        while ((xImg<w) || (isFirst))
        {
            yImg = h;
            while ((yImg>0) || (isFirst))
            {
                glRasterPos2f(xImg,yImg);
                glDrawPixels(wallpaperGL.width(), wallpaperGL.height(), GL_RGBA, GL_UNSIGNED_BYTE, wallpaperGL.bits());
                yImg = yImg - wallpaperGL.height();
                isFirst = false;
            }
            xImg = xImg + wallpaperGL.width();
        }
        
    }
    glTranslatef(this->shiftTranslateX, this->shiftTranslateY, 0);
    //int cntt = (flagAnimation) ? ani.elapsed()*this->speedAnimation : 0;
    glTranslatef(0,0,1);
    if (tmpBeg>-1)
    {
        Device * begining = this->items[this->tmpBeg];
        GLfloat x1 = begining->x()+begining->width()/2-50;
        GLfloat y1 = begining->y()+begining->height()/2-20;
        
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
        
        
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_XOR);
        glColor3f(1,1,1);
        glLineWidth(4.5);
        
        glBegin(GL_LINE);
        glVertex2f(x1,y1);
        glVertex2f(tmpX, tmpY);
        glEnd();
        
        glDisable(GL_COLOR_LOGIC_OP);
        //painter.end();
        
        /*
          
        glEnable(GL_LINE_SMOOTH);
        //glEnable(GL_LINE_STIPPLE);
        glEnable(GL_POINT_SMOOTH_HINT);
        glEnable(GL_COLOR_LOGIC_OP);
        
        glLogicOp(GL_XOR);
        glColor3f(1,1,1);
        //glLineStipple(5, 0xFCFC);
        // glLineStipple(2, 0xAAAA);
        // glLineStipple(2, 0x00FF);
        glLineWidth(4);
        
        glShadeModel(GL_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
        
        glBegin(GL_LINE);
        glVertex2f(x1,y1);
        glVertex2f(tmpX, tmpY);
        glEnd();
        
        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1);
        */
        /*
        glBegin(GL_LINES);
            glVertex2f(tmpX-50,tmpY);
            glVertex2f(tmpX+50,tmpY);
            glVertex2f(tmpX,tmpY-50);
            glVertex2f(tmpX,tmpY+50);
        glEnd();
        */
        //glLineWidth(2);
        /*
        glBegin(GL_LINE_LOOP);
            glVertex2f(tmpX-20,tmpY-20);
            glVertex2f(tmpX+20,tmpY-20);
            glVertex2f(tmpX+20,tmpY+20);
            glVertex2f(tmpX-20,tmpY+20);
        glEnd();
        
        glDisable(GL_COLOR_LOGIC_OP);
        //glDisable(GL_LINE_STIPPLE);
        glDisable(GL_POINT_SMOOTH_HINT);
        */
    }
    //glLineStipple(2,0x00FF);
    for (int i=0;i<this->links.count();i++)
    {
        Link *theLink = this->links[i];
        if (this->selectMode)
        {
            bool isSelected = selArea.contains(theLink->getCentralArea());
            if (this->additionSelectionMode)
                isSelected = isSelected || theLink->isSelected();
            theLink->setIsSelected(isSelected);
        }
        theLink->paint(1);
    }
    
    glTranslatef(0,0,1);

    for (int i=0;i<items.count();i++)
    {
        glPushMatrix();
        Device * theBlock = this->items[i];
        glTranslatef(theBlock->x()-30,theBlock->y()-30,i*2);
        
        if (this->selectMode)
        {
            bool isSelected = (selArea.contains(theBlock->x(),theBlock->y()));
            if (this->additionSelectionMode)
                isSelected = isSelected || theBlock->getIsSelected();
            theBlock->setIsSelected(isSelected);
        }
        
        theBlock->paint();
        glPopMatrix();
    }

    
    if (this->selectMode)
    {
        //glPushAttrib(GL_ENABLE_BIT);
        /*
        glEnable(GL_BLEND);
        //        if (this->additionSelectionMode)
        //            glColor4f(1,1,0,0);
        //        else
        glColor4f(0.5,0,1,0);
        
        glBegin(GL_POLYGON);
        glVertex2f(selArea.left(),selArea.top());
        glVertex2f(selArea.right(),selArea.top());
        glVertex2f(selArea.right(),selArea.bottom());
        glVertex2f(selArea.left(),selArea.bottom());
        glEnd();
        
        glDisable(GL_BLEND);
        */
        glEnable(GL_COLOR_LOGIC_OP);
        glDisable(GL_DEPTH_TEST);
        glLogicOp(GL_XOR);
        glEnable(GL_LINE_STIPPLE);
        glLineWidth(3);
        glLineStipple(2,0xCCCC);
        //        if (this->additionSelectionMode)
        //            glLineStipple(1,0xCCCC);
        //        else
        
        //Выделение мышкой
        glLineStipple(2,0x00FF);
        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
        glVertex2f(selArea.left(),selArea.top());
        glVertex2f(selArea.right(),selArea.top());
        glVertex2f(selArea.right(),selArea.bottom());
        glVertex2f(selArea.left(),selArea.bottom());
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        //        if (this->additionSelectionMode)
        //        {
        //            glLineWidth(3);
        //            const GLfloat afb = 5;
        //            GLfloat left = selArea.left();
        //            GLfloat right = selArea.right();
        //            if (selArea.left() > selArea.right())
        //            {
        //                left = selArea.right();
        //                right = selArea.left();
        //            }
        //            GLfloat top = selArea.top();
        //            GLfloat bottom = selArea.bottom();
        //            if (selArea.bottom() < selArea.top())
        //            {
        //                top = selArea.bottom();
        //                bottom = selArea.top();
        //            }
        //            glBegin(GL_LINE_LOOP);
        //              glVertex2f(left-afb, top-afb);
        //              glVertex2f(right+afb, top-afb);
        //              glVertex2f(right+afb, bottom+afb);
        //              glVertex2f(left-afb, bottom+afb);
        //            glEnd();
        //        }
        glTranslatef(-this->shiftTranslateX, -this->shiftTranslateY, 0);
        //        if (this->selectMode)
        //        {
        //            if (additionSelectionMode)
        //                this->renderText(15+imgInfo.width(),10+imgInfo.height(),0, QString::fromLocal8Bit("бШДЕКЕМХЕ Я ДНАЮБКЕМХЕЛ Й ОПЕДШДСЫЕЛС"));
        //            else
        //                this->renderText(15+imgInfo.width(),10+imgInfo.height(),0, QString::fromLocal8Bit("бШДЕКЕМХЕ ЯН ЯАПНЯНЛ ОПЕДШДСЫЕЦН"));
        //        }
        
        glDisable(GL_COLOR_LOGIC_OP);
        /*        glEnable(GL_BLEND);
        glRasterPos2f(10,10+imgInfo.height());
        glDrawPixels(imgInfo.width(), imgInfo.height(), GL_RGBA, GL_UNSIGNED_BYTE, imgInfo.bits());
        glDisable(GL_BLEND);*/
        glPopAttrib();
    }
}
//---------------------------------------

void Field::contextMenuEvent(QContextMenuEvent *e)
{
}
//--- Фильтр событий ---
bool Field::eventFilter(QObject *obj, QEvent *evnt)
{
    qDebug()<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    QMouseEvent * me = dynamic_cast<QMouseEvent *>(evnt);
    if (me)
    {
        this->tmpX = me->pos().x()-this->shiftTranslateX;
        this->tmpY = me->pos().y()-this->shiftTranslateY;
        qDebug()<<"this->tmpX"<<this->tmpX<<"this->tmpY"<<this->tmpY;
        
    }
    
    if (evnt->type() == QEvent::MouseButtonPress)
    {
        if (me->button() == Qt::MidButton)
        {
            this->shiftMode = true;
            this->shiftX = this->tmpX;
            this->shiftY = this->tmpY;
        }
        else
        {
            this->additionSelectionMode = (me->button() == Qt::RightButton);
            this->movingBlock = 0;
            this->movingText = 0;
            this->movingText2 = 0;
            this->tmpBeg = -1;
            this->tmpText = -1;
            this->tmpText2 = -1;
            this->selectMode = false;
            /*
            for (int i=links.size()-1;(i>=0);i--)
            {
                Link * lnk = this->links.at(i);
                qDebug()<<">>>>>>>>>>>>>>>>>>>Link * lnk = this->links.at(i);";
                QPoint shiftedPoint(tmpX, tmpY);
                if (lnk->getCentralArea().contains(shiftedPoint))
                {
                      qDebug()<<"lnk->getCentralArea()";

                    this->movingBlock = lnk->begining;
                    for (int j=0;j<this->items.size();j++)
                    {
                        if (items.at(j) == this->movingBlock)
                        {
                            this->tmpBeg = j;
                            this->tmpText = j;
                            this->tmpText2 = j;
                            break;
                        }
                    }
                    this->delLink(i);
                    emit SignalDelChan(i);
                    break;
                }
            }
            */
            for (int i=items.count()-1;i>=0;i--)
            {
                Device * theBlock = items[i];
                if (isAreaDevice(tmpX,tmpY,theBlock))
                {
                    this->blockX = tmpX - theBlock->x();
                    this->blockY = tmpY  - theBlock->y();
                    this->movingBlock = theBlock;
                    if (additionSelectionMode)
                    {
                        this->tmpBeg = i;
                    }
                    break;
                }
            }
            for (int i=links.size()-1;(i>=0);i--)
            {
                Link * lnk = this->links.at(i);
                if (isAreaDevice(tmpX,tmpY,lnk->txt1))
                {

                    this->t_blockX = tmpX - lnk->txt1->x();
                    this->t_blockY = tmpY - lnk->txt1->y();
                    this->movingText = lnk->txt1;
                    //this->movingText->setIsSelected(true);
                    this->movingText->paint();
                    this->tmpText = i;
                    qDebug()<<"***********I = "<<i;
                    if (additionSelectionMode)
                    {
                        this->tmpText = i;
                    }
                    break;

                }
            }

            for (int i=links.size()-1;(i>=0);i--)
            {
                Link * lnk1 = this->links.at(i);
                qDebug()<<"Try find movingText ";
                if (isAreaDevice(tmpX,tmpY,lnk1->txt2))
                {

                    this->t_blockX = tmpX - lnk1->txt2->x();
                    this->t_blockY = tmpY - lnk1->txt2->y();

                    this->movingText2 = lnk1->txt2;
                    this->movingText2->paint();
                    this->tmpText2 = i;
                    if (additionSelectionMode)
                    {
                        this->tmpText2 = i;
                    }
                    break;

                }
            }
            qDebug()<<"****************************************************************";


            if ((!movingBlock) && (tmpBeg==-1) && ((tmpText==-1) && (tmpText2==-1)))
            {
                this->selectMode = true;
                this->selectedArea.setTopLeft(me->pos());
                this->selectedArea.setBottomRight(me->pos());
            }

            this->updateGL();
        }
        
        
        if (me->button()==Qt::LeftButton)
        {
            Device *dev;
            switch(create_dev)
            {
                
            case COMPUTER:             
                dev = new Device(this,this->tmpX,this->tmpY,create_dev,"","");
                this->appendItem(dev);
                
                emit setDefault();
                break;
            case ROUTER:
                dev = new Device(this,this->tmpX,this->tmpY,create_dev,"","");
                this->appendItem(dev);
                emit setDefault();
                break;
            case RADIO:
                dev = new Device(this,this->tmpX,this->tmpY,create_dev,"","");
                this->appendItem(dev);
                emit setDefault();
                break;
            case LINK:                
                this->additionSelectionMode = (me->button() == Qt::LeftButton);
                this->movingBlock = 0;
                this->movingText = 0;
                 this->movingText2 = 0;
                //this->tmpBeg = -1;
                //this->tmpText = -1;
                this->selectMode = false;
                
                for (int i=links.size()-1;(i>=0);i--)
                {
                    Link * lnk = this->links.at(i);
                    QPoint shiftedPoint(tmpX, tmpY);
                    if (lnk->getCentralArea().contains(shiftedPoint))
                    {
                        this->movingBlock = lnk->begining;
                        for (int j=0;j<this->items.size();j++)
                        {
                            if (items.at(j) == this->movingBlock)
                            {
                                this->tmpBeg = j;
                                break;
                            }
                        }
                        this->delLink(i);
                        emit SignalDelChan(i);
                        break;
                    }
                    
                }
                
                for (int i=items.count()-1;i>=0;i--)
                {
                    Device * theBlock = items[i];
                    if (isAreaDevice(tmpX,tmpY,theBlock))
                    {
                        theBlock->setIsSelected(true);
                        this->blockX = tmpX - theBlock->x();
                        this->blockY = tmpY  - theBlock->y();
                        this->movingBlock = theBlock;
                        if (additionSelectionMode)
                        {
                            this->tmpBeg = i;
                        }
                        break;
                    }
                }

                if ((!movingBlock) && (tmpBeg==-1))
                {
                    this->selectMode = true;
                    this->selectedArea.setTopLeft(me->pos());
                    this->selectedArea.setBottomRight(me->pos());
                }


                break;
                
            case DEFAULT:
            default:
                setSelect(items,true,tmpX,tmpY);
                break;
            }
            this->updateGL();
        } 
    }
    if (evnt->type() == QEvent::MouseButtonRelease)
    {
        if (me->button()==Qt::RightButton)
        {
            contextMenu(items,tmpX,tmpY,me,this);
        }
        if (me->button()==Qt::LeftButton)
        {
            this->shiftMode = false;
            this->selectMode = false;
            this->selectedArea = QRect();
            this->movingBlock = 0;
            for (int i=items.count()-1;i>=0;i--)
            {
                Device * theBlock = items[i];
                if (isAreaDevice(tmpX,tmpY,theBlock))
                {
                    qDebug()<<"is area";
                    if (tmpBeg>-1)
                    {
                        this->tmpEnd = i;
                        if (tmpBeg!=tmpEnd)
                        {
                            emit this->newLinkAdded(tmpBeg, tmpEnd);
                            SlotAddChannel(tmpBeg,tmpEnd);
                        }
                    }
                    break;
                }
            }
            tmpBeg = -1;
            tmpEnd = -1;            
            this->updateGL();
        }

    }

    //перетаскивание всей мнемосхемы колёсиком
    if ((evnt->type() == QEvent::MouseMove) && (shiftMode))
    {

        this->shiftTranslateX = me->pos().x() - this->shiftX;
        this->shiftTranslateY = me->pos().y() -  this->shiftY;
        this->updateGL();

    }

/*
        if (evnt->type() == QEvent::MouseMove)
    {

        this->shiftTranslateX = me->pos().x() - this->shiftX;
        this->shiftTranslateY = me->pos().y() -  this->shiftY;
        this->updateGL();

    }
        */
    if ((evnt->type() == QEvent::MouseMove) && (movingBlock) && (!shiftMode))
    {
        // Перетаскивание обьекта с помощью мышки
        //Move object with the mouse
        // qDebug()<<"QEvent::MouseMove) && (movingBlock) && (!shiftMode) ";
        if (tmpBeg == -1)
            movingBlock->move(tmpX-this->blockX, tmpY-this->blockY);
        this->updateGL();

    }

    if ((evnt->type() == QEvent::MouseMove) &&  (movingText) && (!shiftMode))
    {
        // Перетаскивание обьекта с помощью мышки
        //Move object with the mouse
        if (tmpText >-1)
            movingText->move(tmpX-this->t_blockX, tmpY-this->t_blockY);
        this->updateGL();
    }

        if ((evnt->type() == QEvent::MouseMove) && (movingText2) && (!shiftMode))
    {
        // Перетаскивание обьекта с помощью мышки
        //Move object with the mouse
        if (tmpText2 >-1)
            movingText2->move(tmpX-this->t_blockX, tmpY-this->t_blockY);
        this->updateGL();
    }

    if ((evnt->type() == QEvent::MouseMove) && (this->selectMode) && (!shiftMode))
    {
        //Выделение мышкой
        this->selectedArea.setBottomRight(QPoint(me->pos()));
        this->updateGL();

    }

    if (evnt->type() == QEvent::MouseButtonDblClick)
    {

    }


    return QWidget::eventFilter(obj,evnt);
}
//---------------------------------------

//--- Устанавливает и возвращает признак редактирования связей ---
void Field::setEditRegime(bool er)
{
    this->flagAddLinkRegime = er;
    this->updateGL();
}
bool Field::getEditRegime()
{
    return this->flagAddLinkRegime;
}
//---------------------------------------


void Field::createTerminal()
{
    TelnetForm *w = new TelnetForm();
    PresenterTelnet *presenterTelnet = new PresenterTelnet(w);
    Q_UNUSED(presenterTelnet);
    w->show();
}
void Field::createProperty()
{
    Device * select  = getLastSelectedItem();
    select->edit->show();
   // qDebug()<<"TXT1"<<select->getLink(0)->txt1->getText();
    qDebug()<<"TXT2"<<select->getLink(0)->txt2->getText();
     //select->edit->setName()
    //select
}

//работа со списком элементов мнемосхемы
void Field::addItem(int x, int y,DeviceType type/*QString name,int type,QString address,QString image,QString name*/)
{
    Device * theItem = new Device(this,x,y,type,"","");
    //net_node * theItem = new net_node(this, name, type,address,300,150);
    this->items.append(theItem);
}

void Field::appendItem(Device * newItem)
{
    if (newItem)
        items.append(newItem);
}
//установка и возврат значении сдвигов(перемещений)
void Field::setShiftTranslateX(int newX)
{
    this->shiftTranslateX = newX;
}
int Field::getShiftTranslateX() const
{
    return this->shiftTranslateX;
}
void Field::setShiftTranslateY(int newY)
{
    this->shiftTranslateY = newY;
}
int Field::getShiftTranslateY() const
{
    return this->shiftTranslateY;
}
//---------------------------------------


//установка фонового изображения
void Field::setWallpaper(QImage & img)
{
    this->wallpaper = img;
    this->wallpaperGL = QGLWidget::convertToGLFormat(img);
}
QImage Field::getWallpaper() const
{
    return this->wallpaper;
}
QImage Field::getWallpaperGL() const
{
    return this->wallpaperGL;
}


//Возврат листа с описанием узлов и каналов связи
QList <Device *> Field::getLstNode()
{
    return items;
}

QList <Link *> Field::getLstChannel()
{
    return links;
}

void Field::appendLink(Link * newLink)
{
    if (newLink)
        this->links.append(newLink);
}
void Field::delLink(int num)
{
    if (!((num>=0) && (num<this->links.size())))
        return;
    Link * theLink = this->links.at(num);
    delete theLink;
    links.removeAt(num);
}


void Field::delItem(int num)
{
    qDebug()<<"Field::delItem";
    if (!((num>=0) && (num<this->items.size())))
        return;
    Device * theItem = items.at(num);
    delete theItem;
    items.removeAt(num);
}

int Field::getItemsCount() const
{
    qDebug()<<"Field::getItemsCount";
    return this->items.size();

}

void Field::clearItems()
{
    qDebug()<<"Field::clearItems ";
    this->clearLinks();
    while (items.size())
    {
        Device * theItem = items.last();
        delete theItem;
        items.removeLast();
    }
    this->items.clear();
}

Device * Field::getItem(int num) const
{
    qDebug()<<"Field::getItem";
    if ((num>=0) && (num<this->items.size()))
        return items.at(num);
    else
        return 0;
}

Device * Field::getLastSelectedItem()
{
    qDebug()<<"Field::getLastSelectedItem";
    int num = -1;
    for (int i=items.size()-1;i>=0;i--)
    {
        Device * theItem = items.at(i);
        if (theItem->getIsSelected())
        {
            num = i;
            break;
        };
    }
    for (int i=0;i<num;i++)
        items.at(i)->setIsSelected(false);
    return this->getItem(num);
}

Link * Field::addLinkByNum(int begNum, int endNum)
{
    qDebug()<<"Field::addLinkByNum";
    Device * beg = this->getItem(begNum);
    Device * end = this->getItem(endNum);
    if ((beg==0) || (end==0))
        return 0;
    return this->addLink(beg, end);

}
Link * Field::addLink(Device * beg, Device * end)
{
    qDebug()<<"Field::addLink";
    Link * theLink = new Link(this,beg, end,"",0,4,"","",0,0,0,0);
    this->links.append(theLink);
    return theLink;
}
Link * Field::getLink(int num) const
{
    if ((num>=0) && (num<this->links.size()))
        return links.at(num);
    else
        return 0;
}
int Field::getLinksCount() const
{
    qDebug()<<"Field::getLinksCount";
    return this->links.size();
}
void Field::clearLinks()
{
    qDebug()<<"Field::clearLinks";
    while (links.size())
    {
        Link * theLink = links.last();
        delete theLink;
        links.removeLast();
    }
    this->links.clear();
}

void Field::addRoute(int route)
{
    qDebug()<<"addRoute() = "<<route;
    switch (route)
    {
    case 1:
        append(links,route1);
        break;
    case 2:
        append(links,route2);
        break;
    case 3:
        append(links,route3);
        qDebug()<<"-----------------------------------------route3"<<route3;
        break;
                default:
        break;
    }

    /*
        for (int i=links.size()-1;(i>=0);i--)
        {
            //this->links
            Link * lnk = this->links.at(i);
            if (lnk->isActive)
            {
                qDebug()<<"isActive";
                qDebug()<<"lnk"<<lnk;
                //route3.append(lnk);
                route3.append(this->links.at(i));
                
            }
            
            
            //lnk->active = active;
            //lnk->paint(0);
            //qDebug()<<"iter";
            //  qDebug()<<"Element"<<*lnk;
        }
        qDebug()<<"route3"<<route3;
        */
}

void Field::showRoute(int route, bool active)
{
    qDebug()<<"-----------------------------------------showRoute";
    switch (route)
    {
                case 1:
        setActiveRoute(route1,active);
        break;
    case 2:
        setActiveRoute(route2,active);
        break;
    case 3:
        setActiveRoute(route3,active);
        this->repaint();
        qDebug()<<"-----------------------------------------setActiveRoute(route3)"<<route3;
        break;
                default:
        break;
    }
    //setActiveRoute(route3,active);

    this->repaint();
}

void Field::setActive(bool active)
{
    setActiveRoute(links,active);
    this->repaint();
}
void Field::setInfo(bool active)
{
      //work_field->showInfo(show);
    setInform(links,active);
    //this->setInfo();
    this->repaint();
}

void Field::SlotAddChannel(int indBeg, int indEnd)
{
    qDebug()<<"SlotAddChannel";
    for (int i=0;i<this->getLinksCount();i++)
    {
        Link * chanel = this->getLink(i);
        int beg = -1;
        int end = -1;
        for (int j=0; j<this->getItemsCount(); j++)
        {
            Device * nd = this->getItem(j);
            if (nd == chanel->begining)
                beg = j;
            if (nd == chanel->ending)
                end = j;
        }
        if ((beg == indBeg) && (end == indEnd))
        {
            /*
            QMessageDlg(mtWarning, this, this->windowTitle().append(0x20),
                        QString::fromLocal8Bit(msgChannel),QString::fromLocal8Bit(msgCancel));
            */
            return;
        }
    }
    qDebug()<<"SlotAddChannel Device";
    Device * blockBegin = this->getItem(indBeg);
    blockBegin->link++;
    Device * blockEnd = this->getItem(indEnd);
    blockEnd->link++;

    //ДХЮКНЦ ЯБНИЯРБ ЙЮМЮКЮ ЯБЪГХ
    /*
    frm_add *add = new frm_add(this);
        add->setType(1);
    add->exec();*/
    //if(add->result()==QDialog::Accepted)
    //{
    //ЯНГДЮЕЛ ЙЮМЮК ЯБЪГХ
    Link * ch = new Link(this,blockBegin, blockEnd,"Имя",0,4,"","",0,0,0,0);
    //Link(Device * first, Device * last, QString theName, int theType, int theWidth);
    //ДНАЮБКЪЕЛ ЕЦН МЮ ПЮАНВЕЕ ОНКЕ
    this->appendLink(ch);
    //ЯНГДЮЕЛ ЯРПСЙРСПС ДКЪ НРНАПЮФЕМХЪ ЙЮМЮКЮ Б РЮАКХЖЕ
    /*
        StChan *cha = new Struct_Channel(add->getName(),blockBegin->getName(),blockEnd->getName(),
                                         QString::fromLocal8Bit(uzNotActiv),add->getLocalType());
        lstTblChan<<cha;
        if(chan)
        {
            chanel->CreateTblChannel(lstTblChan);
        }
        */

    //}
    //delete add;
}


