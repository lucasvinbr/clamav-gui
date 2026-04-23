#include "profilemanager.h"
#include "ui_profilemanager.h"
#include "sharedvars.cpp"

ProfileManager::ProfileManager(QWidget* parent, setupFileHandler* setupFile) : QWidget(parent), m_setupFile(setupFile), m_ui(new Ui::ProfileManager)
{
    // m_setupFile = new setupFileHandler(QDir::homePath() + "/.clamav-gui/settings.ini", this); --> uses the setupFileHandler provided by the clamav_gui class
    m_ui->setupUi(this);
    getProfileList();
    slot_readProfileSettings();
    checkMonochromeSettings();
}

ProfileManager::~ProfileManager()
{
    delete m_ui;
}

void ProfileManager::getProfileList()
{
    QStringList profiles = m_setupFile->getKeywords("Profiles");
    QStringList selectableProfiles;
    setupFileHandler sf(this);

    foreach (QString profile, profiles)
    {
        sf.setSetupFileName(QDir::homePath() + "/.clamav-gui/profiles/" + profile + ".ini");
        if (sf.getSectionValue(profile, "Directories") != "")
            selectableProfiles << profile;
    }

    m_ui->profileComboBox->clear();
    m_ui->profileComboBox->addItems(profiles);
}

void ProfileManager::checkMonochromeSettings()
{
    if (m_setupFile->getSectionBoolValue("Setup", "DisableLogHighlighter") == true)
    {
        m_ui->targetsLabel->setStyleSheet("background-color:#404040;color:white;padding:3px;border-radius:3px");
        m_ui->filenameLabel->setStyleSheet("background-color:#404040;color:white;padding:3px;border-radius:3px");
        m_ui->optionsLabel->setStyleSheet("background-color:#404040;color:white;padding:3px;border-radius:3px");
    }
    else {
        m_ui->targetsLabel->setStyleSheet("background-color:#c0c0c0;color:black;padding:3px;border-radius:3px");
        m_ui->filenameLabel->setStyleSheet("background-color:#c0c0c0;color:black;padding:3px;border-radius:3px");
        m_ui->optionsLabel->setStyleSheet("background-color:#c0c0c0;color:black;padding:3px;border-radius:3px");
    }
}

void ProfileManager::slot_readProfileSettings()
{
    QString profileName = m_ui->profileComboBox->currentText();
    if (profileName == "")
        return;

    setupFileHandler* tempSetupFile = new setupFileHandler(QDir::homePath() + "/.clamav-gui/profiles/" + profileName + ".ini", this);
    QStringList targets;
    QString targetLabel;
    QStringList options;
    QString optionLabel;
    QString logFile = tempSetupFile->getSectionValue("Directories", "ScanReportToFile");

    targets = tempSetupFile->getSectionValue(profileName, "Directories").split('\n');
    options = tempSetupFile->getKeywords("SelectedOptions");

    if ((targets[0] != "") & (targets.count() > 0))
        targetLabel = targetLabel + targets[0];
    for (int i = 1; i < targets.count(); i++)
    {
        if ((targets[i] != "") & (targetLabel != ""))
        {
            targetLabel = targetLabel + "\n" + targets[i];
        }
        else {
            if (targets[i] != "")
                targetLabel = targets[i];
        }
    }

    m_ui->targetsListLabel->setText(targetLabel);

    if (options.count() > 0)
        optionLabel = optionLabel + options[0];
    for (int i = 1; i < options.count(); i++)
    {
        optionLabel = optionLabel + "\n" + options[i];
    }

    for (int idx = 0; idx < inclExclKeywords.size(); idx ++)
    {
        if (tempSetupFile->keywordExists("REGEXP_and_IncludeExclude", inclExclKeywords.at(idx)))
        {
            if (idx < 4)
            {
                if ((tempSetupFile->getSectionValue("REGEXP_and_IncludeExclude", "DontScanFileNamesMatchingRegExp") != "") &&
                    (tempSetupFile->getSectionValue("REGEXP_and_IncludeExclude", "DontScanFileNamesMatchingRegExp").indexOf("not checked") == -1))
                {
                    optionLabel = optionLabel + "\n" + inclExclKeywords.at(idx) + "=" +
                                  tempSetupFile->getSectionValue("REGEXP_and_IncludeExclude", inclExclKeywords.at(idx))
                                      .mid(tempSetupFile->getSectionValue("REGEXP_and_IncludeExclude", inclExclKeywords.at(idx)).indexOf("|") + 1);
                }
            }
            else {
                if (tempSetupFile->getSectionBoolValue("REGEXP_and_IncludeExclude", "EnablePUAOptions") == true)
                {
                    if ((tempSetupFile->getSectionBoolValue("REGEXP_and_IncludeExclude", inclExclKeywords.at(idx)) == true) &&
                        (inclExclKeywords.at(idx) != "EnablePUAOptions"))
                    optionLabel = optionLabel + "\ninclude-pua=" + inclExclSwitches.at(idx);
                }
            }
        }
    }

    // Scan Limitations
    QString value = "";
    for (int idx = 0; idx < scanLimitKeywords.size(); idx++)
    {
        value = tempSetupFile->getSectionValue("ScanLimitations", scanLimitKeywords.at(idx));
        if ((value != "") && (value.indexOf("not checked") == -1))
            optionLabel = optionLabel + "\n" + scanLimitSwitches.at(idx) + "=" + value.mid(value.indexOf("|") + 1);
    }

    if (tempSetupFile->getSectionBoolValue(profileName, "Recursion") == true)
    {
        if (optionLabel != "")
        {
            optionLabel = optionLabel + "\n" + "-r";
        }
        else {
            optionLabel = "-r";
        }
    }

    optionLabel = optionLabel.replace("<equal>", "=");
    m_ui->optionsListLabel->setText(optionLabel);

    if (logFile.left(logFile.indexOf("|")) == "checked")
    {
        logFile = logFile.mid(logFile.indexOf("|") + 1);
    }
    else {
        logFile = "";
    }

    m_ui->filenameTextLabel->setText(logFile);

    delete tempSetupFile;
}

