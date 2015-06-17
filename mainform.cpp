/******************************************************************
  * Имя файла : mainform.cpp
  * Назначение модуля: Реализация главной формы программы
  * Функции:
  * Автор: Нечёса И.А.
  * Дата создания :           2015-03-16
  * Дата последней редакции : 2012-03-16
  *****************************************************************/
#include "mainform.h"
#include "ui_mainform.h"
#include "spravka.h"

#include <QtGui>
#include <QtCore>
#include <QtXml>
#include <QDebug>
#include <QKeyEvent>
#include "device.cpp"
#include "constant.h"
#include "const.h"
#include "msgbox.h"

//#include <QTest>
#include <QCursor>


MainForm::MainForm(QWidget *parent)
        : QMainWindow(parent),
        ui(new Ui::MainForm),
        name(""),
        dirProtocol(""),
        dirData(""),
        imageName(""),
        shift(false),key1(0)
{
    ui->setupUi(this);
    this->setWindowTitle(QString::fromLocal8Bit(NAME_PROGRAM));
    //форма по центру экрана
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    //сопоставление сигналов и слотов
    //слоты главного меню
    QObject::connect(ui->action_new,SIGNAL(triggered()),this,SLOT(slotNew()));
    QObject::connect(ui->action_open,SIGNAL(triggered()),this,SLOT(slotOpen()));
    QObject::connect(ui->action_save,SIGNAL(triggered()),this,SLOT(slotSave()));
    QObject::connect(ui->action_save_as,SIGNAL(triggered()),this,SLOT(slotSave_as()));
    //
    QObject::connect(ui->actionShowInfo,SIGNAL(triggered(bool)),this,SLOT(slotShowInfo(bool)));

    //слоты объектов toolbar 0
    QObject::connect(ui->action_add_comp,SIGNAL(triggered(bool)),this,SLOT(addComputer(bool)));
    QObject::connect(ui->action_add_router,SIGNAL(triggered(bool)),this,SLOT(addRouter(bool)));
    QObject::connect(ui->action_add_radio,SIGNAL(triggered(bool)),this,SLOT(addRadio(bool)));
    QObject::connect(ui->action_add_linc,SIGNAL(triggered(bool)),this,SLOT(addLinc(bool)));

    QObject::connect(ui->actionRouteInform,SIGNAL(triggered()),this,SLOT(informRouter()));

    QObject::connect(ui->action_about,SIGNAL(triggered()),this,SLOT(slotAbout()));


    //слоты объектов toolbar 1
    //слоты объектов toolbar 2
    //...

              QMenu * menu = new QMenu(this);
              /*
              QAction *action[3];
              for (int i = 1;i<=3;++i)
              {
                  qDebug()<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>QAction+++";
                  action[i]= new QAction(QString::fromLocal8Bit("Сохранить как маршрут ")+QString::number(i), this);
                  action[i]->setIcon(QIcon(":/img/img/inverse_kinematics_256_"+QString::number(i)+".png"));
                  menu->addAction(action[i]);
                  emit action_Route(i);
                  QObject::connect(action[i],SIGNAL(triggered()),this,SLOT(informRouter(i)));

              }

               QObject::connect(this,SIGNAL(action_Route(int)),this,SLOT(informRouter(int)));
               */

              QAction *action1 = new QAction(QString::fromLocal8Bit("Сохранить как маршрут 1"), this);
               action1->setIcon(QIcon(":/img/img/inverse_kinematics_256_1.png"));
                    menu->addAction(action1);
                    //QObject::connect(action1,SIGNAL(triggered()),this,SLOT(createTerminal()));
                    //menu->addSeparator();
                    QAction *action2 = new QAction(QString::fromLocal8Bit("Сохранить как маршрут 2"), this);
                    action2->setIcon(QIcon(":/img/img/inverse_kinematics_256_2.png"));
                    menu->addAction(action2);
                     QAction *action3 = new QAction(QString::fromLocal8Bit("Сохранить как маршрут 3"), this);
                    action3->setIcon(QIcon(":/img/img/inverse_kinematics_256_3.png"));
                    menu->addAction(action3);
                    //:/img/img/inverse_kinematics_256_1.png
                   // menu->exec();


    QObject::connect(action1,SIGNAL(triggered()),this,SLOT(saveRoute1()));
    QObject::connect(action2,SIGNAL(triggered()),this,SLOT(saveRoute2()));
    QObject::connect(action3,SIGNAL(triggered()),this,SLOT(saveRoute3()));
      ui->actionRouteInform->setMenu(menu);

       // QObject::connect(action3,SIGNAL(triggered()),this,SLOT(saveRoute3()));
     // work_field->addRoute();
    //ui->actionRouteInform->set;

    // QObject::connect(ui->actionRouteInform,SIGNAL(triggered()),menu,SLOT()));

    //слоты объектов toolbar 3
    QObject::connect(ui->action_route1,SIGNAL(triggered(bool)),this,SLOT(selectRouter1(bool)));
    QObject::connect(ui->action_route2,SIGNAL(triggered(bool)),this,SLOT(selectRouter2(bool)));
    QObject::connect(ui->action_route3,SIGNAL(triggered(bool)),this,SLOT(selectRouter3(bool)));

    /*
    QObject::connect(ui->action_route1,SIGNAL(hovered()),this,SLOT(selectRouter1()));
    QObject::connect(ui->action_route2,SIGNAL(hovered()),this,SLOT(selectRouter2()));
    QObject::connect(ui->action_route3,SIGNAL(hovered()),this,SLOT(selectRouter3()));
    */

    //создание рабочего поля мнемосхемы
    work_field = new Field(ui->gbShema);
    work_field->setFormat(QGLFormat(QGL::SampleBuffers));
    QObject::connect(work_field,SIGNAL(setDefault()),this,SLOT(setDefault()));
    ui->gbShema->installEventFilter(this);
    work_field->setcheckDevice(DEFAULT);

    //Конфиг
    //загружаеи последнюю мнемосхему
   loadFromFile("temp.xml");
}

