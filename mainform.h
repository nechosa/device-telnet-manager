/******************************************************************
  * ��� ����� : mainform.h
  * ���������� ������: ����� ������� ����� ���������(�������� ���������� ������)
  * �������:
  * �����: ��ޣ�� �.�.
  * ���� �������� :           2015-03-16
  * ���� ��������� �������� : 2012-03-16
  *****************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "field.h" // ����� �������� ���� ��� ���������� ����������


namespace Ui
{
    class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();
    void virtual keyReleaseEvent(QKeyEvent *event);

    void setDirData(const QString &dir);
    const QString getDirData() const;
    void setDirProtocol(const QString &dir);
    const QString getDirProtocol() const;

private:
    Ui::MainForm *ui;

    QString name; //��� ����������
    QString dirProtocol; //������� ����������������
    int isProtokol; //

    QString dirData; // ������� �������� ������
    int oprosPeriod; //
    int otvetPeriod; //

    QString imageName; // �������� ��������

    //QList <ThreadMyPing *>lstPing;

    Field *work_field;// ������� ���� ��� ���������� ����������
    bool shift; //
    int key1; // ����

    void closeEvent(QCloseEvent *event); // �������� �����
    bool eventFilter(QObject * obj, QEvent * evnt); // ������ �������

    void ClearField(); // ������� ����

    void loadFromFile(QString fname); // �������� �� �����
    void saveToFile(QString fname); // ��������� � ����

private slots:
/*
    void on_action_route2_triggered();
    void on_action_route1_triggered();
    void on_action_route3_triggered();
*/
    void on_action_triggered();
    void on_actionShowInfo_triggered();
    void on_action_route2_hovered();
    void on_action_route1_hovered();//��������� ����� �� ������ ��������  1

    void addComputer(bool flag);    // �������� ���������
    void addRouter(bool flag);      // �������� �������������
    void addRadio(bool flag);      // �������� ���������
    void addLinc(bool flag);        // �������� �����

    void slotNew();         // ���� ��� �������� ����� ����������
    void slotOpen();        // ���� ��� �������� ����� ����������
    void slotSave();        // ���� ��� ���������� ����� ����������
    void slotSave_as();     // ���� ��� ���������� ����� ����������
    void slotSave_image();  // ���� ��� ���������� ��������
    void slotExit();        // ���� ��� ������

    void slotAbout();        // ���� ��� ����������� ����������

    void slotShowInfo(bool show); // ���� ��� �����������/������� ����������


    void selectRouter1(bool flag);  // ����� ��������  1
    void selectRouter2(bool flag);  // ����� ��������  2
    void selectRouter3(bool flag);  // ����� ��������  3

    void selectRouter1();  // ����� ��������  1
    void selectRouter2();  // ����� ��������  2
    void selectRouter3();  // ����� ��������  3

    void informRouter();
    void setDefault();  // ���������� ��� ��-���������

    void saveRoute1();
    void saveRoute2();
    void saveRoute3();

    signals:
    void action_Route(int);
    void saveRoute(int);
};

#endif // MAINFORM_H
