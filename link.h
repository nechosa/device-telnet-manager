#ifndef LINK_H
#define LINK_H

#include "device.h"

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


    //������������� � ���������� ������� ���������
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

#endif // LINK_H
