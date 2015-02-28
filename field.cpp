#include "field.h"
#include <QDebug>
#include <QApplication>
#include <QMenu>
#include <QAction>
#include "presentertelnet.h"
#include "telnetform.h"

#define IS(x1,x0,delta) ((x1>x0-delta)&&(x1<x0+delta))?1:0

Field::Field(QWidget * parent):QGLWidget(parent),
R1(0.831),G1(0.815),B1(0.784),
R2(0.87),G2(0.855),B2(0.824),
//  flagAnimation (false),
//speedAnimation(1),
flagAddLinkRegime(true),
tmpBeg(-1),
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
    //this->items.clear();
    //this->links.clear();

    this->setAutoBufferSwap(true);
    //ani.start();
    this->installEventFilter(this);
}

Field::~Field()
{

}


//утсанавливает и возвращает признак и скорость анимации
/*
void Field::setIsAnimation(bool isAni)
{
    this->flagAnimation = isAni;
}
bool Field::isAnimation()
{
    return this->flagAnimation;
}
void Field::setAnimationSpeed(int newSpeed)
{
    this->speedAnimation = newSpeed;
}
int Field::getAnimationSpeed()
{
    return this->speedAnimation;
}
*/
//---------------------------------------

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
    //glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_ALPHA_TEST);
    //glDisable(GL_LOGIC_OP);
    glClearColor(1,1,1,1);
    //glClear(GL_COLOR_BUFFER_BIT);
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
    qDebug()<<"paintGL";
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
    selArea.moveTopLeft(QPoint(selectedArea.left()-this->shiftTranslateX, selectedArea.top()-this->shiftTranslateY));
    int M = w*0.5;
    /*
    if (flagAnimation)
    {
        int cnt = ani.elapsed()*this->speedAnimation;
        M += 0.33*w*sin(cnt/3000.);
    }
    */
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
        /*
        net_node * begining = this->items[this->tmpBeg];
        GLfloat x1 = begining->x()+begining->width();
        GLfloat y1 = begining->y()+begining->height()/2;
        glEnable(GL_LINE_STIPPLE);
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_XOR);
        glColor3f(1,1,1);
        glLineStipple(5, 0xFCFC);
        glLineWidth(5);
        glBegin(GL_LINES);
            glVertex2f(x1,y1);
            glVertex2f(tmpX, tmpY);
        glEnd();
        glDisable(GL_LINE_STIPPLE);
        glLineWidth(1);
        glBegin(GL_LINES);
            glVertex2f(tmpX-50,tmpY);
            glVertex2f(tmpX+50,tmpY);
            glVertex2f(tmpX,tmpY-50);
            glVertex2f(tmpX,tmpY+50);
        glEnd();
        glLineWidth(2);
        glBegin(GL_LINE_LOOP);
            glVertex2f(tmpX-20,tmpY-20);
            glVertex2f(tmpX+20,tmpY-20);
            glVertex2f(tmpX+20,tmpY+20);
            glVertex2f(tmpX-20,tmpY+20);
        glEnd();
        glDisable(GL_COLOR_LOGIC_OP);
        glDisable(GL_LINE_STIPPLE);
        */
    }
    /*
    for (int i=0;i<this->links.count();i++)
    {
        net_channel *theLink = this->links[i];
        if (this->selectMode)
        {
            bool isSelected = selArea.contains(theLink->getCentralArea());
            if (this->additionSelectionMode)
                isSelected = isSelected || theLink->isSelected();
            theLink->setIsSelected(isSelected);
        }
        theLink->paint(cntt);
    }
    */
    glTranslatef(0,0,1);

    for (int i=0;i<items.count();i++)
    {
        glPushMatrix();
        Device * theBlock = this->items[i];
        glTranslatef(theBlock->x()-30,theBlock->y()-30,i*2);
        /*
        if (this->selectMode)
        {
            bool isSelected = (selArea.contains(theBlock->x(),theBlock->y()));
            if (this->additionSelectionMode)
                isSelected = isSelected || theBlock->getIsSelected();
            theBlock->setIsSelected(isSelected);
        }
        */
        theBlock->paint();
        glPopMatrix();
    }

    if (this->selectMode)
    {
        glPushAttrib(GL_ENABLE_BIT);

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
        glEnable(GL_COLOR_LOGIC_OP);
        glDisable(GL_DEPTH_TEST);
        glLogicOp(GL_XOR);
        glEnable(GL_LINE_STIPPLE);
        glLineWidth(3);
        glLineStipple(2,0xCCCC);
        //        if (this->additionSelectionMode)
        //            glLineStipple(1,0xCCCC);
        //        else
        glLineStipple(2,0x00FF);
        glColor3f(1,1,1);
        glBegin(GL_LINE_LOOP);
        glVertex2f(selArea.left(),selArea.top());
        glVertex2f(selArea.right(),selArea.top());
        glVertex2f(selArea.right(),selArea.bottom());
        glVertex2f(selArea.left(),selArea.bottom());
        glEnd();
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
    /*
     qDebug()<<"contextMenuEvent";
     QMenu menu(this);
     QAction *action1 = new QAction(QString::fromLocal8Bit("Пункт 0"), this);
     menu.addAction(action1);
     menu.addSeparator();
      QAction *action2 = new QAction(QString::fromLocal8Bit("Пункт 2"), this);
      action2->setIcon(QIcon(":/img/img/workstation_256.png"));
      menu.addAction(action2);
      // menu.addAction();
      menu.exec(e->globalPos());
      */
}

