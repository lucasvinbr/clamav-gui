#include "clamdconfcomboboxoption.h"
#define css_mono "background-color:#404040;color:white"

clamdconfcomboboxoption::clamdconfcomboboxoption(QWidget* parent, QString keyword, bool checked, QString label, QString options,
                                                 setupFileHandler* setupFile)
    : ClamdConfOptionBaseClass(parent), m_optionKeyword(keyword), m_setupFile(setupFile)
{
    m_ui.setupUi(this);
    m_ui.checkBox->setChecked(checked);
    QStringList m_comboBoxValues = options.split(",");

    if (m_comboBoxValues.length() > 0)
    {
        for (int i = 0; i < m_comboBoxValues.length() - 1; i++)
        {
            m_ui.comboBox->addItem(m_comboBoxValues.at(i));
        }

        if (m_setupFile->singleLineExists(m_optionKeyword) == true)
        {
            m_ui.comboBox->setCurrentText(m_setupFile->getSingleLineValue(m_optionKeyword));
            m_ui.checkBox->setChecked(true);
        }
        else {
            m_ui.comboBox->setCurrentText(m_comboBoxValues.at(m_comboBoxValues.length() - 1));
        }
    }
    else {
        m_ui.comboBox->setVisible(false);
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
    m_ui.checkBox->setText(translator::beautifyString(label, 120));
    m_ui.checkBox->setToolTip(keyword);

    m_startup = false;

    slot_checkBoxClicked();
}

QString clamdconfcomboboxoption::getKeyword()
{
    return m_optionKeyword;
}

QString clamdconfcomboboxoption::getLabel()
{
    return m_ui.checkBox->text();
}

void clamdconfcomboboxoption::setValue(QString value)
{
    int idx = m_ui.comboBox->findText(value);
    if (idx != -1) m_ui.comboBox->setCurrentIndex(idx);
}

QString clamdconfcomboboxoption::getValue()
{
    return m_ui.comboBox->currentText();
}

void clamdconfcomboboxoption::setChecked(bool checked)
{
    m_ui.checkBox->setChecked(checked);
}

bool clamdconfcomboboxoption::isChecked()
{
    return m_ui.checkBox->isChecked();
}

void clamdconfcomboboxoption::slot_checkBoxClicked()
{
    if (!m_startup)
    {
        bool state = m_ui.checkBox->isChecked();

        m_ui.comboBox->setEnabled(state);
        state ? m_ui.frame->setStyleSheet(css_mono) : m_ui.frame->setStyleSheet("");
        if (state)
        {
            QString m_value = m_setupFile->getSingleLineValue(m_optionKeyword);
            m_setupFile->removeSingleLine(m_optionKeyword, m_value, m_comment);
            m_setupFile->setSingleLineValue(m_optionKeyword, m_ui.comboBox->currentText(), m_comment);
        }
        else {
            QString m_value = m_setupFile->getSingleLineValue(m_optionKeyword);
            m_setupFile->removeSingleLine(m_optionKeyword, m_value, m_comment);
        }
        emit settingChanged();
    }
}

void clamdconfcomboboxoption::slot_comboBoxChanged()
{
    if (!m_startup)
    {
        QString m_value = m_setupFile->getSingleLineValue(m_optionKeyword);
        if (m_setupFile->singleLineExists(m_optionKeyword))
        {
            m_setupFile->removeSingleLine(m_optionKeyword, m_value, m_comment);
        }
        m_setupFile->setSingleLineValue(m_optionKeyword, m_ui.comboBox->currentText(), m_comment);
        emit settingChanged();
    }
}
