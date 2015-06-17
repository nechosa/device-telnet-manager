#ifndef FIELD_H
#define FIELD_H

#include <QGLWidget>
#include <GL/gl.h>
#include <qgl.h>
#include <QImage>
#include <QEvent>
#include <QMouseEvent>
#include <QWidget>
#include "device.h"
#include "const.h"
#include "link.h"
#include "text.h"

#include <QList>


class Field : public QGLWidget
{
    Q_OBJECT
    //Q_ENUMS(DeviceType)

private:
    DeviceType create_dev;

public:
    void setcheckDevice(DeviceType create_new_dev);
    /*
    private:
    DeviceType create_dev;
    public:
    DeviceType setcheckDevice(DeviceType create_new_dev);
*/

protected:
    //������ ���������
    QList <Device *> items;
    QList <Link *> links;

    //QList<T> routes;
    //QList <QList <Link *> > routes; //���������� ���������

    QList <Link *> route1;
    QList <Link *> route2;
    QList <Link *> route3;

    //QList <Link> route3;
    //Link *lnk;

    GLfloat R1,G1,B1;//���� ����������� ������� ����
    GLfloat R2,G2,B2;
    //bool flagAnimation;//������� ��������
    //int speedAnimation;//�������� ��������
    //QTime ani;// ����� ��������

    Device * movingBlock;
    Text * movingText;
    Text * movingText2;

    //����������, ����������� ��� ���������� �����
    bool flagAddLinkRegime;
    int tmpBeg;
    int tmpText;
    int tmpText2;
    int tmpEnd;
    GLfloat tmpX;
    GLfloat tmpY;
    GLfloat blockX;
    GLfloat blockY;
    GLfloat shiftX;
    GLfloat shiftY;
    GLfloat shiftTranslateX;
    GLfloat shiftTranslateY;

    GLfloat t_blockX;
    GLfloat t_blockY;

    bool shiftMode;
    bool selectMode;
    bool additionSelectionMode;
    QRect selectedArea;

    QImage wallpaper;
    QImage wallpaperGL;

public:
    //����������� � ���������� ������
    Field(QWidget * parent);
    virtual ~Field();


    //������ �� ������� ��������� ����������
    //Device
    virtual void addItem(int x, int y,DeviceType type/*QString name, int type,QString address,QString image,QString name*/);
    virtual void appendItem(Device * newItem);
    virtual void delItem(int num);
    virtual int getItemsCount() const;

    virtual void clearItems();
    virtual void setActive(bool active);
    virtual void setInfo(bool active);
    virtual void showRoute(int route,bool active);
    virtual void addRoute(int route);
    virtual Device * getItem(int num) const;
    virtual Device * getLastSelectedItem();

    //Link
    virtual Link * addLinkByNum(int begNum, int endNum);
    virtual Link * addLink(Device * beg, Device * end);
    virtual void appendLink(Link * newLink);
    virtual void delLink(int num);
    virtual Link * getLink(int num) const;
    virtual int getLinksCount() const;
    virtual void clearLinks();


    // virtual void mousePressEvent(QMouseEvent *event);

    /*virtual void delItem(int num);
    virtual net_node * getItem(int num) const;
    virtual int getItemsCount() const;
    virtual void clearItems();
    virtual net_node * getLastSelectedItem();
/*
    //������ �� ������� ������ ��������� ����������
    virtual net_channel * addLinkByNum(int begNum, int endNum);
    virtual net_channel * addLink(net_node * beg, net_node * end);
    virtual void appendLink(net_channel * newLink);
    virtual void delLink(int num);
    virtual net_channel * getLink(int num) const;
    virtual int getLinksCount() const;
    virtual void clearLinks();
    */

    //������������ � ���������� ������� � �������� ��������
    /*
    virtual void setIsAnimation(bool isAni);
    virtual bool isAnimation();
    virtual void setAnimationSpeed(int newSpeed);
    virtual int getAnimationSpeed();
    */

    //������������� � ���������� ���� ������� �������� ����
    virtual void setColor(int r1, int g1, int b1, int r2 = 255, int g2 = 255, int b2 = 255);
    virtual void getColor(int &r1, int &g1, int &b1, int &r2, int &g2, int &b2) ;

    virtual void setEditRegime(bool er);
    virtual bool getEditRegime();

    //����������� ������ ������  OpenGL
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    //��������� � ������� ������� � ���������
    virtual void setShiftTranslateX(int newX);
    virtual int getShiftTranslateX() const;
    virtual void setShiftTranslateY(int newY);
    virtual int getShiftTranslateY() const;

    //��������� � ������� �������� �����������
    virtual void setWallpaper(QImage & img);
    virtual QImage getWallpaper() const;
    virtual QImage getWallpaperGL() const;

    virtual void contextMenuEvent(QContextMenuEvent *e);

    //������� ����� � ��������� ����� � ������� �����

    QList <Device *> getLstNode();

    QList <Link *> getLstChannel();


public slots:
    virtual bool eventFilter(QObject * obj, QEvent * evnt);
    void createTerminal();
    void createProperty();
    void SlotAddChannel(int indBeg, int indEnd);

signals:
    // ����������� ��� ������ ���������� ����� � ������� ����, ����� ��������� ��� �����
    void newLinkAdded(int begin, int end);
    //���������� ��� ������� ����� �� �����
    void SignalEdit();
    //����������� ��� ����� �� ������ �����
    void SignalDelChan(int n);
    void setDefault();
};

#endif // FIELD_H
