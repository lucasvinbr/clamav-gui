#include "clamdconfstringoption.h"
#define css_mono "background-color:#404040;color:white"

clamdConfStringOption::clamdConfStringOption(QWidget* parent, QString keyword, bool checked, QString label, QString options,
                                             setupFileHandler* setupFile)
    : ClamdConfOptionBaseClass(parent), m_optionKeyword(keyword), m_optionValue(options), m_setupFile(setupFile)
{
    m_startup = true;

    m_ui.setupUi(this);

    if (m_setupFile->singleLineExists(keyword) == true)
    {
        m_ui.checkBox->setChecked(true);
        m_ui.lineEdit->setText(m_setupFile->getSingleLineValue(keyword));
    }
    else {
        m_ui.checkBox->setChecked(checked);
        m_ui.lineEdit->setText(options);
    }

// -------------------------------------------------------------------------
// For DEBUG reasons only.
/*    QFile file(QDir::homePath() + "/clamav-xx_XX.ts");
    if (file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)) {
        QTextStream stream(&file);
        stream << "    <message>\n        <source>" << label << "</source>\n        <translation>TRANS</translation>\n    </message>\n";
        file.close();
    }*/
// -------------------------------------------------------------------------

    m_comment = label;
    label = QCoreApplication::translate("ClamAV", label.toUtf8().constData());
    label = translator::beautifyString(label, 120);

    m_ui.checkBox->setText(label);
    m_ui.checkBox->setToolTip(keyword);
    m_startup = false;
    slot_checkBoxClicked();
}

QString clamdConfStringOption::getKeyword()
{
    return m_optionKeyword;
}

QString clamdConfStringOption::getLabel()
{
    return m_ui.checkBox->text();
}

void clamdConfStringOption::setValue(QString value)
{
    m_ui.lineEdit->setText(value);
}

QString clamdConfStringOption::getValue()
{
    return m_ui.lineEdit->text();
}

void clamdConfStringOption::setChecked(bool checked)
{
    m_ui.checkBox->setChecked(checked);
}

bool clamdConfStringOption::isChecked()
{
    return m_ui.checkBox->isChecked();
}

void clamdConfStringOption::slot_checkBoxClicked()
{
    if (m_startup == false)
    {
        bool state = m_ui.checkBox->isChecked();
        m_ui.lineEdit->setEnabled(state);
        if (state == true)
        {
            QString value = m_setupFile->getSingleLineValue(m_optionKeyword);
            m_setupFile->removeSingleLine(m_optionKeyword, value, m_comment);
            m_setupFile->setSingleLineValue(m_optionKeyword, m_ui.lineEdit->text(), m_comment);
        }
        else {
            QString value = m_setupFile->getSingleLineValue(m_optionKeyword);
            m_setupFile->removeSingleLine(m_optionKeyword, value, m_comment);
        }
        emit settingChanged();
        (state == true) ? m_ui.frame->setStyleSheet(css_mono) : m_ui.frame->setStyleSheet("");
    }
}

void clamdConfStringOption::slot_lineEditChanged()
{
    if (m_startup == false)
    {
        if (m_ui.checkBox->isChecked() == true)
        {
            QString value = m_setupFile->getSingleLineValue(m_optionKeyword);
            m_setupFile->removeSingleLine(m_optionKeyword, value, m_comment);
            m_setupFile->setSingleLineValue(m_optionKeyword, m_ui.lineEdit->text(), m_comment);
            emit settingChanged();
        }
    }
}
