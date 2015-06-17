#ifndef LINK_H
#define LINK_H

#include "field.h"
#include "device.h"
#include "text.h"
class Field;
class Device;
class Text;
class Link
{
protected:
    GLfloat R1,G1,B1;//���� ����������� �������
    GLfloat R2,G2,B2;
    GLfloat R1S,G1S,B1S;//���� ����������� ������� (��� ���������)
    GLfloat R2S,G2S,B2S;
protected:

    Field * parent; // ������� ����


private:
    //��� � ���
    QString name;
    QString eth0;
    QString eth1;
    int type;
    //������� �����
    int LineWidth;


public:
Text *txt1;
Text *txt2;
int dx1,dy1; //���������� ��� ���������� �������
int x11,y11; //���������� ����������
    bool isSel;//������� ��������� ����������

    //������ � ��������� �����
    Device * begining;
    Device * ending;

    //����������� � ���������� ������
    Link(Field *work_field,Device * first, Device * last, QString theName, int theType, int theWidth,
         QString l_eth0,QString l_eth1,
          int x_eth0,int y_eth0,
         int x_eth1,int y_eth1);
    virtual ~Link();

    //������������� � ���������� ����
    virtual void setColor(int r1, int g1, int b1,int r2 = 255, int g2 = 255, int b2 = 255);
    virtual void getColor(int &r1, int &g1,int &b1, int &r2,int &g2,int &b2)  ;
    virtual void setColorSelected(int r1, int g1, int b1,int r2 = 255, int g2 = 255, int b2 = 255);
    virtual void getColorSelected(int &r1, int &g1,int &b1, int &r2,int &g2,int &b2)  ;


    //������������� � ���������� ������� ��������

    virtual void setIsSelected(bool fl);
    virtual bool isSelected() const;

    bool active;
    void setActive(bool t_active);

    bool isActive;

    //��������� ����� �����
    void paintPoint(GLfloat x1,GLfloat y1,GLfloat x2,GLfloat y2,GLfloat KS,int R);
    virtual void paint(int aniStep);

    //���������� ������� � ������, ������� ����� ������������ ��� ��������� �����
    virtual QRect getCentralArea() const;

    //��������� �������� ����������
    void SetActive(bool activ);

    //������������� ��� � ���
    void setName(QString n);
    void setType(int t);

    //���������� ��� � ���
    QString getName() const;
    int getType() const;

    //��������� � ������� ������� �����
    void setWidth(int w);
    int getWidth() const;

     //void setCoord(int x,int y);
};

#endif // LINK_H
