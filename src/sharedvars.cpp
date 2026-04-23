#include <QStringList>
#include <QString>

// --------------------------------------------------------------------------------------------------------------------------------------------------
// Used in : scanlimitstab.cpp
// --------------------------------------------------------------------------------------------------------------------------------------------------
enum scanLimits {FilesLargerThanThis,MaxAmountOfData,MinNumberOfFiles,MaxArchiveRecursion,MaxDirectoryRecursion,MaxSizeFilePE,MaxSizeHTMLNormalize,MaxSizeNormalizedHTML,
    MaxSizeScriptFileNormalize,MaxSizeZIPReanalyze,MaxNumberPartitions,MaxNumberIconsPE,NumberSecondsStatsTimeout,BytecodeTimeout,CollectAndPrint,StructSSNFormat,
    StructSSNCount,StructCCCount,StructCCMode,MaxScanTime,MaxRecursionHWP3,MaxCallsPCRE,MaxRecursionCallsPCRE,MaxPCREFileSize,DatabaseOutdated};

// --------------------------------------------------------------------------------------------------------------------------------------------------
// Used in : clamav-gui.cpp, includeexcludeoptions.cpp, main.cpp, profilemanager.cpp, profilewizarddialog.cpp, scheduler.cpp
// --------------------------------------------------------------------------------------------------------------------------------------------------
const QStringList inclExclKeywords = QString("DontScanFileNamesMatchingRegExp|"
                                         "DontScanDirectoriesMatchingRegExp|"
                                         "OnlyScanFileNamesMatchingRegExp|"
                                         "OnlyScanDirectoriesMatchingRegExp|"
                                         "EnablePUAOptions|"
                                         "LoadPUAPacked|"
                                         "LoadPUAPWTool|"
                                         "LoadPUANetTool|"
                                         "LoadPUAP2P|"
                                         "LoadPUAIRC|"
                                         "LoadPUARAT|"
                                         "LoadPUANetToolSpy|"
                                         "LoadPUAServer|"
                                         "LoadPUAScript|"
                                         "LoadPUAAndr|"
                                         "LoadPUAJava|"
                                         "LoadPUAOsx|"
                                         "LoadPUATool|"
                                         "LoadPUAUnix|"
                                         "LoadPUAWin").split("|");

// --------------------------------------------------------------------------------------------------------------------------------------------------
// Used in : clamav-gui.cpp, includeexcludeoptions.cpp, main.cpp, profilemanager.cpp, profilewizarddialog.cpp, scheduler.cpp
// --------------------------------------------------------------------------------------------------------------------------------------------------
const QStringList inclExclSwitches = QString("--exclude|"
                                            "--exclude-dir|"
                                            "--include|"
                                            "--include-dir|"
                                            "|"
                                            "--include-pua=Packed|"
                                            "--include-pua=PWTool|"
                                            "--include-pua=NetTool|"
                                            "--include-pua=P2P|"
                                            "--include-pua=IRC|"
                                            "--include-pua=RAT|"
                                            "--include-pua=NetToolSpy|"
                                            "--include-pua=Server|"
                                            "--include-pua=Script|"
                                            "--include-pua=Andr|"
                                            "--include-pua=Java|"
                                            "--include-pua=Osx|"
                                            "--include-pua=Tool|"
                                            "--include-pua=Unix|"
                                            "--include-pua=Win").split("|");


// --------------------------------------------------------------------------------------------------------------------------------------------------
// Used in : clamav-gui.cpp, main.cpp, profilemanager.cpp, profilewizard.cpp, scanlimitstab.cpp, scheduler.cpp
// --------------------------------------------------------------------------------------------------------------------------------------------------
const QStringList scanLimitKeywords = QString("Files larger than this will be skipped and assumed clean|"
                                            "The maximum amount of data to scan for each container file|"
                                            "The maximum number of files to scan for each container file|"
                                            "Maximum archive recursion level for container file|"
                                            "Maximum directory recursion level|"
                                            "Maximum size file to check for embedded PE|"
                                            "Maximum size of HTML file to normalize|"
                                            "Maximum size of normalized HTML file to scan|"
                                            "Maximum size of script file to normalize|"
                                            "Maximum size zip to type reanalyze|"
                                            "Maximum number of partitions in disk image to be scanned|"
                                            "Maximum number of icons in PE file to be scanned|"
                                            "Number of seconds to wait for waiting a response back from the stats server|"
                                            "Bytecode timeout in milliseconds|"
                                            "Collect and print execution statistics|"
                                            "Structured SSN Format|"
                                            "Structured SSN Count|"
                                            "Structured CC Count|"
                                            "Structured CC Mode|"
                                            "Max Scan-Time|"
                                            "Max recursion to HWP3 parsing function|"
                                            "Max calls to PCRE match function|"
                                            "Max recursion calls to the PCRE match function|"
                                            "Max PCRE file size|"
                                            "Database outdated if older than x days").split("|");

// --------------------------------------------------------------------------------------------------------------------------------------------------
// Used in : clamav-gui.cpp, main.cpp, profilemanager.cpp, profilewizard.cpp, scanlimitstab.cpp, scheduler.cpp
// --------------------------------------------------------------------------------------------------------------------------------------------------
const QStringList scanLimitSwitches = QString("--max-filesize|"
                                            "--max-scansize|"
                                            "--max-files|"
                                            "--max-recursion|"
                                            "--max-dir-recursion|"
                                            "--max-embeddedpe|"
                                            "--max-htmlnormalized|"
                                            "--max-htmlnotags|"
                                            "--max-scriptnormalize|"
                                            "--max-ziptypercg|"
                                            "--max-partitions|"
                                            "--max-iconspe|"
                                            "--stats-timeout|"
                                            "--bytecode-timeout|"
                                            "--statistics|"
                                            "--structured-ssn-format|"
                                            "--structured-ssn-count|"
                                            "--structured-cc-count|"
                                            "--structured-cc-mode|"
                                            "--max-scantime|"
                                            "--max-rechwp3|"
                                            "--pcre-match-limit|"
                                            "--pcre-recmatch-limit|"
                                            "--pcre-max-filesize|"
                                            "--fail-if-cvd-older-than").split("|");

// --------------------------------------------------------------------------------------------------------------------------------------------------
// Used in : clamav-gui.cpp, main.cpp, optiondialog.cpp, scheduler.cpp
// --------------------------------------------------------------------------------------------------------------------------------------------------
const QStringList directoryOptionKeywords = QString("LoadSupportedDBFiles|"
                                                "ScanReportToFile|"
                                                "ScanFilesFromFile|"
                                                "TmpFile|"
                                                "MoveInfectedFiles|"
                                                "CopyInfectedFiles|"
                                                "FollowDirectorySymLinks|"
                                                "FollowFileSymLinks").split("|");

// --------------------------------------------------------------------------------------------------------------------------------------------------
// Used in : clamav-gui.cpp, main.cpp, optiondialog.cpp, scheduler.cpp
// --------------------------------------------------------------------------------------------------------------------------------------------------
const QStringList directoryOptionSwitches = QString("--database|"
                                                "--log|"
                                                "--file-list|"
                                                "--tempdir|"
                                                "--move|"
                                                "--copy|"
                                                "--follow-dir-symlinks|"
                                                "--follow-file-symlinks").split("|");