MainForm::~MainForm()
{
    qDebug()<<"save File";
    saveToFile("temp.xml");
    qDebug()<<"save File end";
    delete ui;
}

void MainForm::setDirData(const QString &dir)
{
    dirData = dir;
}

const QString MainForm::getDirData() const
{
    return dirData;
}

void MainForm::setDirProtocol(const QString &dir)
{
    dirProtocol = dir;
}

const QString MainForm::getDirProtocol() const
{
    return dirProtocol;
}

void MainForm::setDefault()
{
    /* Установка значений по-умолчанию */
    work_field->setcheckDevice(DEFAULT);
    ui->action_add_router->setChecked(false);
    ui->action_add_linc->setChecked(false);
    ui->action_add_comp->setChecked(false);
    ui->action_add_radio->setChecked(false);
}

void MainForm::slotNew()
{
    qDebug()<<" Create new schema";
    /* Создание новой мнемосхемы */

}

void MainForm::slotAbout()
{
    spravka *dlg = new spravka(this);
    dlg->exec();
    qDebug()<<" Create new schema";
    /* Создание новой мнемосхемы */

}

void MainForm::slotOpen()
{
    qDebug()<<" Open schema";
    /* Открыть мнемосхему */
    QString filename = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("Открыть"),dirData,QString::fromLocal8Bit(msgFormat));

    if(!filename.isEmpty())
    {
        ClearField();
        loadFromFile(filename);
    }
}
void MainForm::slotSave()
{
    /* Сохранить текущую мнемосхему */
    qDebug()<<" Save schema";

}

