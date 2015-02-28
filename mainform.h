#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "field.h"

namespace Ui
{
    class MainForm;
}
/*
enum Type
{
    Computer,
    Router
};
*/

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = 0);
    ~MainForm();

private:
    Ui::MainForm *ui;
    Field *work_field;
    bool eventFilter(QObject * obj, QEvent * evnt);
    //QString name;

private slots:

    void addComputer();
    void addRouter();
    void addLinc(bool flag);
    //QString
};

#endif // MAINFORM_H
