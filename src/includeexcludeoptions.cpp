#include "includeexcludeoptions.h"
#include "ui_includeexcludeoptions.h"
#include "sharedvars.cpp"
#define css "background-color:#404040;color:white"

includeExcludeOptions::includeExcludeOptions(QWidget* parent, setupFileHandler* setupFile) : QWidget(parent), m_setupFile(setupFile), m_ui(new Ui::includeExcludeOptions)
{
    m_ui->setupUi(this);

    if (m_setupFile->sectionExists("REGEXP_and_IncludeExclude") == true)
    {
        m_readSettingsInProgress = true;
        readSettings();
    }

    m_readSettingsInProgress = false;
    slot_highlightSettings();
}

includeExcludeOptions::~includeExcludeOptions()
{
    delete m_ui;
}

void includeExcludeOptions::slot_writeSettings()
{
    QString section = "REGEXP_and_IncludeExclude";
    QString checked;
    QString value;

    if (m_readSettingsInProgress == false)
    {
        for (int idx = 0; idx < inclExclKeywords.size(); idx++)
        {
            switch (idx)
            {
                case 0  :
                    value = m_ui->dontScanFileNameLineEdit->text();
                    checked = m_ui->dontScanFileNameCheckBox->isChecked()?"checked":"not checked";
                    break;
                case 1  :
                    value = m_ui->dontScanDirLineEdit->text();
                    checked = m_ui->dontScanDirCheckBox->isChecked()?"checked":"notChecked";
                    break;
                case 2  :
                    value = m_ui->onlyScanFileNameLineEdit->text();
                    checked = m_ui->onlyScanFileNameCheckBox->isChecked()?"checked":"notChecked";
                    break;
                case 3  :
                    value = m_ui->onlyScanDirLineEdit->text();
                    checked = m_ui->onlyScanDirCheckBox->isChecked()?"checked":"not checked";
                    break;
                case 4  :
                    value = "";
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->enablePUACheckBox->isChecked());
                    break;
                case 5  :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAPackedRadioButon->isChecked());
                    break;
                case 6  :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAPWToolRadioButton->isChecked());
                    break;
                case 7  :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUANetToolRadioButton->isChecked());
                    break;
                case 8  :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAP2PRadioButton->isChecked());
                    break;
                case 9  :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAIRCRadioButton->isChecked());
                    break;
                case 10 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUARATRadioButton->isChecked());
                    break;
                case 11 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUANetToolSpyRadioButton->isChecked());
                    break;
                case 12 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAServerRadioButton->isChecked());
                    break;
                case 13 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAScriptRadioButton->isChecked());
                    break;
                case 14 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAAndrRadioButton->isChecked());
                    break;
                case 15 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAJavaRadioButton->isChecked());
                    break;
                case 16 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAOsxRadioButton->isChecked());
                    break;
                case 17 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAToolRadioButton->isChecked());
                    break;
                case 18 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAUnixRadioButton->isChecked());
                    break;
                case 19 :
                    m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), m_ui->loadPUAWinRadioButton->isChecked());
                    break;
            }

            if (value != "")
                m_setupFile->setSectionValue(section, inclExclKeywords.at(idx), checked + "|" + value);
        }


        emit updateClamdConf();
    }
}

