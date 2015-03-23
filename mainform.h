#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "field.h"
//#include "device.h"


namespace Ui
{
    class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = 0);
    ~MainForm();
    void virtual keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainForm *ui;
    Field *work_field;
    //Device *dev;
    bool shift;
    int key1;
    bool eventFilter(QObject * obj, QEvent * evnt);
    //QString name;

private slots:

    void on_action_route1_hovered();
    void addComputer(bool flag);
    void addRouter(bool flag);
    void addLinc(bool flag);

    void selectRouter1(bool flag);
    void selectRouter2(bool flag);
    void selectRouter3(bool flag);

    void setDefault();
    //QStrin
};

#endif // MAINFORM_H
