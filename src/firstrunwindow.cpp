#include "firstrunwindow.h"
#include "ui_firstrunwindow.h"

firstRunWindow::firstRunWindow(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::firstRunWindow)
{
    m_ui->setupUi(this);
    this->setWindowTitle("ClamAV-GUI Basic Settings");

    m_processInit = true;

    createServiceMenu();
    createBaseDirStructur();

    m_setupFile = new setupFileHandler(QDir::homePath() + "/.clamav-gui/settings.ini");
    m_setupFile->setSectionValue("Setup","FirstRun",true);
    createInitialSettings();
    createClamdConfFile();
    m_delayTimer = new QTimer(this);
    m_delayTimer->setSingleShot(true);
    connect(m_delayTimer,SIGNAL(timeout()),this,SLOT(slot_findRequiredApplications()));
    m_delayTimer->start(500);
    findTranslation();

    m_processInit = false;
}

firstRunWindow::~firstRunWindow()
{
    delete m_setupFile;
    delete m_ui;
}

void firstRunWindow::slot_findRequiredApplications()
{
    m_initCommands << "whereis" << "whereis" << "whereis" << "whereis" << "whereis" << "whereis" << "whereis" << "whoami" << "groups" << "man";
    m_initParameters  << "clamd" << "freshclam"<< "clamonacc" << "clamscan" << "clamdscan" << "pkexec" << "kdesu" << "" << "" << "clamd.conf";
    m_initIndex = 0;

    m_initProcess = new QProcess(this);
    connect(m_initProcess,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(slot_initProcessFinished()));

    m_processParameters.clear();
    m_processParameters << m_initParameters.at(m_initIndex);
    m_initProcess->start(m_initCommands.at(m_initIndex),m_processParameters);
}

void firstRunWindow::slot_monochromeModeChanged()
{
    m_setupFile->setSectionValue("Setup", "DisableLogHighlighter", m_ui->monochromeModeCheckBox->isChecked());
}

void firstRunWindow::slot_startupModeChanged()
{
    if (m_ui->startupModeComboBox->currentIndex() == 0)
        m_setupFile->setSectionValue("Setup", "WindowState", "maximized");
    if (m_ui->startupModeComboBox->currentIndex() == 1)
        m_setupFile->setSectionValue("Setup", "WindowState", "minimized");
}

void firstRunWindow::slot_clamdscanChanged()
{
    m_setupFile->setSectionValue("Clamd","ClamdScanMultithreading",m_ui->clamdscanComboBox->currentIndex());
}

void firstRunWindow::findTranslation()
{
    int index = -1;
    QString m_country = "";
    QString translation_path = QCoreApplication::applicationDirPath() + "/../share/clamav-gui/";
    //QString translation_path = "/usr/share/clamav-gui/"; for testing ...
    QDir directory(translation_path);
    QStringList m_filelist = directory.entryList(QDir::Files);
    foreach(QString m_file, m_filelist) {
        if (m_file.indexOf(".qm") != -1 && m_file.contains("gui")) {
            QString m_lang = m_file.mid(11,5);
            QLocale locale(m_lang);

#if (QT_VERSION >= QT_VERSION_CHECK(6, 2, 0))
            m_country = locale.territoryToString(locale.territory());
#else
            m_country = locale.countryToString(locale.country());
#endif

            m_ui->applicationLanguageComboBox->addItem(QIcon(translation_path + "languageicons/" + m_lang + ".png"),"[" + m_lang + "] " + m_country);
        }
    }

    QString lang = QLocale::system().name();
    index = m_ui->applicationLanguageComboBox->findText("[" + lang + "]", Qt::MatchContains);
    if (index == -1)
        index = m_ui->applicationLanguageComboBox->findText("[en_GB]", Qt::MatchContains);
    m_ui->applicationLanguageComboBox->setCurrentIndex(index);
 }

