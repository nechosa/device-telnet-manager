#include "mainform.h"
#include "ui_mainform.h"

#include <QtGui>
#include <QtCore>
#include <QtXml>
#include <QDebug>
#include "device.cpp"

MainForm::MainForm(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainForm)
{
    ui->setupUi(this);


    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    QObject::connect(ui->action_add_comp,SIGNAL(triggered()),this,SLOT(addComputer()));
    QObject::connect(ui->action_add_router,SIGNAL(triggered()),this,SLOT(addRouter()));
    QObject::connect(ui->action_add_linc,SIGNAL(triggered(bool)),this,SLOT(addLinc(bool)));

    work_field = new Field(ui->gbShema);

    //QObject::connect(work_field,SIGNAL(SignalEdit()),this,SLOT(SlotEdit()));
    //QObject::connect(work_field,SIGNAL(newLinkAdded(int,int)),this,SLOT(SlotAddChannel(int,int)));
    //QObject::connect(work_field,SIGNAL(SignalDelChan(int)),this,SLOT(SlotDelChan(int)));
    ui->gbShema->installEventFilter(this);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::addComputer()
{
    //qDebug()<<"addComputer()";
    setCursor(Qt::ArrowCursor);
    ui->action_add_router->setChecked(false);
    ui->action_add_linc->setChecked(false);

}

void MainForm::addRouter()
{
    //qDebug()<<"addRouter()";
    setCursor(Qt::ArrowCursor);
    ui->action_add_comp->setChecked(false);
    ui->action_add_linc->setChecked(false);
}
void MainForm::addLinc(bool flag)
{
    // qDebug()<<"addLinc()";
    if (flag)
    {
        setCursor(Qt::CrossCursor);
        ui->action_add_router->setChecked(false);
        ui->action_add_comp->setChecked(false);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
    //action_add_linc
}

bool MainForm::eventFilter(QObject * obj, QEvent * evnt)
{
    // qDebug()<<"eventFilter()";
    //qDebug()<<"eventFilter()";
    //qDebug()<<"Фильтр событий ";
    QMouseEvent * me = dynamic_cast<QMouseEvent *>(evnt);
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

    if ((evnt->type() == QEvent::MouseButtonPress)&&(me->button()==Qt::LeftButton))
    {
         qDebug()<<"LeftButton()!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    }


    if ((evnt->type() == QEvent::MouseMove)&&(QApplication::mouseButtons()==Qt::LeftButton))
    {
        qDebug()<<"Move + LeftButton()";
        // setCursor(Qt::IBeamCursor);

    }
    if ((evnt->type() == QEvent::MouseButtonPress)&&(QApplication::mouseButtons()==Qt::LeftButton))
    {
        //qDebug()<<" tmpX = "<<  work_field->tmpX <<" tmpY = "<< work_field->tmpY;
        Device *dev;
        qDebug()<<"LeftButton()!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        if (ui->action_add_comp->isChecked())
        {
            qDebug()<< "create COMP()";
            //dev = new Device(work_field,me->pos().x(),me->pos().y(),":/img/img/workstation_256.png");
            dev = new Device(work_field,me->pos().x(),me->pos().y(),":/img/img/workstation_128.png","Компьютер");
            //dev = new Device(work_field,me->pos().x(),me->pos().y(),":/img/img/workstation_128.ico");
            //dev = new Device(work_field,me->pos().x(),me->pos().y(),":/img/img/dedicated_server_128.bmp");

            work_field->appendItem(dev);
            //dev = new Device(work_field,me->pos().x(),me->pos().y());
            //   dev = new Device(work_field,work_field->tmpX,work_field->tmpY);
        }
        if (ui->action_add_router->isChecked())
        {
            qDebug()<< "create ROUTER()";
            dev = new Device(work_field,me->pos().x(),me->pos().y(),":/img/img/router-th.png","Маршрутизатор");
            work_field->appendItem(dev);
            //dev = new Device();
            //dev = new Device(work_field,work_field->tmpX,work_field->tmpY);
        }
        if (ui->action_add_linc->isChecked())
        {
            qDebug()<< "create LINK()";

            /*
              dev = new Device(work_field,me->pos().x(),me->pos().y(),"");
              work_field->appendItem(dev);
              */
            //  dev = new Device();
            // dev = new Device(work_field,work_field->tmpX,work_field->tmpY);
        }
        // dev = new Device(work_field,me->pos().x(),me->pos().y());
        //work_field->add
    }

    if ((evnt ->type() == QEvent::Show) || (evnt->type() == QEvent::Resize) || (evnt->type() == QEvent::MouseButtonRelease))
        work_field->resize(ui->gbShema->width(), ui->gbShema->height());
    return QWidget::eventFilter(obj, evnt);
}
