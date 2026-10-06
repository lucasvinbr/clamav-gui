/************************************************************************
 * Round progress dialog used by freshclamsetter
************************************************************************/
#include "progressdialog.h"

progressDialog::progressDialog(QWidget* parent) 
: QWidget(parent)
{
    m_ui.setupUi(this);
    m_progressBar = new QRoundProgressBar(this);
    m_progressBar->setGeometry((this->width() - 80) / 2, 20, 100, 100);
    m_progressBar->setMaximum(100);
    m_progressBar->setMinimum(0);
    m_progressBar->setValue(0);
    m_progressBar->setBarStyle(QRoundProgressBar::StyleDonut);
    m_progressBar->setFormat("");
    m_progressBar->show();
}

void progressDialog::setText(QString text)
{
    QString output = text.replace("\n", "");

    m_ui.progressText->setText(output);
}

void progressDialog::setProgressBarMaxValue(double value)
{
    m_progressBar->setMaximum(value);
}

void progressDialog::setProgressBarValue(double value)
{
    m_progressBar->setValue(value);
}