void firstRunWindow::slot_initProcessFinished()
{
    QString rc = m_initProcess->readAll().trimmed();
    QStringList elements = rc.split(" ");

    switch (m_initIndex) {
        case 0 :
            if (elements.count() == 3) {
                m_ui->clamdSourceLabel->setText(elements.at(1));
                m_ui->clamdStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
                m_setupFile->setSectionValue("Clamd","ClamdLocation",elements.at(1));
                m_setupFile->setSectionValue("Clamd","StartClamdOnStartup",false);
            }
            break;
        case 1 :
            if (elements.count() == 3) {
                m_ui->freshclamSourceLabel->setText(elements.at(1));
                m_ui->freshclamStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
                m_setupFile->setSectionValue("FreshclamSettings","FreshclamLocation",elements.at(1));
            }
            break;
        case 2 :
            if (elements.count() == 3) {
                m_ui->clamonaccSourceLabel->setText(elements.at(1));
                m_ui->clamonaccStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
                m_setupFile->setSectionValue("Clamd","ClamonaccLocation",elements.at(1));
            }
            break;
        case 3 :
            if (elements.count() == 3) {
                m_ui->clamscanSourceLabel->setText(elements.at(1));
                m_ui->clamscanStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
            }
            break;
        case 4 :
            if (elements.count() == 3) {
                m_ui->clamdscanSourceLabel->setText(elements.at(1));
                m_ui->clamdscanStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
            }
            break;
        case 5 :
            if (elements.count() == 3) {
                m_ui->sudoGUISourceLabel->setText(elements.at(1));
                m_ui->sudoGUIStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
                m_initIndex = 6;
            }
            break;
        case 6 :
            if (elements.count() == 3) {
                m_ui->sudoGUISourceLabel->setText(elements.at(1));
                m_ui->sudoGUIStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
            }
            break;
        case 7 :
            if (rc != "") {
                m_ui->applicationUserLabel->setText("Application User : " + elements.at(0));
                m_ui->applicationUserStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
            }
            break;
        case 8 :
            if (elements.count() > 0) {
                m_ui->applicationGroupLabel->setText("Application Group : " + elements.at(0));
                m_ui->applicationGroupStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
            }
            break;
        case 9 :
            QFile file(QDir::homePath() + "/.clamav-gui/clamd.conf.man");
            if (file.open(QIODevice::WriteOnly|QIODevice::Text)) {
                QTextStream stream(&file);
                stream << rc;
                Qt::endl(stream);
                file.close();
            }
            break;
    }

    if (m_initIndex < m_initCommands.size()-1) {
        switch (m_initIndex) {
            case 0:
                m_setupFile->setSectionValue("FreshclamSettings", "FreshclamLocation", elements.at(1));
                break;
            case 1:
            case 2:
                break;
            case 3:
                if (rc == "") {
                    QMessageBox::warning(this, "ERROR", "Clamav is missing. Please install!", QMessageBox::Ok);
                    emit quitApplication();
                }
                break;
            case 4:
                break;
            case 5:
            case 6:
                if (elements.count() == 3) {
                    m_setupFile->setSectionValue("RequiredApplications",m_initParameters.at(m_initIndex),elements.at(1));
                    m_setupFile->setSectionValue("Settings","SudoGUI",elements.at(1));
                } else {
                    m_setupFile->setSectionValue("RequiredApplications",m_initParameters.at(m_initIndex),"n/a");
                    m_setupFile->setSectionValue("Settings","SudoGUI","n/a");
                }
                break;
            case 7:
            case 8:
                m_setupFile->setSectionValue("RequiredApplications","Group",m_ui->applicationGroupLabel->text());
                break;
            case 9:
                m_setupFile->setSectionValue("RequiredApplication","User",m_ui->applicationUserLabel->text());
                break;
        }

        m_initIndex++;
        m_processParameters.clear();
        if (m_initParameters.at(m_initIndex) != "") {
            m_processParameters << m_initParameters.at(m_initIndex);
            m_initProcess->start(m_initCommands.at(m_initIndex),m_processParameters);
        } else {
            m_processParameters << m_initParameters.at(m_initIndex);
            m_initProcess->start(m_initCommands.at(m_initIndex),QStringList());
        }
    } else {

    }
}

