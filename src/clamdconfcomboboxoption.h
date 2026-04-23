#ifndef CLAMDCONFCOMBOBOXOPTION_H
#define CLAMDCONFCOMBOBOXOPTION_H

#include "ui_clamdconfcomboboxoption.h"
#include "clamdconfoptionbaseclass.h"
#include "setupfilehandler.h"
#include "translator.h"

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class clamdconfcomboboxoption;
}

class clamdconfcomboboxoption : public ClamdConfOptionBaseClass
{
    Q_OBJECT

public:
    explicit clamdconfcomboboxoption(QWidget *parent = nullptr, 
                                     QString keyword="", 
                                     bool checked=false, 
                                     QString label="", 
                                     QString options="",
                                     setupFileHandler * setupFile = nullptr);
    ~clamdconfcomboboxoption() = default;

    QString getKeyword();
    QString getLabel();
    void setValue(QString value = 0);
    QString getValue();
    void setChecked(bool checked = true);
    bool isChecked();

private:
    Ui::clamdconfcomboboxoption m_ui;
    QString m_optionKeyword;
    QString m_comment;
    bool m_startup{ true};
    setupFileHandler    * m_setupFile;

private slots:
    void slot_checkBoxClicked();
    void slot_comboBoxChanged();

signals:
    void settingChanged();
};

#endif // CLAMDCONFCOMBOBOXOPTION_H
