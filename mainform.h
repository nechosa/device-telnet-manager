/******************************************************************
  * Имя файла : mainform.h
  * Назначение модуля: Класс главной формы программы(описание интерфейса класса)
  * Функции:
  * Автор: Нечёса И.А.
  * Дата создания :           2015-03-16
  * Дата последней редакции : 2012-03-16
  *****************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

#include <QtGui/QMainWindow>
#include "field.h" // класс рабочего поля для построения мнемосхемы


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

    QString name; //имя мнемосхемы
    QString dirProtocol; //каталог протоколирования
    int isProtokol; //

    QString dirData; // каталог исходных данных
    int oprosPeriod; //
    int otvetPeriod; //

    QString imageName; // название картинки

    //QList <ThreadMyPing *>lstPing;

    Field *work_field;// рабочее поле для построения мнемосхемы
    bool shift; //
    int key1; // ключ

    void closeEvent(QCloseEvent *event); // закрытие формы
    bool eventFilter(QObject * obj, QEvent * evnt); // фильтр событий

    void ClearField(); // очистка поля

    void loadFromFile(QString fname); // загрузка из файла
    void saveToFile(QString fname); // сохранить в файл

private slots:
/*
    void on_action_route2_triggered();
    void on_action_route1_triggered();
    void on_action_route3_triggered();
*/
    void on_action_triggered();
    void on_actionShowInfo_triggered();
    void on_action_route2_hovered();
    void on_action_route1_hovered();//Наведение мышки на кнопку маршрута  1

    void addComputer(bool flag);    // Добавить компьютер
    void addRouter(bool flag);      // Добавить маршрутизатор
    void addRadio(bool flag);      // Добавить Радиомост
    void addLinc(bool flag);        // Добавить Связь

    void slotNew();         // слот для создания новой мнемосхемы
    void slotOpen();        // слот для открытия новой мнемосхемы
    void slotSave();        // слот для сохранения новой мнемосхемы
    void slotSave_as();     // слот для сохранения новой мнемосхемы
    void slotSave_image();  // слот для сохранения картинки
    void slotExit();        // слот для выхода

    void slotAbout();        // слот для отображения информации

    void slotShowInfo(bool show); // слот для отображения/скрытия информации


    void selectRouter1(bool flag);  // выбор маршрута  1
    void selectRouter2(bool flag);  // выбор маршрута  2
    void selectRouter3(bool flag);  // выбор маршрута  3

    void selectRouter1();  // выбор маршрута  1
    void selectRouter2();  // выбор маршрута  2
    void selectRouter3();  // выбор маршрута  3

    void informRouter();
    void setDefault();  // установить все по-умолчанию

    void saveRoute1();
    void saveRoute2();
    void saveRoute3();

    signals:
    void action_Route(int);
    void saveRoute(int);
};

#endif // MAINFORM_H
