/************************************************************************
 * Setup Tab of the applicatino
 ************************************************************************/
#include "setuptab.h"
#define css_red "background-color:red;color:white"
#define css_yellow "background-color:yellow;color:black"
#define css_green "background-color:green;color:yellow"
#define css_mono "background-color:#404040;color:white"

setupTab::setupTab(QWidget* parent, setupFileHandler* setupFile) : QWidget(parent), m_setupFile(setupFile)
{
    m_ui.setupUi(this);
    m_supressMessage = true;  // verhindert, dass bei der Initialisierung der Sprachauswahl die Warnmeldung kommt.

    m_monochrome = false;
    if (m_setupFile->keywordExists("Setup", "DisableLogHighlighter") == true)
        m_monochrome = m_setupFile->getSectionBoolValue("Setup", "DisableLogHighlighter");

    if (m_setupFile->keywordExists("Setup", "WindowState") == true)
    {
        if (m_setupFile->getSectionValue("Setup", "WindowState") == "minimized")
            m_ui.windowStateComboBox->setCurrentIndex(1);
        else
            m_ui.windowStateComboBox->setCurrentIndex(0);
    }

    if (m_setupFile->keywordExists("Clamd", "ClamdScanMultithreading") == true)
        m_ui.clamdscanComboBox->setCurrentIndex(m_setupFile->getSectionIntValue("Clamd", "ClamdScanMultithreading"));
    else
        m_setupFile->setSectionValue("Clamd", "ClamdScanMultithreading", 0);

    if (m_setupFile->keywordExists("Setup", "DisableLogHighlighter") == true)
        m_ui.logHighlighterCheckBox->setChecked(m_setupFile->getSectionBoolValue("Setup", "DisableLogHighlighter"));
    else
        m_setupFile->setSectionValue("Setup", "DisableLogHighlighter", false);

    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),SLOT(slot_requestFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("https://www.clamav.net/download")));

    eicarManager = new QNetworkAccessManager(this);
    connect(eicarManager,SIGNAL(finished(QNetworkReply*)),SLOT(slot_eicarRequestFinished(QNetworkReply*)));

    findTranslation();
    slot_updateSystemInfo();
    slot_filemanagerComboBoxChanged(0);
    m_supressMessage = false;
}

QString setupTab::checkmonochrome(QString color)
{
    QString rc = "";
    if (m_monochrome == true)
        rc = css_mono;
    else {
        if (color == "red")
            rc = css_red;
        if (color == "yellow")
            rc = css_yellow;
        if (color == "green")
            rc = css_green;
    }

    return rc;
}

