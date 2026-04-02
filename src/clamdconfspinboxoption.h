#ifndef CLAMDCONFSPINBOXOPTION_H
#define CLAMDCONFSPINBOXOPTION_H

#include "ui_clamdconfspinboxoption.h"

#include "translator.h"
#include "setupfilehandler.h"
#include "clamdconfoptionbaseclass.h"

#include <QWidget>

namespace Ui {
class clamdconfspinboxoption;
}

class clamdconfspinboxoption : public ClamdConfOptionBaseClass
{
    Q_OBJECT

public:
    explicit clamdconfspinboxoption(QWidget *parent = nullptr, 
                                    QString keyword = "", 
                                    bool checked = false, 
                                    QString label = "", 
                                    QString options = "0,99,1,1",
                                    setupFileHandler * setupFile = nullptr);
    ~clamdconfspinboxoption() = default;

    QString getKeyword();
    QString getLabel();
    void setValue(QString value = 0);
    QString getValue();
    void setChecked(bool checked = true);
    bool isChecked();

private:
    Ui::clamdconfspinboxoption m_ui;
    QString m_optionKeyword;
    bool m_startup {true};
    setupFileHandler    * m_setupFile;

private slots:
    void slot_checkboxClicked();
    void slot_spinboxChanged();

signals:
    void settingChanged();
};

#endif // CLAMDCONFSPINBOXOPTION_H