void firstRunWindow::slot_sddComboBoxChanged()
{
    if (m_processInit == false) {
        setupFileHandler * m_clamdConf = new setupFileHandler(QDir::homePath() + "/.clamav-gui/clamd.conf");
        setupFileHandler * m_freshclamConf = new setupFileHandler(QDir::homePath() + "/.clamav-gui/freshclam.conf");
        if (m_ui->signatureDatabaseDirectoryComboBox->currentText() == QDir::homePath() + "/.clamav-gui/signatures") {
            m_setupFile->setSectionValue("Directories", "LoadSupportedDBFiles", "checked|" + QDir::homePath() + "/.clamav-gui/signatures");
            m_setupFile->setSectionValue("FreshClam","runasroot",false);
            m_clamdConf->setSingleLineValue("DatabaseDirectory",QDir::homePath() + "/.clamav-gui/signatures");
            m_freshclamConf->setSingleLineValue("DatabaseDirectory", QDir::homePath() + "/.clamav-gui/signatures");
        } else  {
            m_setupFile->setSectionValue("Directories", "LoadSupportedDBFiles", "checked|" + m_ui->signatureDatabaseDirectoryComboBox->currentText());
            m_setupFile->setSectionValue("FreshClam","runasroot",true);
            m_clamdConf->setSingleLineValue("DatabaseDirectory",m_ui->signatureDatabaseDirectoryComboBox->currentText());
            m_freshclamConf->setSingleLineValue("DatabaseDirectory",m_ui->signatureDatabaseDirectoryComboBox->currentText());
        }
        emit settingChanged();
        delete m_clamdConf;
        delete m_freshclamConf;
    }
}

void firstRunWindow::slot_languageChanged()
{
    m_setupFile->setSectionValue("Setup", "language", m_ui->applicationLanguageComboBox->currentText().mid(0, 7));
}

void firstRunWindow::slot_done()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void firstRunWindow::createBaseDirStructur()
{
    //*****************************************************************************
    //creating service Menu
    //*****************************************************************************
    QDir dir(QDir::homePath());
    dir.mkpath(QDir::homePath() + "/.clamav-gui");
    dir.mkpath(QDir::homePath() + "/.clamav-gui/logs");
    dir.mkpath(QDir::homePath() + "/.clamav-gui/profiles");
    dir.mkpath(QDir::homePath() + "/.clamav-gui/quarantine");
    dir.mkpath(QDir::homePath() + "/.clamav-gui/signatures");
    QFile::setPermissions(QDir::homePath() + "/.clamav-gui/signatures",
                          QFileDevice::ReadOwner  | QFileDevice::ReadUser  | QFileDevice::ReadGroup  | QFileDevice::ReadOther  |
                          QFileDevice::WriteOwner | QFileDevice::WriteUser | QFileDevice::WriteGroup | QFileDevice::WriteOther |
                          QFileDevice::ExeOwner   | QFileDevice::ExeUser   | QFileDevice::ExeGroup   | QFileDevice::ExeOther);
    //_____________________________________________________________________________________________________________________________________
    // For UALinux
    // If the settings.ini in the home folder of the user is not present a predefined version is been copied into the folder.
    //_____________________________________________________________________________________________________________________________________
    if ((!QFileInfo::exists(QDir::homePath() + "/.clamav-gui/settings.ini")) && (!QFile::exists(QDir::homePath() + "/.clamav-gui/settings.ini"))) {
        dir.mkdir(QDir::homePath() + "/.clamav-gui");

        if (QFile::exists("/etc/clamav-gui/settings.ini"))
            QFile::copy("/etc/clamav-gui/settings.ini", QDir::homePath() + "/.clamav-gui/settings.ini");
    }
    //______________________________________________________________________________________________________________________________________

    m_ui->initialDirectoryStructureStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
}

