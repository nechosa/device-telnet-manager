#include "presentertelnet.h"

#include <QList>
#include <QListIterator>
#include <QtCore/QObject>

PresenterTelnet::PresenterTelnet(IViewTelnet *view,QObject *parent):
        QObject(parent),t_model(new ModelTelnet),t_view(view)
{
    //view
     //QObject::connect(view,SIGNAL(processConnect()),this,SLOT(processConnect()));
     QObject *view_obj = dynamic_cast<QObject*>(t_view);
     connect(view_obj,SIGNAL(processConnect()),this,SLOT(processConnect()));
    // connect(view,SIGNAL(processConnect()),this,SLOT(processConnect()));
     connect(view_obj,SIGNAL(onCommand(QString)),this,SLOT(onCommand(QString)));
    // connect(view,SIGNAL(onCommand(QString)),this,SLOT(onCommand(QString)));

    refreshView();
}

PresenterTelnet::~PresenterTelnet()
{
    qDebug("~PresenterTelnet()");
}

//Подключение к Телнет
void PresenterTelnet::processConnect()
{
    qDebug("My PresenterTelnet::processConnect()");
    t_model->connectToTelnet(t_view->getIPAddress(),t_view->getLogin(),t_view->getPassword());
}

void PresenterTelnet::onCommand(QString command)
{
    t_model->onCommand(command);
    //qDebug("My PresenterTelnet::onCommand()");
}

/*
void PresenterTelnet::response(const QString& msg)
{
    t_model->response(msg);
}

void PresenterTelnet::error(QString errorMsg)
{
    //Отправлять на форму сообщение об ошибке
}

void PresenterTelnet::timeout(QString timeoutMsg)
{
    //Отправляем на форму сообщение что время истекло
}


    Обновить представление
  */
void PresenterTelnet::refreshView() const
{

}

