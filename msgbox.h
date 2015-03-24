/****************************************************************
* ���� : msgbox.h
* ����������: ����������� ���������������� �������
* ����� : A.Kalinin, ToWpeko
* ���� ��������: 2003
* ���� ��������� ����������: 2011\11\23
**************************************************************
*__REVISION_HISTORY__
*
*****************************************************************/

#ifndef QMSGBOX_H
#define QMSGBOX_H

#ifndef QT_H
#include "qmessagebox.h"
#include "qdialog.h"
#endif // QT_H

//--- ������������ ��� ������ ��� ��������� ������� ---
enum msgDlgType
{Custom, Information, Warning, Critical, mtInformation, mtWarning, mtCritical,  mtConfirmation};


//--- ����� �������, ������������ ����� ������� ������---
int QMessageDlg( msgDlgType dlgType, QWidget *parent,	const QString& text,
                   int button0=0, int button1=0, int button2=0 );
int QMessageDlg( msgDlgType dlgType, QWidget *parent, const QString &caption,
                   const QString& text, int button0, int button1=0, int button2=0 );
int QMessageDlg( msgDlgType dlgType, QWidget *parent, const QString &caption,
                   const QString& text, const QString& button0Text = QString::null,
                   const QString& button1Text = QString::null, const QString& button2Text = QString::null,
                   int defaultButtonNumber = 0, int escapeButtonNumber = -1);
//-------------------------------

#endif