void setupTab::slot_updateSystemInfo()
{
    QString systemInfo;
    if (m_setupFile->keywordExists("Clamd", "ClamdLocation") == true)
        m_ui.clamdPath->setText(m_setupFile->getSectionValue("Clamd", "ClamdLocation").replace("\n", ""));
    if (m_setupFile->keywordExists("Clamd", "ClamonaccLocation") == true)
        m_ui.clamonaccPath->setText(m_setupFile->getSectionValue("Clamd", "ClamonaccLocation").replace("\n", ""));
    if (m_setupFile->keywordExists("FreshclamSettings", "FreshclamLocation") == true)
        m_ui.freshclamPath->setText(m_setupFile->getSectionValue("FreshclamSettings", "FreshclamLocation").replace("\n", ""));

    if (m_setupFile->sectionExists("Updater") == true)
    {
        m_ui.databasePath->setText(m_setupFile->getSectionValue("Directories", "LoadSupportedDBFiles")
                                       .mid(m_setupFile->getSectionValue("Directories", "LoadSupportedDBFiles").indexOf("|") + 1));
        m_ui.databaseLastUpdate->setText(m_setupFile->getSectionValue("Updater", "LastUpdate"));
        m_ui.databaseMainFile->setText(m_setupFile->getSectionValue("Updater", "MainVersion"));
        m_ui.databaseDailyFile->setText(m_setupFile->getSectionValue("Updater", "DailyVersion"));
        m_ui.databaseBytecodeFile->setText(m_setupFile->getSectionValue("Updater", "BytecodeVersion"));
        m_ui.databasePath->setToolTip(m_ui.databasePath->text());
        m_ui.databaseLastUpdate->setToolTip(m_ui.databaseLastUpdate->text());
        m_ui.databaseMainFile->setToolTip(m_ui.databaseMainFile->text());
        m_ui.databaseDailyFile->setToolTip(m_ui.databaseDailyFile->text());
        m_ui.databaseBytecodeFile->setToolTip(m_ui.databaseBytecodeFile->text());
        systemInfo = getClamAVVersion();
        emit sendSystemInfo(systemInfo);
    }

    if (m_setupFile->keywordExists("Clamd", "ClamonaccPid") == true)
    {
        m_ui.clamonaccPID->setText(m_setupFile->getSectionValue("Clamd", "ClamonaccPid"));
        if (m_setupFile->getSectionValue("Clamd", "ClamonaccPid") == "n/a")
        {
            m_ui.clamonaccActivityLabel->setPixmap(QPixmap(":/icons/icons/gifs/activity.gif"));
            m_ui.clamonaccStatus->setText(m_setupFile->getSectionValue("Clamd", "Status2"));
            m_ui.clamonaccStatus->setStyleSheet(checkmonochrome("red"));
        }
        else {
            m_ui.clamonaccActivityLabel->setMovie(new QMovie(":/icons/icons/gifs/activity.gif"));
            m_ui.clamonaccActivityLabel->movie()->start();
            m_ui.clamonaccStatus->setText("is running");
            m_ui.clamonaccStatus->setStyleSheet(checkmonochrome("green"));
        }
    }

    if (m_setupFile->keywordExists("Clamd", "ClamdPid") == true)
    {
        m_ui.clamdPID->setText(m_setupFile->getSectionValue("Clamd", "ClamdPid"));
        if (m_setupFile->getSectionValue("Clamd", "ClamdPid") == "n/a")
        {
            m_ui.clamdActivityLabel->setPixmap(QPixmap(":/icons/icons/gifs/activity.gif"));
            QString message = m_setupFile->getSectionValue("Clamd", "Status");
            if ((message == "starting up ...") || (message == "shutting down ..."))
            {
                m_ui.clamdStatus->setStyleSheet(checkmonochrome("yellow"));
                m_ui.clamdStatus->setText(message);
                if (m_setupFile->getSectionValue("Clamd", "Status2") != "n/a")
                {
                    m_ui.clamonaccStatus->setStyleSheet(checkmonochrome("yellow"));
                    m_ui.clamonaccStatus->setText(message);
                }
            }
            if (message == "is running")
            {
                m_ui.clamdStatus->setStyleSheet(checkmonochrome("green"));
                m_ui.clamdStatus->setText(message);
                if (m_setupFile->getSectionValue("Clamd", "Status2") != "is running")
                {
                    m_ui.clamonaccStatus->setStyleSheet(checkmonochrome("green"));
                    m_ui.clamonaccStatus->setText(message);
                }
            }
            if ((message == "shut down") || (message == "not running"))
            {
                m_ui.clamdStatus->setStyleSheet(checkmonochrome("red"));
                m_ui.clamdStatus->setText("is down");
                m_ui.clamonaccStatus->setStyleSheet(checkmonochrome("red"));
                m_ui.clamonaccStatus->setText("is down");
            }
        }
        else {
            m_ui.clamdActivityLabel->setMovie(new QMovie(":/icons/icons/gifs/activity.gif"));
            m_ui.clamdActivityLabel->movie()->start();
            m_ui.clamdStatus->setText("is running");
            m_ui.clamdStatus->setStyleSheet(checkmonochrome("green"));
        }
    }

    if (m_setupFile->keywordExists("Freshclam", "Pid") == true)
    {
        m_ui.freshclamPID->setText(m_setupFile->getSectionValue("Freshclam", "Pid"));
        if (m_setupFile->getSectionValue("Freshclam", "Pid") == "n/a")
        {
            m_ui.freshclamActivityLabel->setPixmap(QPixmap(":/icons/icons/gifs/activity.gif"));
            m_ui.freshclamStatus->setText("is down");
            m_ui.freshclamStatus->setStyleSheet(checkmonochrome("red"));
        }
        else {
            m_ui.freshclamActivityLabel->setMovie(new QMovie(":/icons/icons/gifs/activity.gif"));
            m_ui.freshclamActivityLabel->movie()->start();
            m_ui.freshclamStatus->setText("is running");
            m_ui.freshclamStatus->setStyleSheet(checkmonochrome("green"));
        }
    }
}

void setupTab::slot_clamdButtonClicked()
{
    emit switchActiveTab(6);
}

void setupTab::slot_freshclamButtonClicked()
{
    emit switchActiveTab(5);
}

void setupTab::slot_clamdscanComboBoxClicked()
{
    m_setupFile->setSectionValue("Clamd", "ClamdScanMultithreading", m_ui.clamdscanComboBox->currentIndex());
}

