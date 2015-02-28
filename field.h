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
#include <QList>

class Field : public QGLWidget
{
    Q_OBJECT
protected:
    //������ ���������
    QList <Device *> items;

    //QList <net_channel *> links;

    GLfloat R1,G1,B1;//���� ����������� ������� ����
    GLfloat R2,G2,B2;
    //bool flagAnimation;//������� ��������
    //int speedAnimation;//�������� ��������
    //QTime ani;// ����� ��������

    //net_node * movingBlock;

    //����������, ����������� ��� ���������� �����
    bool flagAddLinkRegime;
    int tmpBeg;
    int tmpEnd;
    GLfloat tmpX;
    GLfloat tmpY;
    GLfloat blockX;
    GLfloat blockY;
    GLfloat shiftX;
    GLfloat shiftY;
    GLfloat shiftTranslateX;
    GLfloat shiftTranslateY;

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

    virtual void addItem(int x, int y/*QString name, int type,QString address*/,QString image,QString name);
    virtual void appendItem(Device * newItem);
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
   /*
    QList <net_channel *> getLstChannel();
    */

public slots:
    virtual bool eventFilter(QObject * obj, QEvent * evnt);
    void createTerminal();

signals:
    // ����������� ��� ������ ���������� ����� � ������� ����, ����� ��������� ��� �����
    void newLinkAdded(int begin, int end);
    //���������� ��� ������� ����� �� �����
    void SignalEdit();
    //����������� ��� ����� �� ������ �����
    void SignalDelChan(int n);
};

#endif // FIELD_H