void MainForm::ClearField()
{
    /* Очистистить рабочее поле от объектов и связей */
    //НВХЫЮЕЛ ПЮАНВЕЕ ОНКЕ
    work_field->clearItems();
    //work_field->setColor(212,208,200,222,218,210);
    //slotSetAnimation(false);
    //ui->action_animation->setChecked(false);
    //НВХЫЮЕЛ РЮАКХЖШ
    /*
    lstTblNode.clear();
    lstTblChan.clear();
    if(uz)
        uzel->CreateTblNode(lstTblNode);
    if(chan)
        chanel->CreateTblChannel(lstTblChan);
    */
}

void MainForm::slotSave_as()
{
    /* Сохранить текущую мнемосхему как ... с вызовом диалогового окна*/
        QString filename = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("Сохранить мнемосхему"),dirData,QString::fromLocal8Bit(msgFormat));

    if(!filename.isEmpty())
    {
        if(filename.right(4)!=".xml")
        {
            filename=filename+".xml";
            saveToFile(filename);
        }
        else
            saveToFile(filename);
    }
    qDebug()<<" Save_as schema";

}

void MainForm::slotSave_image()
{
    /* Сохранить изображение мнемосхемы */
    qDebug()<<" Save image";
}

void MainForm::slotExit()
{
    qDebug()<<" Exit";
    /* Выход */
}

void MainForm::slotShowInfo(bool show)
{
    /* Отобразить информацию */
    qDebug()<<" show1"<<show;
     work_field->setInfo(show);
}