void ProfileManager::slot_addProfileButtonClicked()
{

    m_profileWizard = new ProfileWizardDialog(this);
    connect(m_profileWizard, SIGNAL(signal_profileSaved()), this, SLOT(slot_profileSaved()));
    m_profileWizard->setModal(true);
    m_profileWizard->show();
    slot_readProfileSettings();
}

void ProfileManager::slot_editProfileButtonClicked()
{
    QString profileName = m_ui->profileComboBox->currentText();

    if (profileName != "")
    {
        m_profileWizard = new ProfileWizardDialog(this, profileName);
        connect(m_profileWizard, SIGNAL(signal_profileSaved()), this, SLOT(slot_profileSaved()));
        m_profileWizard->setModal(true);
        m_profileWizard->show();
        slot_readProfileSettings();
    }
}

void ProfileManager::slot_eraseProfileButtonClicked()
{
    QString profileName = m_ui->profileComboBox->currentText();
    QStringList scanJobs = m_setupFile->getKeywords("ScanJobs");
    QString line;
    QString logfileName;
    bool found = false;

    if (profileName != "")
    {
        foreach (QString scanJob, scanJobs)
        {
            line = m_setupFile->getSectionValue("ScanJobs", scanJob);
            if (line.indexOf("|" + profileName + "|") != -1)
                found = true;
        }
        if (found == false)
        {
            int rc = QMessageBox::question(this, tr("WARNING"), tr("Do you realy want to remove this (") + profileName + tr(") profile"),
                                           QMessageBox::Yes, QMessageBox::No);
            QFile tempFile(QDir::homePath() + "/.clamav-gui/profiles/" + m_ui->profileComboBox->currentText() + ".ini");
            if (rc == QMessageBox::Yes)
            {
                setupFileHandler* sf = new setupFileHandler(QDir::homePath() + "/.clamav-gui/profiles/" + m_ui->profileComboBox->currentText() + ".ini", this);
                logfileName = sf->getSectionValue("Directories", "ScanReportToFile")
                                  .mid(sf->getSectionValue("Directories", "ScanReportToFile").indexOf("|") + 1);
                if (logfileName != "")
                {
                    if (QMessageBox::question(this, tr("Info"),
                                              tr("There is a log-file associated with this profile. Shall I remove the log-file as well?"),
                                              QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
                    {
                        QFile fileRemover(logfileName);
                        fileRemover.remove();
                    }
                }
                m_setupFile->removeKeyword("Profiles", m_ui->profileComboBox->currentText());
                tempFile.remove();
                QMessageBox::information(this, tr("Info"), tr("Profile \"") + m_ui->profileComboBox->currentText() + tr("\" removed"));
                getProfileList();
                slot_readProfileSettings();
                emit triggerProfilesChanged();
                delete sf;
            }
        }
        else {
            QMessageBox::information(this, tr("ERROR"), tr("Profile can not be removed because it is in use by the scheduler!"));
        }
    }
}

void ProfileManager::slot_profileSaved()
{
    emit triggerProfilesChanged();
    getProfileList();
}

void ProfileManager::monochromeModeChanged(bool state)
{
    Q_UNUSED(state)
    checkMonochromeSettings();
}
