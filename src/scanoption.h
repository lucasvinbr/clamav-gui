#ifndef SCANOPTION_H
#define SCANOPTION_H

#include "ui_scanoption.h"
#include "setupfilehandler.h"
#include "translator.h"
#include <QWidget>

namespace Ui {
class scanoption;
}

class scanoption : public QWidget
{
    Q_OBJECT

public:
    explicit scanoption(QWidget *parent = nullptr, QString setupFileName = "", QString section = "", bool checked = false, QString label = "", QString comment = "");
    ~scanoption() = default;

private:
    Ui::scanoption m_ui;
    setupFileHandler * m_setupFile;
    QString m_setupFileSection;
    QString m_option;
    QString m_com;

private slots:
    void slot_checkboxClicked();

signals:
    void valuechanged();
};

#endif // SCANOPTION_H