void firstRunWindow::createServiceMenu()
{
    //*****************************************************************************
    //creating service Menu
    //*****************************************************************************
    QString serviceMenuPath;
    if (QFileInfo::exists(QDir::homePath() + "/.local/share/kservices5/ServiceMenus"))
        serviceMenuPath = QDir::homePath() + "/.local/share/kservices5/ServiceMenus";

    if (serviceMenuPath.isEmpty() && QFileInfo::exists(QDir::homePath() + "/.local/share/kio/servicemenus"))
        serviceMenuPath = QDir::homePath() + "/.local/share/kio/servicemenus";

    if (serviceMenuPath.isEmpty())
        serviceMenuPath = serviceMenuPath = QDir::homePath() + "/.local/share/kservices5/ServiceMenus";

    if (!QFileInfo::exists(serviceMenuPath + "/scanWithClamAV-GUI.desktop")) {
        if (!QFileInfo::exists(serviceMenuPath)) {
            QDir dir(serviceMenuPath);
            dir.mkpath(serviceMenuPath);
        }
        setupFileHandler* serviceFile = new setupFileHandler(serviceMenuPath + "/scanWithClamAV-GUI.desktop", this);
        serviceFile->setSectionValue("Desktop Entry", "Type", "Service");
        serviceFile->setSectionValue("Desktop Entry", "ServiceTypes", "KonqPopupMenu/Plugin");
        serviceFile->setSectionValue("Desktop Entry", "MimeType", "all/all;");
        serviceFile->setSectionValue("Desktop Entry", "Actions", "scan;");
        serviceFile->setSectionValue("Desktop Entry", "Icon", "clamav-gui");
        serviceFile->setSectionValue("Desktop Entry", "X-KDE-Priority", "TopLevel");
        serviceFile->setSectionValue("Desktop Entry", "X-KDE-StartupNotify", "false");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu", "Scan with ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[de]", "Scannen mit ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[da_DK]", "Scannen med ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[es_ES]", "Analizar con ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[us]", "Scan with ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[gb]", "Scan with ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[pt]", "Investigar com ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[br]", "Investigar com ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[pt_BR]", "Investigar com ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[fr]", "Scanner avec ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[it]", "Scansione con ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Entry", "NO-X-KDE-Submenu[uk]", "Сканування за допомогою ClamAV-GUI");

        serviceFile->setSectionValue("Desktop Action scan", "Name", "scan");
        serviceFile->setSectionValue("Desktop Action scan", "Name[de]", "Scannen mit ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Action scan", "Name[es_ES]", "Analizar con ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Action scan", "Name[us]", "Scan with ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Action scan", "Name[gb]", "Scan with ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Action scan", "Name[pt]", "Investigar com ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Action scan", "Name[br]", "Investigar com ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Action scan", "Name[fr]", "Scanner avec ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Action scan", "Name[it]", "Scansione con ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Action scan", "Name[uk]", "Сканування за допомогою ClamAV-GUI");
        serviceFile->setSectionValue("Desktop Action scan", "Icon", "clamav-gui");
        serviceFile->setSectionValue("Desktop Action scan", "Exec", "clamav-gui --scan %F");
        delete serviceFile;
    }
    //*****************************************************************************

    m_ui->dolphinContestMenuStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
}

void firstRunWindow::createInitialSettings()
{
    if ((QFileInfo::exists("/var/lib/clamav")) && (QFile::exists("/var/lib/clamav/freshclam.dat"))) {
        if (m_setupFile->keywordExists("Directories","LoadSupportedDBFiles") == false)
            m_setupFile->setSectionValue("Directories", "LoadSupportedDBFiles", "checked|/var/lib/clamav");

        if (m_setupFile->keywordExists("FreshClam","runasroot") == false)
            m_setupFile->setSectionValue("FreshClam","runasroot",true);

        m_ui->signatureDatabaseDirectoryComboBox->addItem("/var/lib/clamav");
        m_ui->signatureDatabaseDirectoryComboBox->addItem(QDir::homePath() + "/.clamav-gui/signatures");
    }
    else {
        if (m_setupFile->keywordExists("Directories","LoadSupportedDBFiles") == false)
            m_setupFile->setSectionValue("Directories", "LoadSupportedDBFiles", "checked|" + QDir::homePath() + "/.clamav-gui/signatures");

        m_setupFile->setSectionValue("FreshClam","runasroot",false);
        if (m_setupFile->keywordExists("FreshClam","runasroot") == false)

            m_ui->signatureDatabaseDirectoryComboBox->addItem("/.clamav-gui/signatures");
    }
    if (m_setupFile->keywordExists("Directories", "TmpFile") == false)
        m_setupFile->setSectionValue("Directories", "TmpFile", "checked|/tmp");

    if (m_setupFile->keywordExists("Directories", "ScanReportToFile") == false)
        m_setupFile->setSectionValue("Directories", "ScanReportToFile", "checked|" + QDir::homePath() + "/.clamav-gui/logs/report-scan.log");

    if (m_setupFile->keywordExists("Directories", "MoveInfectedFiles") == false)
        m_setupFile->setSectionValue("Directories", "MoveInfectedFiles", "not checked|" + QDir::homePath() + "/.clamav-gui/quarantine");

    if (m_setupFile->keywordExists("Directories", "CopyInfectedFiles") == false)
        m_setupFile->setSectionValue("Directories", "CopyInfectedFiles", "not checked|" + QDir::homePath() + "/.clamav-gui/quarantine");

    if (m_setupFile->keywordExists("Setup", "language") == false)
        m_setupFile->setSectionValue("Setup", "language", 2);

    if (m_setupFile->keywordExists("FreshClam","UpdatesPerDay") == false)
        m_setupFile->setSectionValue("FreshClam","UpdatesPerDay",12);

    if (m_setupFile->keywordExists("FreshClam","DataBaseToUpdate") == false)
        m_setupFile->setSectionValue("FreshClam","DataBaseToUpdate",0);

    if (m_setupFile->keywordExists("Freshclam","StartDaemon") == false)
        m_setupFile->setSectionValue("Freshclam","StartDaemon",false);

    if (m_setupFile->keywordExists("Setup","DisableLogHighlighter") == false)
        m_setupFile->setSectionValue("Setup","DisableLogHighlighter",false);

    if (m_setupFile->keywordExists("Setup","WindowState") == false)
        m_setupFile->setSectionValue("Setup","WindowState","maximized");

    m_ui->initialSettingsFileStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
}