void MainForm::loadFromFile(QString fname)
{
    /* Загрузить из файла */

    QFile * f = new QFile (fname);
    if(f->open(QIODevice::ReadOnly))
    {
        qDebug()<<"Open File";
        QByteArray content = f->readAll();
        QString theContent = QString::fromLocal8Bit(content.data());
        f->close();

        QDomDocument doc;
        doc.setContent(theContent);

        QString codec;
        QDomNode nod = doc.firstChild();
        if(nod.isProcessingInstruction())
        {
            QDomProcessingInstruction pi = nod.toProcessingInstruction();
            if (pi.data().toUpper().contains("KOI8-R"))
                codec="koi8-r";
            else
                codec="windows-1251";

            theContent.clear();
            f->open(QIODevice::ReadOnly);
            QTextStream in(f);
            in.setCodec(QTextCodec::codecForName(codec.toLocal8Bit()));
            while(!in.atEnd())
                theContent=theContent+in.readLine();
            f->close();
            doc.setContent(theContent);
        }
        delete f;

        QDomElement tagRoot = doc.documentElement();
        if ((doc.doctype().name().toUpper()==QString("MNEMONET"))&&(tagRoot.tagName().toUpper()==QString("MNEMONET")))
        {
            QDomNode node = tagRoot.firstChild();
            while (!node.isNull())
            {
                QDomElement tag = node.toElement();

                //МЮХЛЕМНБЮМХЕ ЛМЕЛНЯУЕЛШ
                if (tag.tagName().toUpper()==QString("MNEMO_NAME"))
                    name=tag.attribute(QString("NAME"));
                //ТНМ
                if (tag.tagName().toUpper()==QString("BACKGROUND"))
                {
                    work_field->setColor(tag.attribute(QString("R1")).toInt(),tag.attribute(QString("G1")).toInt(),
                                         tag.attribute(QString("B1")).toInt(),
                                         tag.attribute(QString("R2")).toInt(),
                                         tag.attribute(QString("G2")).toInt(),
                                         tag.attribute(QString("B2")).toInt());
                    imageName=tag.attribute(QString("IMG"));
                    if( !(imageName.isEmpty() || imageName.isNull()) )
                    {
                        QImage image;
                        image.load(imageName, 0);
                        work_field->setWallpaper(image);
                        work_field->updateGL();
                    }
                    //setUpdatePeriod(tag.attribute(QString("ANIMATION")).toInt());
                    if(tag.attribute(QString("IS_ANIMATION")).toInt()==1)
                    {
                        //slotSetAnimation(true);
                        //ui->action_animation->setChecked(true);
                    }
                    else
                    {
                        //slotSetAnimation(false);
                        //ui->action_animation->setChecked(false);
                    }
                }
                //оЕПХНДШ
                if (tag.tagName().toUpper()==QString("TIMEOUT"))
                {
                    //oprosPeriod=tag.attribute(QString("OPROS")).toInt();
                    //otvetPeriod=tag.attribute(QString("OTVET")).toInt();
                }
                //йЮРЮКНЦХ ОН СЛНКВЮМХЧ
                if (tag.tagName().toUpper()==QString("DIR"))
                {
                    //setDirData(tag.attribute(QString("DATA")));
                    //setDirProtocol(tag.attribute(QString("PROTOKOL")));
                    //dirData=tag.attribute(QString("DATA"));
                    //dirProtokol=tag.attribute(QString("PROTOKOL"));
                    //isProtokol=tag.attribute(QString("IS_PROT")).toInt();
                }
                //сГКШ ЯБЪГХ
                if (tag.tagName().toUpper() == QString("HOSTS"))
                {
                    QDomNode nodeC = tag.firstChild();
                    while (!nodeC.isNull())
                    {
                        QDomElement tagC = nodeC.toElement();
                        if (tagC.tagName().toUpper() == QString("HOST"))
                        {

                            //ЯНГДЮЕЛ СГЕК
                            /*
                            Device * node=new Device(field,tagC.attribute(QString("NAME")),
                                                       tagC.attribute(QString("TYPE")).toInt(),tagC.attribute(QString("HOSTNAME")),
                                                       tagC.attribute(QString("X")).toInt(),tagC.attribute(QString("Y")).toInt());
                            */
                            //DeviceType type = ROUTER;
                            //int m = tagC.attribute(QString("TYPE")).toInt();
                            //DeviceType type1 = tagC.attribute(QString("TYPE")).toInt();
                            //qDebug()<<"TYPE = "<<tagC.attribute(QString("TYPE"));
                            //qDebug()<<"ROUTER = "<<ROUTER;
                            //qDebug()<<"TYPE1 = "<<type1;
                            /*
                            Device * node=new Device(work_field,tagC.attribute(QString("X")).toInt(),
                            tagC.attribute(QString("Y")).toInt(), (DeviceType)tagC.attribute(QString("TYPE")).toInt());
                            */

                            Device * node=new Device(work_field,tagC.attribute(QString("X")).toInt(),
                            tagC.attribute(QString("Y")).toInt(), (DeviceType)tagC.attribute(QString("TYPE")).toInt(),
                            tagC.attribute(QString("NAME")),tagC.attribute(QString("IP")));
                            qDebug()<<"TYPE"<<tagC.attribute(QString("TYPE"));
                            //Device(Field *work_field,int tmpX, int tmpY,QString image, QString myName);
                            //ДНАЮБКЪЕЛ СГЕК МЮ ПЮАНВЕЕ ОНКЕ
                            work_field->appendItem(node);
                            /*
                            StNode *nod = new Struct_Node(tagC.attribute(QString("NAME")),tagC.attribute(QString("HOSTNAME")),
                                                          QString::fromLocal8Bit(uzNotActiv), tagC.attribute(QString("TYPE")).toInt());
                            */
                            //lstTblNode<<nod;

                            //ЕЯКХ РЮАКХЖЮ СГКНБ НРЙПШРЮ, РН ГЮОНКМЪЕЛ ЕЕ
                            /*
                            if(uz)
                            {
                                uzel->CreateTblNode(lstTblNode);
                            }
                            */

                        }
                        nodeC = nodeC.nextSibling();
                    }

                }

                //ЙЮМЮКШ ЯБЪГХ

                if (tag.tagName().toUpper() == QString("LINKS"))
                {
                    QDomNode nodeC = tag.firstChild();
                    while (!nodeC.isNull())
                    {
                        QDomElement tagC = nodeC.toElement();
                        if (tagC.tagName().toUpper() == QString("LINK"))
                        {
                             /*QDomNode nodeLink = tag.firstChild();
                              while (!nodeLink.isNull())
                              {
                                QDomElement tagLinkItem = nodeLink.toElement();
                                if (tagC.tagName().toUpper() == QString("PARAM"))
                                {

                                }
                                if (tagC.tagName().toUpper() == QString("ETH0"))
                                {

                                }
                                if (tagC.tagName().toUpper() == QString("ETH1"))
                                {

                                }
                              }
                             */

                            Device * blockBegin = work_field->getItem(tagC.attribute(QString("BEGIN")).toInt());
                            Device * blockEnd = work_field->getItem(tagC.attribute(QString("END")).toInt());

                            Link * ch = new Link(work_field,blockBegin, blockEnd,tagC.attribute(QString("NAME")),
                                                        tagC.attribute(QString("TYPE")).toInt(),tagC.attribute(QString("WIDTH")).toInt(),
                                                        tagC.attribute(QString("ETH0")),tagC.attribute(QString("ETH1")),
                                                        tagC.attribute(QString("ETH0X")).toInt(),tagC.attribute(QString("ETH0Y")).toInt(),
                                                        tagC.attribute(QString("ETH1X")).toInt(),tagC.attribute(QString("ETH1Y")).toInt()
                                                        );
       /*
     Link::Link(Field *work_field,Device * first, Device * last, QString theName,int theType,int theWidth,QString l_eth0,QString l_eth1,
         int x_eth0,int y_eth0,
         int x_eth1,int y_eth1
           ) :parent(work_field),
     */
              /*
                                        tagC.setAttribute(QString("ETH0"),theChannel->txt1->getText());
            tagC.setAttribute(QString("ETH0X"),theChannel->txt1->x());
            tagC.setAttribute(QString("ETH0Y"),theChannel->txt1->y());
            tagC.setAttribute(QString("ETH1"),theChannel->txt2->getText());
            tagC.setAttribute(QString("ETH1X"),theChannel->txt2->x());
            tagC.setAttribute(QString("ETH1Y"),theChannel->txt2->y());
            */
                            work_field->appendLink(ch);
                        }
                        nodeC = nodeC.nextSibling();
                    }

                }

                node=node.nextSibling();
            }
        }
        else
        {
            //МЕЙЙНПЕЙРМШИ ТНПЛЮР ТЮИКЮ
            QMessageDlg(mtWarning, this, this->windowTitle().append(0x20),
                        QString::fromLocal8Bit(msgNotFormat),
                        QString::fromLocal8Bit(msgCancel));
        }

    }
    else
    {
        //МЕБНГЛНФМН НРЙПШРЭ ТЮИК
        QMessageDlg(mtWarning, this, this->windowTitle().append(0x20),
                    QString::fromLocal8Bit(msgFileNotOpen),
                    QString::fromLocal8Bit(msgCancel));
    }
}
//---------------------------------------