void setupTab::slot_logHightlighterCheckBoxClicked()
{
    m_setupFile->setSectionValue("Setup", "DisableLogHighlighter", m_ui.logHighlighterCheckBox->isChecked());
    emit logHighlightingChanged(m_ui.logHighlighterCheckBox->isChecked());
    m_monochrome = m_ui.logHighlighterCheckBox->isChecked();
    slot_updateSystemInfo();
}

void setupTab::slot_requestFinished(QNetworkReply * reply)
{
    int pos, len, ltsCount = 0;
    QString ltsVersions = "n/a";
    QString version = m_setupFile->getSectionValue("Updater","Version").trimmed().replace("Scanner ","");
    if (version.indexOf("ClamAV") != -1) version = version.replace("ClamAV","");
    m_ui.clamavInstalled->setText(version);
    m_setupFile->setSectionValue("Updater","Version",version);

    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        QString replyString = reply->readAll();
        QStringList lines = replyString.split("\n");
        foreach(QString line, lines)
        {
            if (line.indexOf("<h3>") != -1)
            {
                pos = line.indexOf("<strong>") + 8;
                len = line.indexOf("</strong>") - pos;
                line = line.mid(pos,len);
                m_ui.clamavLatest->setText(line);
            }
            if ((line.indexOf("<h4>") != -1) && (line.indexOf("LTS") != -1))
            {
                pos = line.indexOf("<h4>") + 4;
                len = line.indexOf("<span") - pos;
                line = line.mid(pos,len);
                if (ltsCount == 0)
                {
                    ltsVersions = "(" + line + ")";
                    ltsCount++;
                }
                else {
                    ltsVersions = ltsVersions + " ,(" + line + ")";
                }
            }
        }
        m_ui.clamavLTS1->setText(ltsVersions);
        if (m_ui.clamavInstalled->text() == m_ui.clamavLatest->text()) m_ui.clamavStatus->setText(tr("OK")); else m_ui.clamavStatus->setText("update");
    }

    reply->deleteLater();
}