void firstRunWindow::createClamdConfFile()
{
    QFile clamdConfFile(QDir::homePath() + "/.clamav-gui/clamd.conf");

    if (clamdConfFile.exists() == false) {
        m_clamdConf = new setupFileHandler(QDir::homePath() + "/.clamav-gui/clamd.conf", this);
        QString value = m_setupFile->getSectionValue("Directories", "LoadSupportedDBFiles");
        if (value.indexOf("checked|") == 0)
            m_clamdConf->addSingleLineValue("DatabaseDirectory", value.mid(value.indexOf("|") + 1));
        m_clamdConf->setSingleLineValue("LogSyslog", "no");
        m_clamdConf->setSingleLineValue("LogFacility", "LOG_LOCAL6");
        m_clamdConf->setSingleLineValue("PidFile", "/tmp/clamd.pid");
        m_clamdConf->setSingleLineValue("ExtendedDetectionInfo", "yes");
        m_clamdConf->setSingleLineValue("LocalSocket", QDir::homePath() + "/.clamav-gui/clamd-socket");
        m_clamdConf->setSingleLineValue("LogFile", QDir::homePath() + "/.clamav-gui/clamd.log");
        m_clamdConf->setSingleLineValue("LocalSocketGroup", "users");
        m_clamdConf->setSingleLineValue("TCPAddr", "127.0.0.1");
        m_clamdConf->addSingleLineValue("TCPAddr", "::1");
        m_clamdConf->setSingleLineValue("LogFileMaxSize", "1M");
        m_clamdConf->setSingleLineValue("LogTime", "yes");
        m_clamdConf->setSingleLineValue("LogRotate", "yes");
        m_clamdConf->setSingleLineValue("OnAccessMaxFileSize", "10M");
        m_clamdConf->setSingleLineValue("OnAccessMaxThreads", "10");
        m_clamdConf->setSingleLineValue("OnAccessPrevention", "yes");
        m_clamdConf->setSingleLineValue("OnAccessDenyOnError", "no");
        m_clamdConf->setSingleLineValue("OnAccessExtraScanning", "yes");
        m_clamdConf->setSingleLineValue("OnAccessRetryAttempts", "0");
        m_clamdConf->setSingleLineValue("OnAccessExcludeUname", "root");
        m_clamdConf->setSingleLineValue("OnAccessExcludeUID", "0");
    }

    m_ui->clamdConfStatusLabel->setPixmap(QPixmap(":/icons/icons/create.png"));
}

void firstRunWindow::createFreshclamConfFile()
{
    if (QFile::exists(QDir::homePath() + "/.clamav-gui/freshclam.conf") == false) {
        QFile freshclamConfFile(QDir::homePath() + "/.clamav-gui/freshclam.conf");
        freshclamConfFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);

        m_freshclamConf = new setupFileHandler(QDir::homePath() + "/.clamav-gui/freshclam.conf", this);
        QString value = m_setupFile->getSectionValue("Directories", "LoadSupportedDBFiles");
        if (value.indexOf("checked|") == 0)
            m_freshclamConf->setSingleLineValue("DatabaseDirectory", value.mid(value.indexOf("|") + 1));

        m_freshclamConf->setSingleLineValue("LogSyslog", "no");
        m_freshclamConf->setSingleLineValue("LogFacility", "LOG_LOCAL6");
        m_freshclamConf->setSingleLineValue("LogTime", "no");
        m_freshclamConf->setSingleLineValue("LogRotate", "no");
        m_freshclamConf->setSingleLineValue("PidFile", "/tmp/freshclam.pid");
        m_freshclamConf->setSingleLineValue("DatabaseOwner", "clamav");
        m_freshclamConf->setSingleLineValue("DatabaseMirror", "database.clamav.net");
        m_freshclamConf->setSingleLineValue("LogVerbose", "no");
        m_freshclamConf->setSingleLineValue("Checks", "12");
    }
}

