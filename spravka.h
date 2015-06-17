/********************************************************
* Имя файла: spravka.h
* Назначение модуля: справка о программе
* Автор: Zakharov
* Дата создания:           2013/19/06
* Дата последней редакции: 2013/19/06
*********************************************************/

#ifndef SPRAVKA_H
#define SPRAVKA_H

#include <QDialog>

namespace Ui {
    class spravka;
}

class spravka : public QDialog {
    Q_OBJECT
public:
    spravka(QWidget *parent = 0);
    ~spravka();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::spravka *ui;

};

#endif // SPRAVKA_H
