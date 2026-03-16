#include "clamdconfmultioption.h"
#include "ui_clamdconfmultioption.h"
#define css_mono "background-color:#404040;color:white"

clamdconfmultioption::clamdconfmultioption(QWidget* parent, QString keyword, bool checked, QString label, QStringList values, setupFileHandler * setupFile, setupFileHandler * baseSetupFile)
    : QWidget(parent), m_ui(new Ui::clamdconfmultioption), m_keyword(keyword), m_checked(checked), m_label(label), m_values(values), m_setupFile(setupFile), m_baseSetupFile(baseSetupFile)
{
    m_ui->setupUi(this);
    if ((m_label.indexOf("directories") != -1) && (m_label.indexOf("REGEX") == -1)) m_fileselector = true; else m_fileselector = false;
    m_label = QCoreApplication::translate("ClamAV", m_label.toUtf8().constData());
    m_label = translator::beautifyString(m_label,120);
    m_ui->checkBox->setToolTip(m_keyword);
    if (m_values.length() > 0) {
        m_ui->checkBox->setChecked(true);
        m_ui->comboBox->addItems(m_values);
    } else {
        m_ui->checkBox->setChecked(false);
    }

    m_ui->checkBox->setText(m_label);

    m_startup = false;
    slot_checkBoxClicked();
}

clamdconfmultioption::~clamdconfmultioption()
{
    delete m_ui;
}

void clamdconfmultioption::slot_checkBoxClicked()
{
    if (!m_startup) {
        bool state = m_ui->checkBox->isChecked();

        m_ui->comboBox->setEnabled(state);
        state ? m_ui->frame->setStyleSheet(css_mono) : m_ui->frame->setStyleSheet("");
        QStringList templist = m_setupFile->getSingleLineValues(m_keyword);

        foreach (QString entry, templist) {
            if (!state) {
                m_baseSetupFile->setSectionValue(m_keyword,entry,"used");
            }
            m_setupFile->removeSingleLine(m_keyword,entry);
        }

        if (state) {
            if (m_ui->comboBox->count() == 0) {
                QStringList entries = m_baseSetupFile->getKeywords(m_keyword);
                m_ui->comboBox->addItems(entries);
            }
            m_baseSetupFile->removeSection(m_keyword);
            for (int i = 0; i < m_ui->comboBox->count(); i++) {
                m_setupFile->addSingleLineValue(m_keyword,m_ui->comboBox->itemText(i));
            }
            m_ui->addPushButton->setDisabled(false);
            m_ui->delPushButton->setDisabled(false);
        } else {
            m_ui->addPushButton->setDisabled(true);
            m_ui->delPushButton->setDisabled(true);
        }
        emit settingChanged();
    }
}

void clamdconfmultioption::slot_addButtonClicked()
{
    QString newValue;

    if (m_fileselector == false) newValue = QInputDialog::getText(this,m_keyword,m_keyword); else newValue = QFileDialog::getExistingDirectory(this,m_keyword);
    if (newValue != "") {
        m_setupFile->addSingleLineValue(m_keyword,newValue);
        QStringList values = m_setupFile->getSingleLineValues(m_keyword);
        m_ui->comboBox->clear();
        m_ui->comboBox->addItems(values);
    }
    emit settingChanged();
}

void clamdconfmultioption::slot_delButtonClicked()
{
    if (m_ui->comboBox->currentText() != "") {
        m_setupFile->removeSingleLine(m_keyword,m_ui->comboBox->currentText());
        m_ui->comboBox->removeItem(m_ui->comboBox->currentIndex());
    }
    emit settingChanged();
}