//ЯНУПЮМЕМХЕ Б ТЮИК
void MainForm::saveToFile(QString fname)
{
    QFile * f = new QFile (fname);
    if(f->open(QIODevice::WriteOnly))
    {
        QDomDocument doc ("MnemoNet");

#ifdef Q_OS_WIN32
        QDomProcessingInstruction pi = doc.createProcessingInstruction(
                QString("xml"), QString("version='1.0' encoding='windows-1251'"));
#else
        QDomProcessingInstruction pi = doc.createProcessingInstruction(
                QString("xml"), QString("version='1.0' encoding='koi8-r'"));
#endif
        doc.appendChild(pi);

        QDomElement tagRoot = doc.createElement("MNEMONET");
        QDomElement tag;

        //ХЛЪ ЛМЕЛНЯУЕЛШ
        tag = doc.createElement(QString("MNEMO_NAME"));
        tag.setAttribute(QString("NAME"),name);
        tagRoot.appendChild(tag);

        //ТНМ
        int r1(0),g1(0),b1(0),r2(0),g2(0),b2(0);
        work_field->getColor(r1,g1,b1,r2,g2,b2);

        tag = doc.createElement(QString("BACKGROUND"));
        tag.setAttribute(QString("R1"),r1);
        tag.setAttribute(QString("G1"),g1);
        tag.setAttribute(QString("B1"),b1);
        tag.setAttribute(QString("R2"),r2);
        tag.setAttribute(QString("G2"),g2);
        tag.setAttribute(QString("B2"),b2);
        tag.setAttribute(QString("B2"),b2);
        tag.setAttribute(QString("IMG"),imageName);
        //tag.setAttribute(QString("ANIMATION"),updatePeriod);
        //tag.setAttribute(QString("IS_ANIMATION"),isAnimation);
        tagRoot.appendChild(tag);

        //оЕПХНДШ
        //tag = doc.createElement(QString("TIMEOUT"));
        //tag.setAttribute(QString("OPROS"),oprosPeriod);
        //tag.setAttribute(QString("OTVET"),otvetPeriod);
        tagRoot.appendChild(tag);

        //йЮРЮКНЦХ ОН СЛНКВЮМХЧ
        //tag = doc.createElement(QString("DIR"));
        //tag.setAttribute(QString("DATA"),dirData);
        //tag.setAttribute(QString("PROTOKOL"),dirProtocol);
        //tag.setAttribute(QString("IS_PROT"),isProtokol);
        tagRoot.appendChild(tag);

        //сГКШ ЯБЪГХ

        QList <Device *> nodes = work_field->getLstNode();
        tag = doc.createElement(QString("HOSTS"));
        for (int i=0;i<nodes.size();i++)
        {
            Device * theBlock = nodes[i];
            QDomElement tagC = doc.createElement(QString("HOST"));
            tagC.setAttribute(QString("X"),theBlock->x());
            tagC.setAttribute(QString("Y"),theBlock->y());
            tagC.setAttribute(QString("NAME"),theBlock->getName());
            tagC.setAttribute(QString("TYPE"),theBlock->getDeviceType());
            //tagC.setAttribute(QString("TYPE"),theBlock->getType());
            tagC.setAttribute(QString("IP"),theBlock->getIpaddr());
            tag.appendChild(tagC);
        }
        tagRoot.appendChild(tag);

        //йЮМЮКШ ЯБЪГХ
        qDebug()<<"Link";
        QList <Link *> channels = work_field->getLstChannel();
        tag = doc.createElement(QString("LINKS"));
        qDebug()<<"Link size" << channels.size();
        for (int i=0;i<channels.size();i++)
        {
            Link * theChannel = channels[i];
            QDomElement tagC = doc.createElement(QString("LINK"));
            tagC.setAttribute(QString("NAME"),theChannel->getName());
            tagC.setAttribute(QString("TYPE"),theChannel->getType());
            int beg=0;int end=0;
            for (int j=0;j<nodes.size();j++)
            {
                if(nodes[j]==theChannel->begining)
                    beg=j;
                if(nodes[j]==theChannel->ending)
                    end=j;
            }
            tagC.setAttribute(QString("BEGIN"),beg);
            tagC.setAttribute(QString("END"),end);
            tagC.setAttribute(QString("WIDTH"),theChannel->getWidth());
            tagC.setAttribute(QString("ETH0"),theChannel->txt1->getText());
            tagC.setAttribute(QString("ETH0X"),theChannel->txt1->x());
            tagC.setAttribute(QString("ETH0Y"),theChannel->txt1->y());
            tagC.setAttribute(QString("ETH1"),theChannel->txt2->getText());
            tagC.setAttribute(QString("ETH1X"),theChannel->txt2->x());
            tagC.setAttribute(QString("ETH1Y"),theChannel->txt2->y());
            tag.appendChild(tagC);
        }
        tagRoot.appendChild(tag);

        doc.appendChild(tagRoot);
        QString theContent = doc.toString();
        f->write(theContent.toLocal8Bit().data(),theContent.length());
        f->flush();
        f->close();
    }
    delete f;

}
//---------------------------------------