void setupTab::slot_eicarRequestFinished(QNetworkReply *reply)
{
    if(reply->error())
    {
        QMessageBox::information(this,"ERROR",reply->errorString());
    }
    else
    {
        QStringList parameters;
        QString replyString = reply->readAll();
        QFile file(QDir::homePath() + "/.cache/eicartest/eicar.com.txt");

        if (file.open(QIODevice::Text|QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << replyString;
            file.close();
        }

        assembleScanParameters(m_setupFile,&parameters);

        parameters << QDir::homePath() + "/.cache/eicartest/eicar.com.txt";

        scheduleScanObject * scanObject = new scheduleScanObject(this,"Eicar Test",parameters);
        connect(scanObject,SIGNAL(sendStatusReport(int,QString,QString)),this,SLOT(slot_eicarTestStatusReport(int,QString,QString)));
        scanObject->setWindowTitle("EICAR Test");
        scanObject->setWindowIcon(QIcon(":/icons/icons/media.png"));
        scanObject->setModal(true);
        scanObject->exec();
        delete scanObject;
    }
}

void setupTab::slot_addRemoveFilemanagerIntegrationButtonClicked()
{
    switch (m_ui.filemanagerComboBox->currentIndex())
    {
        case 0  :   if (serviceMenuConfigPresent("dolphin") == false)
                        addServiceMenuDolphin();
                    else
                        removeServiceMenuDolphin();
                    slot_filemanagerComboBoxChanged(0);
            break;
        case 1  :   if (serviceMenuConfigPresent("nemo") == false)
                        addServiceMenuNemo();
                    else
                        removeServiceMenuNemo();
                    slot_filemanagerComboBoxChanged(1);
            break;
        case 2  :   if (serviceMenuConfigPresent("gnome-commander") == false)
                        addServiceMenuGnomeCommander();
                    else
                        removeServiceMenuGnomeCommander();
                    slot_filemanagerComboBoxChanged(2);
            break;
    }
}

void setupTab::slot_filemanagerComboBoxChanged(int value)
{
    QString labelText = "";
    QIcon addIcon(":/icons/icons/add.png");
    QIcon delIcon(":/icons/icons/trash-can.png");

    switch (value)
    {
        case 0  :   serviceMenuConfigPresent("dolphin") == true?labelText = "remove":labelText = "add";
            break;
        case 1  : serviceMenuConfigPresent("nemo") == true?labelText = "remove":labelText = "add";
            break;
        case 2  : serviceMenuConfigPresent("gnome-commander") == true?labelText = "remove":labelText = "add";
            break;
    }

    m_ui.addIntegrationPushButton->setText(tr(QString(labelText).toLocal8Bit()));
    labelText == "add"?m_ui.addIntegrationPushButton->setIcon(addIcon):m_ui.addIntegrationPushButton->setIcon(delIcon);

}

void setupTab::slot_startEicarTest()
{
    QDir eicarTestDir(QDir::homePath() + "/.cache/eicartest");
    eicarTestDir.mkpath(QDir::homePath() + "/.cache/eicartest");

    eicarManager->get(QNetworkRequest(QUrl("https://secure.eicar.org/eicar.com.txt")));
}

void setupTab::slot_eicarTestStatusReport(int rc, QString text1, QString text2)
{
    Q_UNUSED(text1);
    Q_UNUSED(text2);

    if (QFileInfo::exists(QDir::homePath() + "/.cache/eicartest/eicar.com.txt"))
    {
        QFile eraseFile(QDir::homePath() + "/.cache/eicartest/eicar.com.txt");
        eraseFile.remove();
    }

    if (rc == 2)
    {
        QMessageBox::information(this,"EICAR-TEST",tr("Eicar-Test finished successfully!"));
        m_ui.eicarTestResultButton->setIcon(QIcon(":/icons/icons/create.png"));
    }
    else {
        if (rc == 1)
        {
            QMessageBox::warning(this,"EICAR-TEST",tr("Eica-Test finished with an error!\nThe test was interrupted by a user action."));
            m_ui.eicarTestResultButton->setIcon(QIcon(":/icons/icons/cancel.png"));
        }
        else {
            QMessageBox::warning(this,"EICAR-TEST",tr("Eica-Test finished with an error!"));
            m_ui.eicarTestResultButton->setIcon(QIcon(":/icons/icons/cancel.png"));
        }
    }
}

void setupTab::findTranslation()
{
    int index = -1;
    QString langhelper;
    QString m_country = "";
    QString translation_path;

    translation_path = QCoreApplication::applicationDirPath() + "/../share/clamav-gui/";
    if (isRunninginFlatPak())
        translation_path = "/app/usr/share/clamav-gui/";
    if (isRunninginAppImage())
        translation_path = "/usr/share/clamav-gui/";
    QDir directory(translation_path);
    QStringList m_filelist = directory.entryList(QDir::Files);
    foreach(QString m_file, m_filelist)
    {
        if (m_file.indexOf(".qm") != -1 && m_file.contains("gui"))
        {
            QString m_lang = m_file.mid(11,5);
            QLocale locale(m_lang);

#if (QT_VERSION >= QT_VERSION_CHECK(6, 2, 0))
            m_country = locale.territoryToString(locale.territory());
#else
            m_country = locale.countryToString(locale.country());
#endif

            m_ui.languageSelectComboBox->addItem(QIcon(translation_path + "languageicons/" + m_lang + ".png"),"[" + m_lang + "] " + m_country);        
        }
    }

    if (m_setupFile->keywordExists("Setup", "language") == true)
    {
        langhelper = m_setupFile->getSectionValue("Setup", "language");
        index = m_ui.languageSelectComboBox->findText(langhelper, Qt::MatchContains);
        if (index == -1)
            index = m_ui.languageSelectComboBox->findText("[en_GB]", Qt::MatchContains);
        m_ui.languageSelectComboBox->setCurrentIndex(index);
    }
    else {
        QString lang = QLocale::system().name();
        index = m_ui.languageSelectComboBox->findText("[" + lang + "]", Qt::MatchContains);
        if (index == -1)
            index = m_ui.languageSelectComboBox->findText("[en_GB]", Qt::MatchContains);
        m_ui.languageSelectComboBox->setCurrentIndex(index);
    }
}

void setupTab::slot_clamonaccButtonClicked()
{
    emit switchActiveTab(6);
}

void setupTab::slot_selectedLanguageChanged()
{
    m_setupFile->setSectionValue("Setup", "language", m_ui.languageSelectComboBox->currentText().mid(0, 7));
    if (m_supressMessage == false)
        QMessageBox::information(this, tr("Warning"), tr("You have to restart the application for changes to take effect!"));
}

void setupTab::slot_basicSettingsChanged()
{
    if (m_ui.windowStateComboBox->currentIndex() == 0)
        m_setupFile->setSectionValue("Setup", "WindowState", "maximized");
    if (m_ui.windowStateComboBox->currentIndex() == 1)
        m_setupFile->setSectionValue("Setup", "WindowState", "minimized");
}
