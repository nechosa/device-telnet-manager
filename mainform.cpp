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

#include <QtGui>
#include <QtCore>
#include <QtXml>
#include <QDebug>
#include <QKeyEvent>
#include "device.cpp"
#include "constant.h"
#include "msgbox.h"
//#include <QTest>


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

    //слоты объектов toolbar 0
    QObject::connect(ui->action_add_comp,SIGNAL(triggered(bool)),this,SLOT(addComputer(bool)));
    QObject::connect(ui->action_add_router,SIGNAL(triggered(bool)),this,SLOT(addRouter(bool)));
    QObject::connect(ui->action_add_linc,SIGNAL(triggered(bool)),this,SLOT(addLinc(bool)));

    //слоты объектов toolbar 1
    //слоты объектов toolbar 2
    //...

    //слоты объектов toolbar 3
    QObject::connect(ui->action_route1,SIGNAL(triggered(bool)),this,SLOT(selectRouter1(bool)));
    QObject::connect(ui->action_route2,SIGNAL(triggered(bool)),this,SLOT(selectRouter2(bool)));
    QObject::connect(ui->action_route3,SIGNAL(triggered(bool)),this,SLOT(selectRouter3(bool)));

    //создание рабочего поля мнемосхемы
    work_field = new Field(ui->gbShema);
    work_field->setFormat(QGLFormat(QGL::SampleBuffers));
    QObject::connect(work_field,SIGNAL(setDefault()),this,SLOT(setDefault()));
    ui->gbShema->installEventFilter(this);
    work_field->setcheckDevice(DEFAULT);

    //Конфиг
    //загружаеи последнюю мнемосхему
    //loadFromFile("temp.xml");
}

MainForm::~MainForm()
{
    //saveToFile("temp.xml");
    delete ui;
}

void MainForm::setDirData(const QString &dir)
{
    dirData = dir;
}

QString MainForm::getDirData() const
{
    return dirData;
}

void MainForm::setDirProtocol(const QString &dir)
{
    dirProtocol = dir;
}

QString MainForm::getDirProtocol() const
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
}

void MainForm::slotNew()
{
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


void MainForm::loadFromFile(QString fname)
{
    /* Загрузить из файла */
    QFile * f = new QFile (fname);
    if(f->open(QIODevice::ReadOnly))
    {
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
                    work_field->setColor(tag.attribute(QString("R1")).toInt(),tag.attribute(QString("G1")).toInt(),tag.attribute(QString("B1")).toInt(),
                                         tag.attribute(QString("R2")).toInt(),tag.attribute(QString("G2")).toInt(),tag.attribute(QString("B2")).toInt());
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
                    setDirData(tag.attribute(QString("DATA")));
                    setDirProtocol(tag.attribute(QString("PROTOKOL")));
                    //dirData=tag.attribute(QString("DATA"));
                    //dirProtokol=tag.attribute(QString("PROTOKOL"));
                    isProtokol=tag.attribute(QString("IS_PROT")).toInt();
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
                            /*
                            //ЯНГДЮЕЛ СГЕК
                            Device * node=new Device(field,tagC.attribute(QString("NAME")),
                                                       tagC.attribute(QString("TYPE")).toInt(),tagC.attribute(QString("HOSTNAME")),
                                                       tagC.attribute(QString("X")).toInt(),tagC.attribute(QString("Y")).toInt());

                            //Device(Field *work_field,int tmpX, int tmpY,QString image, QString myName);
                            //ДНАЮБКЪЕЛ СГЕК МЮ ПЮАНВЕЕ ОНКЕ
                            work_field->appendItem(node);
                            StNode *nod = new Struct_Node(tagC.attribute(QString("NAME")),tagC.attribute(QString("HOSTNAME")),
                                                          QString::fromLocal8Bit(uzNotActiv), tagC.attribute(QString("TYPE")).toInt());
                            lstTblNode<<nod;

                            //ЕЯКХ РЮАКХЖЮ СГКНБ НРЙПШРЮ, РН ГЮОНКМЪЕЛ ЕЕ
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
                            /*
                            //МЮВЮКН Х ЙНМЕЖ ЯБЪГХ
                            Device * blockBegin = work_field->getItem(tagC.attribute(QString("BEGIN")).toInt());
                            Device * blockEnd = work_field->getItem(tagC.attribute(QString("END")).toInt());

                            //ЯНГДЮЕЛ ЙЮМЮК ЯБЪГХ
                            Link * ch = new Link(blockBegin, blockEnd,tagC.attribute(QString("NAME")),
                                                        tagC.attribute(QString("TYPE")).toInt(),tagC.attribute(QString("WIDTH")).toInt());
                            //ДНАЮБКЪЕЛ ЕЦН МЮ ПЮАНВЕЕ ОНКЕ
                            field->appendLink(ch);
                            //ЯНГДЮЕЛ ЯРПСЙРСПС ДКЪ НРНАПЮФЕМХЪ ЙЮМЮКЮ Б РЮАКХЖЕ
                            StChan *cha = new Struct_Channel(tagC.attribute(QString("NAME")),blockBegin->getName(),blockEnd->getName(),
                                                             QString::fromLocal8Bit(uzNotActiv),tagC.attribute(QString("TYPE")).toInt());
                            lstTblChan<<cha;
                            //ЕЯКХ РЮАКХЖЮ ЙЮМЮКНБ НРЙПШРЮ, РН ГЮОНКМЪЕЛ ЕЕ
                            if(chan)
                            {
                                chanel->CreateTblChannel(lstTblChan);
                            }
                            */
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
        tag = doc.createElement(QString("TIMEOUT"));
        tag.setAttribute(QString("OPROS"),oprosPeriod);
        tag.setAttribute(QString("OTVET"),otvetPeriod);
        tagRoot.appendChild(tag);

        //йЮРЮКНЦХ ОН СЛНКВЮМХЧ
        tag = doc.createElement(QString("DIR"));
        tag.setAttribute(QString("DATA"),dirData);
        tag.setAttribute(QString("PROTOKOL"),dirProtocol);
        tag.setAttribute(QString("IS_PROT"),isProtokol);
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
            //tagC.setAttribute(QString("TYPE"),theBlock->getType());
            //tagC.setAttribute(QString("HOSTNAME"),theBlock->getAddress());
            tag.appendChild(tagC);
        }
        tagRoot.appendChild(tag);
/*
        //йЮМЮКШ ЯБЪГХ
        QList <Link *> channels = work_field->getLstChannel();
        tag = doc.createElement(QString("LINKS"));
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
            tag.appendChild(tagC);
        }
        tagRoot.appendChild(tag);
*/
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
    /* Слот добавление Связи   */
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
    /* Слот выбора 1 маршрута  */
    ui->action_route2->setChecked(false);
    ui->action_route2->setEnabled(false);
    ui->action_route3->setChecked(false);
    ui->action_route3->setEnabled(false);

    //sleep(1);
    ui->action_route2->setEnabled(true);
    ui->action_route3->setEnabled(true);


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



}
void MainForm::selectRouter3(bool flag)
{
    /* Слот выбора 3 маршрута  */
    ui->action_route1->setChecked(false);
    ui->action_route1->setEnabled(false);
    ui->action_route2->setChecked(false);
    ui->action_route2->setEnabled(false);

    //sleep(1);
    ui->action_route1->setEnabled(true);
    ui->action_route2->setEnabled(true);



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
    qDebug()<<"MainForm::on_action_route1_hovered()";
//    work_field->set
    work_field->setActive(true);
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
    work_field->setActive(false);
}