void includeExcludeOptions::readSettings()
{
    QString section = "REGEXP_and_IncludeExclude";
    QString checked;
    QString value;

    for (int idx = 0 ;idx < inclExclKeywords.size(); idx++)
    {
        value = m_setupFile->getSectionValue(section, inclExclKeywords.at(idx));
        checked = value.left(value.indexOf("|"));
        value = value.mid(value.indexOf("|") + 1);
        switch (idx)
        {
            case  0 :
                checked == "checked" ? m_ui->dontScanFileNameCheckBox->setChecked(true) : m_ui->dontScanFileNameCheckBox->setChecked(false);
                m_ui->dontScanFileNameLineEdit->setText(value);
                break;
            case 1  :
                checked == "checked" ? m_ui->dontScanDirCheckBox->setChecked(true) : m_ui->dontScanDirCheckBox->setChecked(false);
                m_ui->dontScanDirLineEdit->setText(value);
                break;
            case 2  :
                checked == "checked" ? m_ui->onlyScanFileNameCheckBox->setChecked(true) : m_ui->onlyScanFileNameCheckBox->setChecked(false);
                m_ui->onlyScanFileNameLineEdit->setText(value);
                break;
            case 3  :
                checked == "checked" ? m_ui->onlyScanDirCheckBox->setChecked(true) : m_ui->onlyScanDirCheckBox->setChecked(false);
                m_ui->onlyScanDirLineEdit->setText(value);
                break;
            case 4  :
                m_ui->enablePUACheckBox->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                m_ui->PUAFrame->setEnabled(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 5  :
                m_ui->loadPUAPackedRadioButon->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 6  :
                m_ui->loadPUAPWToolRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 7  :
                m_ui->loadPUANetToolRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 8  :
                m_ui->loadPUAP2PRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 9  :
                m_ui->loadPUAIRCRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 10 :
                m_ui->loadPUARATRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 11 :
                m_ui->loadPUANetToolSpyRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 12 :
                m_ui->loadPUAServerRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 13 :
                m_ui->loadPUAScriptRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 14 :
                m_ui->loadPUAAndrRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 15 :
                m_ui->loadPUAJavaRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 16 :
                m_ui->loadPUAOsxRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 17 :
                m_ui->loadPUAToolRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 18 :
                m_ui->loadPUAUnixRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
            case 19 :
                m_ui->loadPUAWinRadioButton->setChecked(m_setupFile->getSectionBoolValue(section, inclExclKeywords.at(idx)));
                break;
        }
    }
    m_readSettingsInProgress = false;
}

void includeExcludeOptions::slot_enablePUACheckBoxClicked()
{
    m_ui->PUAFrame->setEnabled(m_ui->enablePUACheckBox->isChecked());
    slot_writeSettings();
}

void includeExcludeOptions::slot_highlightSettings()
{
    m_ui->dontScanFileNameCheckBox->isChecked() ? m_ui->frame01->setStyleSheet(css) : m_ui->frame01->setStyleSheet("");
    m_ui->dontScanDirCheckBox->isChecked() ? m_ui->frame02->setStyleSheet(css) : m_ui->frame02->setStyleSheet("");
    m_ui->onlyScanFileNameCheckBox->isChecked() ? m_ui->frame03->setStyleSheet(css) : m_ui->frame03->setStyleSheet("");
    m_ui->onlyScanDirCheckBox->isChecked() ? m_ui->frame04->setStyleSheet(css) : m_ui->frame04->setStyleSheet("");

    m_ui->loadPUAPackedRadioButon->isChecked() ? m_ui->loadPUAPackedRadioButon->setStyleSheet(css) : m_ui->loadPUAPackedRadioButon->setStyleSheet("");
    m_ui->loadPUAPWToolRadioButton->isChecked() ? m_ui->loadPUAPWToolRadioButton->setStyleSheet(css)
                                                : m_ui->loadPUAPWToolRadioButton->setStyleSheet("");
    m_ui->loadPUANetToolRadioButton->isChecked() ? m_ui->loadPUANetToolRadioButton->setStyleSheet(css)
                                                 : m_ui->loadPUANetToolRadioButton->setStyleSheet("");
    m_ui->loadPUAP2PRadioButton->isChecked() ? m_ui->loadPUAP2PRadioButton->setStyleSheet(css) : m_ui->loadPUAP2PRadioButton->setStyleSheet("");
    m_ui->loadPUAIRCRadioButton->isChecked() ? m_ui->loadPUAIRCRadioButton->setStyleSheet(css) : m_ui->loadPUAIRCRadioButton->setStyleSheet("");
    m_ui->loadPUARATRadioButton->isChecked() ? m_ui->loadPUARATRadioButton->setStyleSheet(css) : m_ui->loadPUARATRadioButton->setStyleSheet("");
    m_ui->loadPUANetToolSpyRadioButton->isChecked() ? m_ui->loadPUANetToolSpyRadioButton->setStyleSheet(css)
                                                    : m_ui->loadPUANetToolSpyRadioButton->setStyleSheet("");
    m_ui->loadPUAServerRadioButton->isChecked() ? m_ui->loadPUAServerRadioButton->setStyleSheet(css)
                                                : m_ui->loadPUAServerRadioButton->setStyleSheet("");
    m_ui->loadPUAScriptRadioButton->isChecked() ? m_ui->loadPUAScriptRadioButton->setStyleSheet(css)
                                                : m_ui->loadPUAScriptRadioButton->setStyleSheet("");
    m_ui->loadPUAAndrRadioButton->isChecked() ? m_ui->loadPUAAndrRadioButton->setStyleSheet(css) : m_ui->loadPUAAndrRadioButton->setStyleSheet("");
    m_ui->loadPUAJavaRadioButton->isChecked() ? m_ui->loadPUAJavaRadioButton->setStyleSheet(css) : m_ui->loadPUAJavaRadioButton->setStyleSheet("");
    m_ui->loadPUAOsxRadioButton->isChecked() ? m_ui->loadPUAOsxRadioButton->setStyleSheet(css) : m_ui->loadPUAOsxRadioButton->setStyleSheet("");
    m_ui->loadPUAToolRadioButton->isChecked() ? m_ui->loadPUAToolRadioButton->setStyleSheet(css) : m_ui->loadPUAToolRadioButton->setStyleSheet("");
    m_ui->loadPUAUnixRadioButton->isChecked() ? m_ui->loadPUAUnixRadioButton->setStyleSheet(css) : m_ui->loadPUAUnixRadioButton->setStyleSheet("");
    m_ui->loadPUAWinRadioButton->isChecked() ? m_ui->loadPUAWinRadioButton->setStyleSheet(css) : m_ui->loadPUAWinRadioButton->setStyleSheet("");
}
