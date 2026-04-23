#ifndef CLAMDCONFSTRINGOPTION_H
#define CLAMDCONFSTRINGOPTION_H

#include "setupfilehandler.h"
#include "clamdconfoptionbaseclass.h"
#include "translator.h"
#include "ui_clamdconfstringoption.h"

#include <QWidget>

namespace Ui {
class clamdConfStringOption;
}

class clamdConfStringOption : public ClamdConfOptionBaseClass {
    Q_OBJECT

   public:
    explicit clamdConfStringOption(QWidget* parent = nullptr,
                                   QString keyword = "", 
                                   bool checked = false, 
                                   QString label = "", 
                                   QString options = "",
                                   setupFileHandler * setupFile = nullptr);
    ~clamdConfStringOption() = default;

    QString getKeyword();
    QString getLabel();
    void setValue(QString value = 0);
    QString getValue();
    void setChecked(bool checked = true);
    bool isChecked();

   private:
    Ui::clamdConfStringOption m_ui;
    QString m_optionKeyword;
    QString m_comment;
    QString m_optionValue;
    bool m_startup;
    setupFileHandler* m_setupFile;

   private slots:
    void slot_checkBoxClicked();
    void slot_lineEditChanged();

   signals:
    void settingChanged();
};

#endif  // CLAMDCONFSTRINGOPTION_H
