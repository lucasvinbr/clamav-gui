#ifndef CLAMDCONFMULTIOPTION_H
#define CLAMDCONFMULTIOPTION_H

#include <QWidget>
#include <QInputDialog>
#include <QFileDialog>
#include "setupfilehandler.h"
#include "clamdconfoptionbaseclass.h"
#include "translator.h"

namespace Ui
{
class clamdconfmultioption;
}

class clamdconfmultioption : public ClamdConfOptionBaseClass
{
    Q_OBJECT

   public:
    explicit clamdconfmultioption(QWidget* parent = nullptr,
                                  QString keyword = "",
                                  bool checked = false,
                                  QString label = "",
                                  QStringList values = QStringList(),
                                  setupFileHandler* = nullptr,
                                  setupFileHandler* = nullptr);
    ~clamdconfmultioption();

    QString getKeyword();
    QString getLabel();
    void setValue(QString value = 0);
    QString getValue();
    void setChecked(bool checked = true);
    bool isChecked();

   private:
    Ui::clamdconfmultioption* m_ui;
    QString                   m_keyword;
    bool                      m_checked;
    bool                      m_startup;
    bool                      m_fileselector;
    QString                   m_label;
    QString                   m_comment;
    QStringList               m_values;
    setupFileHandler        * m_setupFile;
    setupFileHandler        * m_baseSetupFile;
   private slots:
    void slot_checkBoxClicked();
    void slot_addButtonClicked();
    void slot_delButtonClicked();
   signals:
    void settingChanged();

};

#endif  // CLAMDCONFMULTIOPTION_H
