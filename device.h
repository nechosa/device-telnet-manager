#ifndef DEVICE_H
#define DEVICE_H

#include "field.h"
#include <QImage>
#include <GL/gl.h>

class Field;

enum EnumType
{
    Computer = 1,
    Router = 2
};

// ����� �������� �� ����������� ����������
class Device//: public Field
{

   // Q_OBJECT


    bool eventFilter(QObject * obj, QEvent * evnt);

    protected:

   Field * parent; // ������� ����

    int X,Y; //���������� �� ����������
    QString Name;
    int H,W; //������ � ������ �� ����������

    QImage pixx,PIXX; // �������� ����

    GLfloat R1,G1,B1;
    GLfloat R2,G2,B2;

    GLfloat R1S,G1S,B1S;
    GLfloat R2S,G2S,B2S;
    GLfloat R1L,G1L,B1L;

    //int X,Y; // ���������� �� ����������
   /* int heigth,width; // ������ � ������ �� ����������
    int linewidth; // ������� �����
    */
/*
    QString name;
    QString ip_addr;//QURL
    QString comment;
    */

public:
    Device(Field *work_field,int tmpX, int tmpY/*GLfloat tmpX, GLfloat tmpY*/,QString image, QString myName);

    virtual ~Device();
    bool isSel;//������� ��������� ����������
    /*
    bool isSelected;
    bool isActive;

    //������������� � ���������� ������
    virtual void resize(int w, int h);
    virtual int getWidth();
    virtual int getHeigth();

    //������������� ���������� ������ ����� ����������
    */
    virtual void move(int x, int y);


      virtual int x();
      virtual int y();
       virtual QString getName();

    virtual int width();
    virtual int height();
/*
    //������������� � ���������� ������� �����
    virtual line_width;
    virtual void setLineWidth(int line_width);

    //������������� � ���������� �������� ����
    virtual void setPix(QImage &px);
    virtual QImage pix();
    */
    virtual void setIsSelected(bool fl);
    virtual bool getIsSelected();

    virtual void contextMenuEvent(QContextMenuEvent *e);
    virtual void mousePressEvent(QMouseEvent *event);

    virtual void setPix(QImage &px);
    virtual QImage pix();
    virtual void paint();


};


class Link
{
protected:
    GLfloat R1,G1,B1;//���� ����������� �������
    GLfloat R2,G2,B2;
    GLfloat R1S,G1S,B1S;//���� ����������� ������� (��� ���������)
    GLfloat R2S,G2S,B2S;

private:
    //��� � ���
    QString name;
    int type;
    //������� �����
    int LineWidth;

public:

 bool isSel;//������� ��������� ����������

    //������ � ��������� �����
    Device * begining;
    Device * ending;

    //����������� � ���������� ������
    Link(Device * first, Device * last, QString theName, int theType, int theWidth);
    virtual ~Link();

    //������������� � ���������� ����
    virtual void setColor(int r1, int g1, int b1,int r2 = 255, int g2 = 255, int b2 = 255);
    virtual void getColor(int &r1, int &g1,int &b1, int &r2,int &g2,int &b2)  ;
    virtual void setColorSelected(int r1, int g1, int b1,int r2 = 255, int g2 = 255, int b2 = 255);
    virtual void getColorSelected(int &r1, int &g1,int &b1, int &r2,int &g2,int &b2)  ;


    //������������� � ���������� ������� ��������

    virtual void setIsSelected(bool fl);
    virtual bool isSelected()  ;

    //��������� ����� �����
    virtual void paint(int aniStep);

    //���������� ������� � ������, ������� ����� ������������ ��� ��������� �����
    virtual QRect getCentralArea();

    //��������� �������� ����������
    void SetActive(bool activ);

    //������������� ��� � ���
    void setName(QString n);
    void setType(int t);

    //���������� ��� � ���
    QString getName();
    int getType();

    //��������� � ������� ������� �����
    void setWidth(int w);
    int getWidth();
};

#endif // DEVICE_H
