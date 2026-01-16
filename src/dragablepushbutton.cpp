#include "dragablepushbutton.h"

dragablePushButton::dragablePushButton(QWidget* parent) : QPushButton(parent)
{
    m_ui.setupUi(this);
}

dragablePushButton::dragablePushButton(QIcon icon, QString text, QWidget* parent, QString dragText) : QPushButton(icon, text, parent)
{
    m_dragDropText = dragText;
}

void dragablePushButton::mouseMoveEvent(QMouseEvent* event)
{
    QUrl url("file://" + m_dragDropText);
    QList<QUrl> urls;
    //event = event;

    urls << url;
    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;

    mimeData->setText("file://" + m_dragDropText);
    mimeData->setUrls(urls);

    drag->setMimeData(mimeData);
    drag->setPixmap(QPixmap(":/icons/icons/media.png"));

    emit dragStarted();

    drag->exec();
}
