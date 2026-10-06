/*******************************************************************
 * Overloaded frame class to display a costum background
 *******************************************************************/
#include "myframe.h"

myFrame::myFrame(QWidget* parent) : QFrame(parent)
{
    m_ui.setupUi(this);
}

void myFrame::setVersionLabel(QString text)
{
    m_ui.versionLabel->setText(text);
}

void myFrame::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    QRectF r1(0.0, 0.0, 220.0, 650.0);
    painter.drawImage(r1, QImage(":/icons/icons/logo.png"));

    QFrame::paintEvent(e);
}
