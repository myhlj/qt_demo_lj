#ifndef BOTTOMPICLABEL_H
#define BOTTOMPICLABEL_H
#include <QLabel>

class BottomPicLabel : public QLabel
{
    Q_OBJECT
public:
    BottomPicLabel(QWidget * parent = 0);
protected:
   virtual void mousePressEvent(QMouseEvent *);

signals:
    void push_down(void);
};

#endif // BOTTOMPICLABEL_H
