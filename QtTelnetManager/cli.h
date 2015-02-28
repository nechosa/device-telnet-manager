#ifndef CLI_H
#define CLI_H

#include <QTextEdit>

#include <QString>
#include <QTime>
#include <QTextEdit>
#include <QDebug>

class CLI : public QTextEdit
{
    Q_OBJECT

public:
    explicit CLI(QWidget* parent = 0);

    void output(QString s);
    void scrollDown();

protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void contextmenuEvent(QContextMenuEvent* event);

private:
    QString promt;
    QTime* time;
    bool isLocked;
    QStringList* history;
    int historyPos;


    void insertPromt(bool insertNewBlock = true);
    void onEnter(void);

    void historyBack();
    void historyForward();
    void historyAdd(QString cmd);

signals:
    void onCommand(QString cmd);
};

#endif // CLI_H