/*
void Field::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::RightButton)
    {
        qDebug()<<"MouseButtonPress RightButton";
        qDebug()<<"contextMenuEvent";
        QMenu menu(this);
        QAction *action1 = new QAction(QString::fromLocal8Bit("Пункт 0"), this);
        menu.addAction(action1);
        menu.addSeparator();
        QAction *action2 = new QAction(QString::fromLocal8Bit("Пункт 2"), this);
        action2->setIcon(QIcon(":/img/img/workstation_256.png"));
        menu.addAction(action2);
        // menu.addAction();
        menu.exec(event->globalPos());
        for (QList <Device *>::const_iterator it = items.constBegin();it !=items.constEnd();++it)
        {
               qDebug()<<"iterator";

        }
         qDebug()<<"iterator end";
       // while ( )


    }

}*/
//--- Фильтр событий ---
bool Field::eventFilter(QObject *obj, QEvent *evnt)
{
    //qDebug()<<"Фильтр событий ";
    QMouseEvent * me = dynamic_cast<QMouseEvent *>(evnt);
    if (me)
    {


        this->tmpX = me->pos().x()-this->shiftTranslateX;
        this->tmpY = me->pos().y()-this->shiftTranslateY;
         qDebug()<<"tmpX"<<this->tmpX<<"tmpY"<<this->tmpY;
                 //qDebug()<<"dev y = "<<dev->y();

    }
/*
    switch (evnt->type())
    {
            case QEvent::MouseButtonPress:
        //qDebug()<<"MouseButtonPress";

        if (evnt->button()==Qt::RightButton)
            {
                qDebug()<<"MouseButtonPress RightButton";
            }
        break;
            default:
        //qDebug()<<"DEFAULT";
        break;
    }
    */

    /*
        if ((evnt->type() == QEvent::MouseButtonPress)&&(QApplication::mouseButtons()==Qt::RightButton))
    {
             // qDebug()<<"MouseButtonPress Right";
    }
        if ((evnt->type() == QEvent::MouseButtonPress)&&(QApplication::mouseButtons()==Qt::LeftButton))
    {
          //  qDebug()<<"MouseButtonPress Left";
        }
        */

    if (evnt->type() == QEvent::MouseButtonPress)
    {
        //event->button()==Qt::RightButton

        // qDebug()<<"MouseButtonPress";
        /*
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
            this->tmpBeg = -1;
            this->selectMode = false;

            for (int i=links.size()-1;(i>=0);i--)
            {
                net_channel * lnk = this->links.at(i);
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
                net_node * theBlock = items[i];
                if ((tmpX>theBlock->x()) && (tmpX < theBlock->x()+theBlock->width())
                    && (tmpY>theBlock->y()) && (tmpY < theBlock->y()+theBlock->height()))
                {
                    this->blockX = tmpX - theBlock->x();
                    this->blockY = tmpY  - theBlock->y();
                    this->movingBlock = theBlock;
                    if (additionSelectionMode)
                        this->tmpBeg = i;
                    break;
                }
            }

            if ((!movingBlock) && (tmpBeg==-1))
            {
                this->selectMode = true;
                this->selectedArea.setTopLeft(me->pos());
                this->selectedArea.setBottomRight(me->pos());
            }
        }
        this->updateGL();
        */
    }
    if (evnt->type() == QEvent::MouseButtonRelease)
    {
        qDebug()<<"MouseButtonRelease";
        if (me->button()==Qt::RightButton)
        {


            /*for (it;it !=items.constEnd();++it)
        {
              qDebug()<<"iterator x = "<<it.next()->x();
        }
        */
            qDebug()<<"tmpX = "<<this->tmpX ;
            qDebug()<<"tmpY = "<< this->tmpY ;
            QListIterator<Device *> it(items);
            while(it.hasNext())
            {

                int i = 1;
                //QString text = "Устройство"+ QString::number(i);
                Device * dev = it.next();
                //#define IS(x1,x0,delta) ((x1>x0-delta)&&(x1<x0+delta))?1:0
                if (IS(this->tmpX,dev->x(),10)&&IS(this->tmpY,dev->y(),10))
                {
                    qDebug()<<"MouseButtonPress RightButton++";

                    qDebug()<<"MouseButtonPress RightButton";
                    qDebug()<<"contextMenuEvent";

                    QMenu menu(this);
                    QAction *action1 = new QAction(QString::fromLocal8Bit(dev->getName().toLatin1()), this);
                    menu.addAction(action1);
                    QObject::connect(action1,SIGNAL(triggered()),this,SLOT(createTerminal()));
                    menu.addSeparator();
                    QAction *action2 = new QAction(QString::fromLocal8Bit("Пункт 2"), this);
                    action2->setIcon(QIcon(":/img/img/workstation_256.png"));
                    menu.addAction(action2);
                    // menu.addAction();
                    menu.exec(me->globalPos());



                    //QListIterator<Device *> it(items);
                    /*
                 qDebug()<<"dev x = "<<dev->x();
                 qDebug()<<"dev y = "<<dev->y();
                 */
                }
                /*
            if (dev->x()>)
            qDebug()<<"dev x = "<<dev->x();
            qDebug()<<"dev y = "<<dev->y();
            */
                //delete dev;
                i++;
                qDebug()<<"********************** ";
            }


            qDebug()<<"iterator end";



        }
        this->updateGL();
        /*
            this->shiftMode = false;
            this->selectMode = false;
            this->selectedArea = QRect();
            //this->movingBlock = 0;
            for (int i=items.count()-1;i>=0;i--)
            {
                Device * theBlock = items[i];
               /*
                if ((tmpX>theBlock->x()) && (tmpX < theBlock->x()+theBlock->width()) && (tmpY>theBlock->y()) && (tmpY < theBlock->y()+theBlock->height()))
                {
                    if (tmpBeg>-1)
                    {
                         this->tmpEnd = i;
                         if (tmpBeg!=tmpEnd)
                              emit this->newLinkAdded(tmpBeg, tmpEnd);
                    }
                    break;
                }
             }

             tmpBeg = -1;
             tmpEnd = -1;
             */
                //this->updateGL();

            }
            if ((evnt->type() == QEvent::MouseMove) && (shiftMode))
            {
                /*
        this->shiftTranslateX = me->pos().x() - this->shiftX;
        this->shiftTranslateY = me->pos().y() -  this->shiftY;
        this->updateGL();
        */
            }
            if ((evnt->type() == QEvent::MouseMove) /*&& (movingBlock)*/ && (!shiftMode))
            {/*
        if (tmpBeg == -1)
            movingBlock->move(tmpX-this->blockX, tmpY-this->blockY);
        this->updateGL();
        */
            }
            if ((evnt->type() == QEvent::MouseMove) && (this->selectMode) && (!shiftMode))
            {
                /*
        this->selectedArea.setBottomRight(QPoint(me->pos()));
        this->updateGL();
        */
            }
            if (evnt->type() == QEvent::MouseButtonDblClick)
            {
                /*
        if (me->button() == Qt::MidButton)
        {
            this->shiftTranslateX = 0;
            this->shiftTranslateY = 0;
            this->shiftX = 0;
            this->shiftY = 0;
        }
        for (int i=items.count()-1;i>=0;i--)
        {
            net_node * theBlock = items[i];
            if ((tmpX>theBlock->x()) && (tmpX < theBlock->x()+theBlock->width())
                && (tmpY>theBlock->y()) && (tmpY < theBlock->y()+theBlock->height()))
            {
                theBlock->isSel=true;
                updateGL();
                emit SignalEdit();
                break;
            }
        }
        this->updateGL();
        */
            }
            /*
    if (this->shiftMode)
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    else
        this->setCursor(Qt::ArrowCursor);*/
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

    //работа со списком элементов мнемосхемы
    void Field::addItem(int x, int y/*QString name,int type,QString address*/,QString image,QString name)
    {
        Device * theItem = new Device(this,x,y,image,name);
        //net_node * theItem = new net_node(this, name, type,address,300,150);
        this->items.append(theItem);
    }

    void Field::appendItem(Device * newItem)
    {
        if (newItem)
            items.append(newItem);
    }
    /*
void Field::delItem(int num)
{
    if (!((num>=0) && (num<this->items.size())))
        return;
    net_node * theItem = items.at(num);
    delete theItem;
    items.removeAt(num);
}
net_node * Field::getItem(int num) const
{
    if ((num>=0) && (num<this->items.size()))
        return items.at(num);
    else
        return 0;
}

int Field::getItemsCount() const
{
    return this->items.size();
}
void Field::clearItems()
{
    this->clearLinks();
    while (items.size())
    {
        net_node * theItem = items.last();
        delete theItem;
        items.removeLast();
    }
    this->items.clear();
}
net_node * Field::getLastSelectedItem()
{
    int num = -1;
    for (int i=items.size()-1;i>=0;i--)
    {
        net_node * theItem = items.at(i);
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
*/
    //---------------------------------------

    /*
//работа со списками связей элементов мнемосхемы
net_channel * Field::addLinkByNum(int begNum, int endNum)
{
    net_node * beg = this->getItem(begNum);
    net_node * end = this->getItem(endNum);
    if ((beg==0) || (end==0))
        return 0;
    return this->addLink(beg, end);
}
net_channel * Field::addLink(net_node * beg, net_node * end)
{
    net_channel * theLink = new net_channel(beg, end,"",0,4);
    this->links.append(theLink);
    return theLink;
}
void Field::appendLink(net_channel * newLink)
{
    if (newLink)
        this->links.append(newLink);
}
void Field::delLink(int num)
{
    if (!((num>=0) && (num<this->links.size())))
        return;
    net_channel * theLink = this->links.at(num);
    delete theLink;
    links.removeAt(num);
}
net_channel * Field::getLink(int num) const
{
    if ((num>=0) && (num<this->links.size()))
        return links.at(num);
    else
        return 0;
}
int Field::getLinksCount() const
{
    return this->links.size();
}
void Field::clearLinks()
{
    while (links.size())
    {
        net_channel * theLink = links.last();
        delete theLink;
        links.removeLast();
    }
    this->links.clear();
}
//---------------------------------------
*/
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
    /*
QList <net_channel *> work_field::getLstChannel()
{return links;}
*/
