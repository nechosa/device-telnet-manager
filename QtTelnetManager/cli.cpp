#include "cli.h"

#include <QString>
#include <QtGui>
#include <QScrollBar>
#include <QPalette>

CLI::CLI(QWidget* parent) : QTextEdit(parent)
{
    promt = "cicso> ";

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);

    insertPromt(false);
    isLocked = false;

    time = new QTime();

    history = new QStringList();
    historyPos = 0;
}

void CLI::keyPressEvent(QKeyEvent* event)
{
    if (isLocked)
    {
        return;
    }


    if (event->key() >= 0x20 && event->key() <= 0x7e
           && (event->modifiers() == Qt::NoModifier || event->modifiers() == Qt::ShiftModifier))
    {
            QTextEdit::keyPressEvent(event);
    }


    
    if (event->key() == Qt::Key_Backspace
           && event->modifiers() == Qt::NoModifier
           && textCursor().position() > promt.length())
    {
            QTextEdit::keyPressEvent(event);
    }
    


    if (event->key() == Qt::Key_Return && event->modifiers() == Qt::NoModifier)
    {
            onEnter();
    }


    if (event->key() == Qt::Key_Up && event->modifiers() == Qt::NoModifier)
    {
        historyBack();
    }

    if (event->key() == Qt::Key_Down && event->modifiers() == Qt::NoModifier)
    {
        historyForward();
    }

}

void CLI::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(*event)
}

void CLI::contextmenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(*event)
}

void CLI::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(*event)

    setFocus();
}

void CLI::insertPromt(bool insertNewBlock)
{
    scrollDown();

    QTextCharFormat format;
    format.setForeground(Qt::green);
    textCursor().setBlockCharFormat(format);

    if(insertNewBlock)
    {
        textCursor().insertBlock();
    }
    textCursor().insertText(promt);
}


void CLI::onEnter()
{

      //  qDebug("onEnter()");
     //qDebug()<<message;
    isLocked = true;


    if (textCursor().position() == promt.length())
    {
        insertPromt();
        return;
    }


    QString cmd = textCursor().block().text().mid(promt.length());

    historyAdd(cmd);
    emit onCommand(cmd);
    //qDebug()<<"cmd = "<<cmd;
    insertPromt();
    isLocked = false;
}

void CLI::output(QString s)
{
    QTextCharFormat format;
    QString a;

    //format.setForeground(Qt::white);
    textCursor().setBlockCharFormat(format);
    textCursor().insertBlock();
    a = time->currentTime().toString() +":  " + s;
    textCursor().insertText(a);


    isLocked = false;


    insertPromt();
}

void CLI::scrollDown()
{
    QScrollBar *vbar = verticalScrollBar();
    vbar->setValue(vbar->maximum());
}

void CLI::historyAdd(QString cmd)
{
    history->append(cmd);

    historyPos = history->length();
}

void CLI::historyBack()
{
    if (!historyPos)
    {
        return;
    }

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(promt + history->at(historyPos - 1));
    setTextCursor(cursor);
    historyPos--;
}

void CLI::historyForward()
{
    if (historyPos == history->length())
    {
            return;
    }

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfBlock);
    cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();

    if (historyPos == history->length() - 1)
    {
        cursor.insertText(promt);
    }
    else
    {
        cursor.insertText(promt + history->at(historyPos + 1));
    }

    setTextCursor(cursor);
    historyPos++;
}

