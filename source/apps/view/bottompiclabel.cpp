#include "bottompiclabel.h"

BottomPicLabel::BottomPicLabel(QWidget *parent) : QLabel(parent)
{

}

void BottomPicLabel::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);
    emit push_down();
}

