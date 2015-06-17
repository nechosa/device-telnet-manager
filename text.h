#ifndef TEXT_H
#define TEXT_H
#include "field.h"

class Field;
class Text{

private:

    QString text;
    bool visible;

protected:

    Field * parent; // рабочее поле
    int X,Y; //координаты на мнемосхеме

    int H,W; //высота и ширина на мнемосхеме
    int linewidth; // толщина линии
    GLfloat R1,G1,B1;
    GLfloat R2,G2,B2;
    GLfloat R1S,G1S,B1S;
    GLfloat R2S,G2S,B2S;
    GLfloat R1L,G1L,B1L;

public:

    Text(Field *work_field,int tmpX, int tmpY,QString text);
    virtual ~Text();

    bool isSel;

    virtual void move(int x, int y);

    virtual int x() const;
    virtual int y() const;

    virtual int width() const;
    virtual int height() const;
    virtual void setIsSelected(bool fl);
    virtual bool getIsSelected();

    void setVisible(bool t_visible);
    bool isVisible();

    QString getText() const;
    void setText(QString t_text);

    int getLineWigth() const;
    void setLineWigth(int lw);

    virtual void paint();


};

//template <typename T>
#endif // TEXT_H
