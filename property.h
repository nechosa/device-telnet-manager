#ifndef PROPERTY_H
#define PROPERTY_H

#include <QtGui/QDialog>

namespace Ui {
    class Property;
}

class Property : public QDialog {
    Q_OBJECT
public:
    Property(QWidget *parent = 0);
    void setName(const QString & p_name);
    ~Property();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Property *m_ui;
};

#endif // PROPERTY_H