void MainForm::addComputer(bool flag)
{
    /* Слот добавление Маршрутизатора   */
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
    /* Слот добавление Маршрутизатора   */
    if (flag)
    {
        //qDebug()<<"addRouter()";
        setCursor(Qt::ArrowCursor);
        ui->action_add_comp->setChecked(false);
        ui->action_add_linc->setChecked(false);
        ui->action_add_radio->setChecked(false);
        //work_field->setcheckDevice(ROUTER);
        work_field->setcheckDevice(ROUTER);
        // work_field->setcheckDevice(Router);
    }
    else
    {
        this->setDefault();

    }
}


void MainForm::addRadio(bool flag)
{
    /* Слот добавление Маршрутизатора   */
    if (flag)
    {
        //qDebug()<<"addRouter()";
        setCursor(Qt::ArrowCursor);
        ui->action_add_comp->setChecked(false);
        ui->action_add_linc->setChecked(false);
        ui->action_add_router->setChecked(false);
        //work_field->setcheckDevice(ROUTER);
        work_field->setcheckDevice(RADIO);
        // work_field->setcheckDevice(Router);
    }
    else
    {
        this->setDefault();

    }
}
void MainForm::addLinc(bool flag)
{
    /* Слот добавление Связи   */
    // qDebug()<<"addLinc()";
    if (flag)
    {
        setCursor(Qt::CrossCursor);
        work_field->setcheckDevice(LINK);
        ui->action_add_router->setChecked(false);
        ui->action_add_comp->setChecked(false);
        ui->action_add_radio->setChecked(false);
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
    /* Слот выбора 1 маршрута  */
    ui->action_route2->setChecked(false);
    ui->action_route2->setEnabled(false);
    ui->action_route3->setChecked(false);
    ui->action_route3->setEnabled(false);

    //sleep(1);
    ui->action_route2->setEnabled(true);
    ui->action_route3->setEnabled(true);

work_field->showRoute(1,flag);
    //ui->action_
    //ui->action_route

}
void MainForm::selectRouter2(bool flag)
{
    /* Слот выбора 2 маршрута  */
    ui->action_route1->setChecked(false);
    ui->action_route1->setEnabled(false);
    ui->action_route3->setChecked(false);
    ui->action_route3->setEnabled(false);

    //sleep(1);
    ui->action_route1->setEnabled(true);
    ui->action_route3->setEnabled(true);

    work_field->showRoute(2,flag);



}
void MainForm::selectRouter3(bool flag)
{
     qDebug()<<"saveRoute3";
    /* Слот выбора 3 маршрута  */
    ui->action_route1->setChecked(false);
    ui->action_route1->setEnabled(false);
    ui->action_route2->setChecked(false);
    ui->action_route2->setEnabled(false);

    //sleep(1);
    ui->action_route1->setEnabled(true);
    ui->action_route2->setEnabled(true);
    work_field->showRoute(3,flag);



}
/********************************************************************/


void MainForm::selectRouter1()
{
    /* Слот выбора 1 маршрута  */
    ui->action_route2->setChecked(false);
    ui->action_route2->setEnabled(false);
    ui->action_route3->setChecked(false);
    ui->action_route3->setEnabled(false);

    //sleep(1);
    ui->action_route2->setEnabled(true);
    ui->action_route3->setEnabled(true);

work_field->showRoute(1,true);
    //ui->action_
    //ui->action_route

}
void MainForm::selectRouter2()
{
    /* Слот выбора 2 маршрута  */
    ui->action_route1->setChecked(false);
    ui->action_route1->setEnabled(false);
    ui->action_route3->setChecked(false);
    ui->action_route3->setEnabled(false);

    //sleep(1);
    ui->action_route1->setEnabled(true);
    ui->action_route3->setEnabled(true);

    work_field->showRoute(2,true);



}
void MainForm::selectRouter3()
{
     qDebug()<<"saveRoute3";
    /* Слот выбора 3 маршрута  */
    ui->action_route1->setChecked(false);
    ui->action_route1->setEnabled(false);
    ui->action_route2->setChecked(false);
    ui->action_route2->setEnabled(false);

    //sleep(1);
    ui->action_route1->setEnabled(true);
    ui->action_route2->setEnabled(true);
    work_field->showRoute(3,true);



}



void MainForm::saveRoute1()
{
    qDebug()<<"saveRoute1";
    //emit saveRoute(1);
     work_field->addRoute(1);
}

void MainForm::saveRoute2()
{
    qDebug()<<"saveRoute2";
    //emit saveRoute(2);
     work_field->addRoute(2);
}

void MainForm::saveRoute3()
{
    qDebug()<<"saveRoute3";
     work_field->addRoute(3);
    //emit saveRoute(3);
}
void MainForm::informRouter()
{
    qDebug()<<"informRouter";
    QPoint globalPos;

    QWidget * entrywidget = ui->toolBar_2->widgetForAction(ui->actionRouteInform);
    qDebug()<<"geometry()"<<entrywidget->geometry();
     qDebug()<<"geometry()"<<this->geometry().x();
     qDebug()<<"x()"<<entrywidget->x();
     qDebug()<<"y()"<<entrywidget->y();
     qDebug()<<"height()"<<entrywidget->height();
     qDebug()<<"width()"<<entrywidget->width();
     //entrywidget->mapToGlobal(&globalPos);
      qDebug()<<"globalPos = "<<entrywidget->pos();
     //entrywidget->ge
    //entrywidget->setEnabled(false);
    
   ui->actionRouteInform->menu()->exec(QPoint(this->geometry().x()+entrywidget->geometry().x()+ui->toolBar_2->x(),
                                              this->geometry().y()+entrywidget->geometry().y()+ui->toolBar_2->y()+entrywidget->height()));
    //ui->actionRouteInform->menu()->exec(QPoint(this->x()/*+ui->toolBar_2->width()*/,
   //this->y()+ ui->toolBar_2->height())/*ui->toolBar_2->x()/*ui->actionRouteInform->p*/);

   //work_field->addRoute();
   //work_field->addRoute();

        /*
    QMenu * menu = new QMenu("My menu");
    ui->toolBar_2->addAction(menu->menuAction());
    menu->menuAction()->setIcon(QIcon(":/img/img/workstation_256.png"));

    */
   // menu->exec();
}
bool MainForm::eventFilter(QObject * obj, QEvent * evnt)
{
    /* Фильтр событий */
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
{
    /* Задания параметра создания множества обьектов при нажатии клавиши Shift */
    /* Задание горячих клавиш */
    /*
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
    /* Выделение нужного маршрута при наведении мышки */
    //qDebug()<<"MainForm::on_action_route1_hovered()";
//    work_field->set
    //work_field->setActive(true);
}


// подтверждение закрытия окна
void MainForm::closeEvent(QCloseEvent * event)
 {
    if (QMessageDlg(mtConfirmation,this,this->windowTitle().append(0x20),
                       QString::fromLocal8Bit(msgExit),
                       QString::fromLocal8Bit(msgYes),
                       QString::fromLocal8Bit(msgNo))==0)
        event->accept();
    else
        event->ignore();
 }

void MainForm::on_action_route2_hovered()
{
    //work_field->setActive(false);
    //work_field->links;
}
/*
void MainForm::on_action_route3_triggered()
{
   // work_field->showRoute(3,true);
}

void MainForm::on_action_route1_triggered()
{
    //work_field->showRoute(1,true);
}

void MainForm::on_action_route2_triggered()
{
    // work_field->showRoute(2,true);
}
*/

void MainForm::on_actionShowInfo_triggered()
{

}

void MainForm::on_action_triggered()
{

}
