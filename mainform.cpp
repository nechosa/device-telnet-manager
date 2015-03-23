#include "mainform.h"
#include "ui_mainform.h"

#include <QtGui>
#include <QtCore>
#include <QtXml>
#include <QDebug>
#include <QKeyEvent>
#include "device.cpp"

MainForm::MainForm(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainForm),key1(0),shift(false)
{
    ui->setupUi(this);


    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    QObject::connect(ui->action_add_comp,SIGNAL(triggered(bool)),this,SLOT(addComputer(bool)));
    QObject::connect(ui->action_add_router,SIGNAL(triggered(bool)),this,SLOT(addRouter(bool)));
    QObject::connect(ui->action_add_linc,SIGNAL(triggered(bool)),this,SLOT(addLinc(bool)));

    QObject::connect(ui->action_route1,SIGNAL(triggered(bool)),this,SLOT(selectRouter1(bool)));
    QObject::connect(ui->action_route2,SIGNAL(triggered(bool)),this,SLOT(selectRouter2(bool)));
    QObject::connect(ui->action_route3,SIGNAL(triggered(bool)),this,SLOT(selectRouter3(bool)));


    work_field = new Field(ui->gbShema);
    work_field->setFormat(QGLFormat(QGL::SampleBuffers));
    //work_field = QGLFormat::defaultFormat();
    //work_field->setSampleBuffers(true);
    //QGLFormat::setDefaultFormat(work_field);
     QObject::connect(work_field,SIGNAL(setDefault()),this,SLOT(setDefault()));

    //QObject::connect(work_field,SIGNAL(SignalEdit()),this,SLOT(SlotEdit()));
    //QObject::connect(work_field,SIGNAL(newLinkAdded(int,int)),this,SLOT(SlotAddChannel(int,int)));
    //QObject::connect(work_field,SIGNAL(SignalDelChan(int)),this,SLOT(SlotDelChan(int)));
    ui->gbShema->installEventFilter(this);
    work_field->setcheckDevice(DEFAULT);
    //work_field->setcheckDevice("DEFAULT");
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::setDefault()
{
     work_field->setcheckDevice(DEFAULT);
     ui->action_add_router->setChecked(false);
     ui->action_add_linc->setChecked(false);
     ui->action_add_comp->setChecked(false);
/*
     if (!shift)
     {

        shift = false;
     }
     */


}
void MainForm::addComputer(bool flag)
{
    if (flag)
    {
        //qDebug()<<"addComputer()";
        setCursor(Qt::ArrowCursor);
        ui->action_add_router->setChecked(false);
        ui->action_add_linc->setChecked(false);
        //work_field->setcheckDevice(COMPUTER);
        work_field->setcheckDevice(COMPUTER);
        // work_field->setcheckDevice(Computer);
    }
    else
    {
        this->setDefault();
    }


}

void MainForm::addRouter(bool flag)
{
    if (flag)
    {
        //qDebug()<<"addRouter()";
        setCursor(Qt::ArrowCursor);
        ui->action_add_comp->setChecked(false);
        ui->action_add_linc->setChecked(false);
        //work_field->setcheckDevice(ROUTER);
        work_field->setcheckDevice(ROUTER);
        // work_field->setcheckDevice(Router);
    }
    else
    {
        this->setDefault();

    }
}
void MainForm::addLinc(bool flag)
{
    // qDebug()<<"addLinc()";
    if (flag)
    {
        setCursor(Qt::CrossCursor);
        work_field->setcheckDevice(LINK);
        ui->action_add_router->setChecked(false);
        ui->action_add_comp->setChecked(false);
    }
    else
    {
        //work_field->setcheckDevice(LINK);
        this->setDefault();
        setCursor(Qt::ArrowCursor);
    }
    //action_add_linc
}

void MainForm::selectRouter1(bool flag)
{
    ui->action_route2->setChecked(false);
    ui->action_route2->setEnabled(false);
    ui->action_route3->setChecked(false);
    ui->action_route3->setEnabled(false);

    sleep(1);
    ui->action_route2->setEnabled(true);
    ui->action_route3->setEnabled(true);


 //ui->action_
    //ui->action_route

}
void MainForm::selectRouter2(bool flag)
{
    ui->action_route1->setChecked(false);
    ui->action_route1->setEnabled(false);
    ui->action_route3->setChecked(false);
    ui->action_route3->setEnabled(false);

    sleep(1);
    ui->action_route1->setEnabled(true);
    ui->action_route3->setEnabled(true);



}
void MainForm::selectRouter3(bool flag)
{
    ui->action_route1->setChecked(false);
    ui->action_route1->setEnabled(false);
    ui->action_route2->setChecked(false);
    ui->action_route2->setEnabled(false);

    sleep(1);
    ui->action_route1->setEnabled(true);
    ui->action_route2->setEnabled(true);



}
bool MainForm::eventFilter(QObject * obj, QEvent * evnt)
{
    // qDebug()<<"eventFilter()";
    //qDebug()<<"eventFilter()";
    //qDebug()<<"Фильтр событий ";
    QMouseEvent * me = dynamic_cast<QMouseEvent *>(evnt);
    /*
    QKeyEvent * ke = static_cast<QKeyEvent *>(evnt);
    if (ke)
    {
          qDebug()<<"Key %d pressed, event type %d"<<ke->key() <<evnt->type();
    }
    */

    if (me)
    {
        /*
        work_field->tmpX = me->pos().x()-work_field->shiftTranslateX;
        work_field->tmpY = me->pos().y()-work_field->shiftTranslateY;
        */
        // qDebug()<<" tmpX = "<< me->pos().x()-work_field->shiftTranslateX<<" tmpY = "<<me->pos().y()-work_field->shiftTranslateY;

    }
    if (evnt->type() == QEvent::MouseMove)
    {
        if (ui->action_add_comp->isChecked())
        {
            // qDebug()<< "move Comp()";

        }
    }

    if ((evnt->type() == QEvent::MouseButtonPress)&&(me->button()==Qt::LeftButton)/*&&(ke->key()==Qt::Key_Shift)*/)
    {
        /*
       qDebug()<<"*****Key_Shift*****************!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
       if (evnt->type() ==QEvent::KeyPress)
       {


       }
       */
    }


    if ((evnt->type() == QEvent::MouseMove)&&(QApplication::mouseButtons()==Qt::LeftButton))
    {
       // qDebug()<<"tmpX = "<<this->tmpX ;
        //qDebug()<<"Move + LeftButton()";
        // setCursor(Qt::IBeamCursor);

    }
    if ((evnt->type() == QEvent::MouseButtonPress)&&(QApplication::mouseButtons()==Qt::LeftButton))
    {
        //
    }

    if ((evnt ->type() == QEvent::Show) || (evnt->type() == QEvent::Resize) || (evnt->type() == QEvent::MouseButtonRelease))
        work_field->resize(ui->gbShema->width(), ui->gbShema->height());
    return QWidget::eventFilter(obj, evnt);
}

void MainForm::keyReleaseEvent(QKeyEvent *event)
{/*
    qDebug()<<"QKeyEvent";
    if (event->key()!=key1)
    {
        return;
    }
    key1 = 0;
*/
    qDebug()<<"QKeyEvent1";
    switch(event->key())
    {
        case Qt::Key_Shift:
        //setShift()

        if (!shift)
        {
             shift = true;
             QObject::disconnect(work_field,SIGNAL(setDefault()),this,SLOT(setDefault()));
        }
        else
        {
             shift = false;
              QObject::connect(work_field,SIGNAL(setDefault()),this,SLOT(setDefault()));
        }
        qDebug()<<"setShift";

        break;
        default:
        break;

    }
}


void MainForm::on_action_route1_hovered()
{
    qDebug()<<"MainForm::on_action_route1_hovered()";
}
