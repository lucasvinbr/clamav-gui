<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="uk_UA" sourcelanguage="en_US">
<context>
    <name>ClamAV</name>
    <message>
        <source>Be verbose.</source>
        <translation>Будьте багатослівними.</translation>
    </message>
    <message>
        <source>Show filenames inside scanned archives.</source>
        <translation>Показувати назви файлів у сканованих архівах.</translation>
    </message>
    <message>
        <source>Enable libclamav&apos;s debug messages.</source>
        <translation>Увімкнути повідомлення про налагодження libclamav.</translation>
    </message>
    <message>
        <source>Only output error messages.</source>
        <translation>Виводити лише повідомлення про помилки.</translation>
    </message>
    <message>
        <source>Write to stdout instead of stderr. Does not affect &apos;debug&apos; messages.</source>
        <translation>Записувати в stdout замість stderr. Не впливає на повідомлення «налагодження».</translation>
    </message>
    <message>
        <source>Disable summary at end of scanning.</source>
        <translation>Вимкнути зведення в кінці сканування.</translation>
    </message>
    <message>
        <source>Only print infected files.</source>
        <translation>Друкуйте лише інфіковані файли.</translation>
    </message>
    <message>
        <source>Skip printing OK files.</source>
        <translation>Пропустити друк файлів OK.</translation>
    </message>
    <message>
        <source>Sound bell on virus detection.</source>
        <translation>Звуковий дзвінок при виявленні вірусу.</translation>
    </message>
    <message>
        <source>Do not remove temporary files.</source>
        <translation>Не видаляйте тимчасові файли.</translation>
    </message>
    <message>
        <source>Create temporary files for nested file scans that would otherwise be in-memory only.</source>
        <translation>Створіть тимчасові файли для сканування вкладених файлів, які інакше були б лише в пам’яті.</translation>
    </message>
    <message>
        <source>Generate JSON metadata for the scanned file(s). For testing &amp; development use ONLY. JSON will be printed if --debug is enabled. A JSON file will dropped to the temp directory if --leave-temps is enabled.</source>
        <translation>Створити метадані у форматі JSON для відсканованих файлів. Використовувати ВИКЛЮЧНО для тестування та розробки. Якщо ввімкнено параметр --debug, метадані у форматі JSON будуть виведені на екран. Якщо ввімкнено параметр --leave-temps, файл JSON буде збережено у тимчасовому каталозі.</translation>
    </message>
    <message>
        <source>Store html URIs in metadata. URIs will be written to the metadata.json file in an array called &apos;URIs&apos;.</source>
        <translation>Зберігайте URI html у метаданих. Ідентифікатори URI будуть записані у файл metadata.json у масиві під назвою «URI».</translation>
    </message>
    <message>
        <source>Store pdf URIs in metadata. URIs will be written to the metadata.json file in an array called &apos;URIs&apos;.</source>
        <translation>Зберігайте URI PDF-файлів у метаданих. Ідентифікатори URI будуть записані у файл metadata.json у масиві під назвою «URI».</translation>
    </message>
    <message>
        <source>Store md5 and sha1 in addition to sha2-256 in metadata.</source>
        <translation>Зберігайте md5 і sha1 на додаток до sha2-256 у метаданих.</translation>
    </message>
    <message>
        <source>Only load official signatures.</source>
        <translation>Завантажувати лише офіційні підписи.</translation>
    </message>
    <message>
        <source>Scan subdirectories recursively.</source>
        <translation>Сканувати підкаталоги рекурсивно.</translation>
    </message>
    <message>
        <source>Continue scanning within file after finding a match.</source>
        <translation>Продовжуйте сканувати файл після того, як знайдете збіг.</translation>
    </message>
    <message>
        <source>Scan files and directories on other filesystems.</source>
        <translation>Сканувати файли та каталоги в інших файлових системах.</translation>
    </message>
    <message>
        <source>Remove infected files. Be careful!</source>
        <translation>Видаліть заражені файли. Будьте обережні!</translation>
    </message>
    <message>
        <source>Load unsigned bytecode. **Caution**: You should NEVER run bytecode signatures from untrusted sources. Doing so may result in arbitrary code execution.</source>
        <translation>Завантажити непідписаний байт-код. **Увага**: НІКОЛИ не слід запускати підписи байт-коду з ненадійних джерел. Це може призвести до виконання довільного коду.</translation>
    </message>
    <message>
        <source>Detect Possibly Unwanted Applications.</source>
        <translation>Виявлення можливо небажаних програм.</translation>
    </message>
    <message>
        <source>Detect structured data (SSN, Credit Card).</source>
        <translation>Виявлення структурованих даних (SSN, кредитна картка).</translation>
    </message>
    <message>
        <source>Scan mail files.</source>
        <translation>Сканувати поштові файли.</translation>
    </message>
    <message>
        <source>Enable email signature-based phishing detection.</source>
        <translation>Увімкнути виявлення фішингу електронної пошти на основі підпису.</translation>
    </message>
    <message>
        <source>Enable URL signature-based phishing detection.</source>
        <translation>Увімкнути виявлення фішингу на основі підпису URL-адреси.</translation>
    </message>
    <message>
        <source>Heuristic alerts.</source>
        <translation>Евристичні сповіщення.</translation>
    </message>
    <message>
        <source>Stop scanning as soon as a heuristic match is found.</source>
        <translation>Припиніть сканування, як тільки буде знайдено евристичний збіг.</translation>
    </message>
    <message>
        <source>Normalize html, script, and text files. Use normalize=no for yara compatibility.</source>
        <translation>Нормалізація html, сценаріїв і текстових файлів. Використовуйте normalize=no для сумісності з yara.</translation>
    </message>
    <message>
        <source>Scan PE files.</source>
        <translation>Сканувати файли PE.</translation>
    </message>
    <message>
        <source>Scan ELF files.</source>
        <translation>Сканування файлів ELF.</translation>
    </message>
    <message>
        <source>Scan OLE2 containers.</source>
        <translation>Сканування контейнерів OLE2.</translation>
    </message>
    <message>
        <source>Scan PDF files.</source>
        <translation>Сканувати файли PDF.</translation>
    </message>
    <message>
        <source>Scan SWF files.</source>
        <translation>Сканувати файли SWF.</translation>
    </message>
    <message>
        <source>Scan HTML files.</source>
        <translation>Сканувати файли HTML.</translation>
    </message>
    <message>
        <source>Scan xml-based document files.</source>
        <translation>Сканувати файли документів на основі xml.</translation>
    </message>
    <message>
        <source>Scan HWP3 files.</source>
        <translation>Сканувати файли HWP3.</translation>
    </message>
    <message>
        <source>Scan OneNote files.</source>
        <translation>Сканування файлів OneNote.</translation>
    </message>
    <message>
        <source>Scan archive files (supported by libclamav).</source>
        <translation>Сканувати архівні файли (підтримується libclamav).</translation>
    </message>
    <message>
        <source>Scan image (graphics) files.</source>
        <translation>Сканувати файли зображень (графіки).</translation>
    </message>
    <message>
        <source>Detect files by calculating image (graphics) fuzzy hashes.</source>
        <translation>Виявляйте файли шляхом обчислення нечітких хешів зображень (графіки).</translation>
    </message>
    <message>
        <source>Alert on broken graphics files (JPEG, TIFF, PNG, GIF).</source>
        <translation>Сповіщення про пошкоджені графічні файли (JPEG, TIFF, PNG, GIF).</translation>
    </message>
    <message>
        <source>Alert on encrypted archives and documents.</source>
        <translation>Сповіщення про зашифровані архіви та документи.</translation>
    </message>
    <message>
        <source>Alert on encrypted archives.</source>
        <translation>Сповіщення про зашифровані архіви.</translation>
    </message>
    <message>
        <source>Alert on OLE2 files containing VBA macros.</source>
        <translation>Сповіщення про файли OLE2, що містять макроси VBA.</translation>
    </message>
    <message>
        <source>Alert on files that exceed max file size, max scan size, or max recursion limit.</source>
        <translation>Сповіщення про файли, які перевищують максимальний розмір файлу, максимальний розмір сканування або максимальний ліміт рекурсії.</translation>
    </message>
    <message>
        <source>Alert on emails containing SSL mismatches in URLs.</source>
        <translation>Сповіщення про електронні листи, які містять невідповідності SSL в URL-адресах.</translation>
    </message>
    <message>
        <source>Alert on emails containing cloaked URLs.</source>
        <translation>Сповіщення про електронні листи, що містять приховані URL-адреси.</translation>
    </message>
    <message>
        <source>Alert on raw DMG image files containing partition intersections.</source>
        <translation>Сповіщення про необроблені файли зображень DMG, які містять перетини розділів.</translation>
    </message>
    <message>
        <source>Disable authenticode certificate chain verification in PE files.</source>
        <translation>Вимкнути перевірку ланцюжка сертифікатів автентикоду в PE-файлах.</translation>
    </message>
    <message>
        <source>Dump authenticode certificate chain in PE files.</source>
        <translation>Дамп ланцюжка сертифікатів автентикоду в PE-файли.</translation>
    </message>
    <message>
        <source>Disable caching and cache checks for hash sums of scanned files.</source>
        <translation>Вимкніть кешування та перевірку кешу на хеш-суми сканованих файлів.</translation>
    </message>
    <message>
        <source>Print the file hash after each file scanned. The type of hash printed will match the '--hash-alg'.</source>
        <translation>Виводити хеш-код файлу після сканування кожного файлу. Тип виведеного хеш-коду відповідатиме параметру «--hash-alg».</translation>
    </message>
    <message>
        <source>Print the file type after each file scanned.</source>
        <translation>Друкуйте тип файлу після кожного сканованого файлу.</translation>
    </message>
    <message>
        <source>Enforce FIPS-like limits on using hash algorithms for cryptographic purposes. Will disable MD5 &amp; SHA1. FP sigs and will require &apos;.sign&apos; files to verify CVD authenticity.</source>
        <translation>Забезпечте обмеження, подібні до FIPS, на використання алгоритмів хешування для криптографічних цілей. Вимкне MD5 і SHA1. PHP підписує та вимагатиме файлів &apos;.sign&apos; для перевірки автентичності CVD.</translation>
    </message>
    <message>
        <source>By default the log file is locked for writing and only a single daemon process can write to it. This option disables the lock. Default: no</source>
        <translation>За замовчуванням файл журналу заблоковано для запису, і лише один процес демона може писати в нього. Цей параметр вимикає блокування. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Maximum size of the log file. Value of 0 disables the limit. Default: 1048576</source>
        <translation>Максимальний розмір файлу журналу. Значення 0 вимикає обмеження. Типове значення: 1048576</translation>
    </message>
    <message>
        <source>Log time for each message. Default: no</source>
        <translation>Час журналу для кожного повідомлення. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Log all clean files. Useful in debugging but drastically increases the log size. Default: no</source>
        <translation>Зареєструвати всі чисті файли. Корисно для налагодження, але значно збільшує розмір журналу. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Use the system logger (can work together with LogFile). Default: no</source>
        <translation>Використовуйте системний журнал (може працювати разом з LogFile). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Type of syslog messages Please refer to &apos;man syslog&apos; for facility names. Default: LOG_LOCAL6</source>
        <translation>Тип повідомлень системного журналу Будь ласка, зверніться до &apos;man syslog&apos; для назв засобів. За замовчуванням: LOG_LOCAL6</translation>
    </message>
    <message>
        <source>Enable verbose logging. Default: no</source>
        <translation>Увімкнути детальне журналювання. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Rotate log file. Requires LogFileMaxSize option set prior to this option. Default: no</source>
        <translation>Повернути файл журналу. Потрібен параметр LogFileMaxSize, встановлений перед цим параметром. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Log additional information about the infected file, such as its size and hash, together with the virus name. Default: no</source>
        <translation>Реєструйте додаткову інформацію про заражений файл, наприклад його розмір і хеш, разом із назвою вірусу. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>This option allows you to change the default temporary directory. Default: system specific (usually /tmp or /var/tmp).</source>
        <translation>Цей параметр дозволяє змінити типовий тимчасовий каталог. За замовчуванням: для системи (зазвичай /tmp або /var/tmp).</translation>
    </message>
    <message>
        <source>This option allows you to change the default database directory. If you enable it, please make sure it points to the same direc‐ tory in both clamd and freshclam. Default: defined at configuration (/usr/local/share/clamav)</source>
        <translation>Цей параметр дозволяє змінити каталог бази даних за замовчуванням. Якщо ви ввімкнете його, переконайтеся, що він вказує на той самий каталог у clamd і freshclam. За замовчуванням: визначено в конфігурації (/usr/local/share/clamav)</translation>
    </message>
    <message>
        <source>Path to a directory containing ClamAV CA certificate files used to verify signed database archives (e.g. CVD files). This direc‐ tory must already exist, be an absolute path, be readable by freshclam, clamd, clamscan, and sigtool. Default: /etc/certs</source>
        <translation>Шлях до каталогу, що містить файли сертифікатів ЦС ClamAV, які використовуються для перевірки підписаних архівів бази даних (наприклад, файли CVD). Цей каталог уже має існувати, бути абсолютним шляхом, бути доступним для читання за допомогою freshclam, clamd, clamscan і sigtool. За замовчуванням: /etc/certs</translation>
    </message>
    <message>
        <source>Enforce FIPS-like limits on using hash algorithms for crypto‐ graphic purposes. Will disable MD5 &amp; SHA1 FP sigs and will re‐ quire &apos;.sign&apos; files to verify CVD authenticity. Default: no</source>
        <translation>Забезпечте обмеження, подібні до FIPS, на використання хеш-алгоритмів для криптографічних цілей. Вимкне підписи MD5 і SHA1 FP і вимагатиме файлів «.sign» для перевірки автентичності CVD. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Only load the official signatures published by the ClamAV project. Default: no</source>
        <translation>Завантажуйте лише офіційні підписи, опубліковані проектом ClamAV. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Return with a nonzero error code if the virus database is older than the specified number of days. Default: -1</source>
        <translation>Повернути з ненульовим кодом помилки, якщо вірусна база даних старша за вказану кількість днів. Типове значення: -1</translation>
    </message>
    <message>
        <source>Remove stale socket after unclean shutdown. Default: yes</source>
        <translation>Видаліть застарілий сокет після нечистого вимкнення. За замовчуванням: так</translation>
    </message>
    <message>
        <source>TCP port number the daemon will listen on. Default: disabled</source>
        <translation>Номер порту TCP, який демон слухатиме. За замовчуванням: вимкнено</translation>
    </message>
    <message>
        <source>By default clamd binds to INADDR_ANY. This option allows you to restrict the TCP address and provide some degree of protection from the outside world. This option can be specified multiple times in order to listen on multiple IPs. IPv6 is now supported. Default: disabled</source>
        <translation>За замовчуванням clamd прив’язується до INADDR_ANY. Цей параметр дозволяє обмежити TCP-адресу та забезпечити певний ступінь захисту від зовнішнього світу. Цей параметр можна вказати кілька разів, щоб прослуховувати кілька IP-адрес. IPv6 тепер підтримується. За замовчуванням: вимкнено</translation>
    </message>
    <message>
        <source>Maximum length the queue of pending connections may grow to. Default: 200</source>
        <translation>Максимальна довжина черги з’єднань, що очікують, може зрости. Типове значення: 200</translation>
    </message>
    <message>
        <source>Close the STREAM session when the data size limit is exceeded. The value should match your MTA&apos;s limit for the maximum attach‐ ment size. Default: 100M</source>
        <translation>Закрийте сеанс STREAM, коли перевищено ліміт розміру даних. Значення має відповідати обмеженню вашого MTA для максимального розміру вкладення. За замовчуванням: 100M</translation>
    </message>
    <message>
        <source>The STREAM command uses an FTP-like protocol. This option sets the lower boundary for the port range. Default: 1024</source>
        <translation>Команда STREAM використовує FTP-подібний протокол. Цей параметр встановлює нижню межу діапазону портів. Типове значення: 1024</translation>
    </message>
    <message>
        <source>This option sets the upper boundary for the port range. Default: 2048</source>
        <translation>Цей параметр встановлює верхню межу діапазону портів. Типове значення: 2048</translation>
    </message>
    <message>
        <source>Maximum number of threads running at the same time. Default: 10</source>
        <translation>Максимальна кількість потоків, що виконуються одночасно. Типове значення: 10</translation>
    </message>
    <message>
        <source>This option specifies the time (in seconds) after which clamd should timeout if a client doesn&apos;t provide any data. Default: 120</source>
        <translation>Цей параметр визначає час (у секундах), після якого clamd має закінчитися, якщо клієнт не надає жодних даних. Типове значення: 120</translation>
    </message>
    <message>
        <source>This option specifies the time (in seconds) after which clamd should timeout if a client doesn&apos;t provide any initial command after connecting. The default is set to 30 to avoid timeouts with TCP sockets when processing large messages. If using a Unix socket, the value can be changed to 5. Note: the timeout for subsequents commands, and/or data chunks is specified by Read‐ Timeout. Default: 30</source>
        <translation>Цей параметр визначає час (у секундах), після якого clamd має закінчитися, якщо клієнт не надає початкової команди після підключення. За замовчуванням встановлено значення 30, щоб уникнути тайм-аутів із TCP-сокетами під час обробки великих повідомлень. Якщо використовується сокет Unix, значення можна змінити на 5. Примітка: тайм-аут для наступних команд і/або фрагментів даних визначається параметром Read‐Timeout. Типове значення: 30</translation>
    </message>
    <message>
        <source>This option specifies how long to wait (in milliseconds) if the send buffer is full. Keep this value low to prevent clamd hang‐ ing. Default: 500</source>
        <translation>Цей параметр визначає, як довго чекати (у мілісекундах), якщо буфер надсилання заповнений. Тримайте це значення низьким, щоб запобігти зависанню. Типове значення: 500</translation>
    </message>
    <message>
        <source>Maximum number of queued items (including those being processed by MaxThreads threads). It is recommended to have this value at least twice MaxThreads if possible. WARNING: you shouldn&apos;t increase this too much to avoid running out of file descriptors, the following condition should hold: MaxThreads*MaxRecursion + MaxQueue - MaxThreads + 6 &lt; RLIMIT_NOFILE. RLIMIT_NOFILE is the maximum number of open file descriptors (usually 1024), set by ulimit -n. Default: 100</source>
        <translation>Максимальна кількість елементів у черзі (включаючи ті, що обробляються потоками MaxThreads). Рекомендується мати це значення принаймні вдвічі більше MaxThreads, якщо це можливо. ПОПЕРЕДЖЕННЯ: ви не повинні збільшувати це надто багато, щоб уникнути вичерпання дескрипторів файлів, така умова має виконуватися: MaxThreads*MaxRecursion + MaxQueue - MaxThreads + 6 &lt; RLIMIT_NOFILE. RLIMIT_NOFILE — максимальна кількість відкритих файлових дескрипторів (зазвичай 1024), встановлена ​​ulimit -n. Типове значення: 100</translation>
    </message>
    <message>
        <source>This option specifies how long (in seconds) the process should wait for a new job. Default: 30</source>
        <translation>Цей параметр визначає, як довго (у секундах) процес має чекати нового завдання. Типове значення: 30</translation>
    </message>
    <message>
        <source>Maximum depth directories are scanned at. Default: 15</source>
        <translation>Каталоги скануються на максимальній глибині. Типове значення: 15</translation>
    </message>
    <message>
        <source>Follow directory symlinks. Default: no</source>
        <translation>Переходьте за символічними посиланнями каталогу. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Scan files and directories on other filesystems. Default: yes</source>
        <translation>Сканувати файли та каталоги в інших файлових системах. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Follow regular file symlinks. Default: no</source>
        <translation>Переходьте за звичайними символічними посиланнями на файли. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>This option specifies the time intervals (in seconds) in which clamd should perform a database check. Default: 600</source>
        <translation>Цей параметр визначає інтервали часу (у секундах), протягом яких clamd має виконувати перевірку бази даних. Типове значення: 600</translation>
    </message>
    <message>
        <source>Enable non-blocking (multi-threaded/concurrent) database reloads. This feature will temporarily load a second scanning engine while scanning continues using the first engine. Once loaded, the new engine takes over. The old engine is removed as soon as all scans using the old engine have completed. This feature requires more RAM, so this option is provided in case users are willing to block scans during reload in exchange for lower RAM requirements. Default: yes</source>
        <translation>Увімкнути неблокуюче (багатопотокове/одночасне) перезавантаження бази даних. Ця функція тимчасово завантажить другий механізм сканування, поки сканування продовжується за допомогою першого механізму. Після завантаження новий двигун бере на себе роботу. Старий механізм видаляється, щойно всі сканування за допомогою старого механізму завершаться. Для цієї функції потрібно більше оперативної пам’яті, тому цей параметр доступний, якщо користувачі бажають блокувати сканування під час перезавантаження в обмін на менші вимоги до оперативної пам’яті. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Execute a command when virus is found. Use the following envi‐ ronment variables to identify the file and virus names: - $CLAM_VIRUSEVENT_FILENAME - $CLAM_VIRUSEVENT_VIRUSNAME In the command string, &apos;%v&apos; will also be replaced with the virus name. Note: The &apos;%f&apos; filename format character has been disabled and will no longer be replaced with the file name, due to command in‐ jection security concerns. Use the &apos;CLAM_VIRUSEVENT_FILENAME&apos; environment variable instead. For the same reason, you should NOT use the environment variables in the command directly, but should use it carefully from your executed script. Default: disabled</source>
        <translation>Виконати команду при виявленні вірусу. Використовуйте наступні змінні середовища, щоб визначити імена файлів і вірусів: - $CLAM_VIRUSEVENT_FILENAME - $CLAM_VIRUSEVENT_VIRUSNAME У командному рядку &quot;%v&quot; також буде замінено назвою вірусу. Примітка. Символ формату назви файлу «%f» вимкнено та більше не замінюватиметься назвою файлу через проблеми безпеки введення команди. Натомість використовуйте змінну середовища &quot;CLAM_VIRUSEVENT_FILENAME&quot;. З тієї ж причини вам НЕ слід використовувати змінні середовища безпосередньо в команді, але слід обережно використовувати їх у виконаному сценарії. За замовчуванням: вимкнено</translation>
    </message>
    <message>
        <source>Stop daemon when libclamav reports out of memory condition. Default: no</source>
        <translation>Зупинити демон, коли libclamav повідомляє про стан пам’яті. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Permit use of the ALLMATCHSCAN command. Default: yes</source>
        <translation>Дозволити використання команди ALLMATCHSCAN. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Don&apos;t fork into background. Default: no</source>
        <translation>Не відходьте на задній план. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Enable debug messages from libclamav. Default: no</source>
        <translation>Увімкнути повідомлення про налагодження з libclamav. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Do not remove temporary files (for debugging purpose). Default: no</source>
        <translation>Не видаляйте тимчасові файли (з метою налагодження). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Record metadata about the file being scanned. Scan metadata is useful for file analysis purposes and for debugging scan behav‐ ior. The JSON metadata will be printed after the scan is com‐ plete if Debug is enabled. A metadata.json file will be written to the scan temp directory if LeaveTemporaryFiles is enabled. Default: no</source>
        <translation>Запис метаданих про файл, який сканується. Метадані сканування корисні для цілей аналізу файлів і для налагодження поведінки сканування. Метадані JSON буде надруковано після завершення сканування, якщо ввімкнено Debug. Файл metadata.json буде записаний у тимчасовий каталог сканування, якщо ввімкнено LeaveTemporaryFiles. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Store URIs found in html files to the json metadata. URIs will be stored in an array with the tag &apos;URIs&apos;. GenerateMetadataJson is required for this feature. Default: yes (if GenerateMetadataJson is used)</source>
        <translation>Зберігайте URI, знайдені у файлах html, у метаданих json. URI будуть зберігатися в масиві з тегом &quot;URI&quot;. Для цієї функції потрібен GenerateMetadataJson. Типове значення: так (якщо використовується GenerateMetadataJson)</translation>
    </message>
    <message>
        <source>Store URIs found in pdf files to the json metadata. URIs will be stored in an array with the tag &apos;URIs&apos;. GenerateMetadataJson is required for this feature. Default: yes (if GenerateMetadataJson is used)</source>
        <translation>Зберігайте URI, знайдені у файлах PDF, у метаданих json. URI будуть зберігатися в масиві з тегом &quot;URI&quot;. Для цієї функції потрібен GenerateMetadataJson. Типове значення: так (якщо використовується GenerateMetadataJson)</translation>
    </message>
    <message>
        <source>Calculate MD5 and SHA1 hashes (in addition to SHA2-256) and store to the json metadata. GenerateMetadataJson is required for this feature. Default: no</source>
        <translation>Обчислюйте хеші MD5 і SHA1 (на додаток до SHA2-256) і зберігайте в метаданих json. Для цієї функції потрібен GenerateMetadataJson. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Run the daemon as a specified user (the process must be started by root). Default: disabled</source>
        <translation>Запустіть демон від імені вказаного користувача (процес повинен бути запущений адміністратором). За замовчуванням: вимкнено</translation>
    </message>
    <message>
        <source>With this option enabled ClamAV will load bytecode from the data‐ base. It is highly recommended you keep this option turned on, otherwise you may miss detections for many new viruses. Default: yes</source>
        <translation>Якщо цей параметр увімкнено, ClamAV завантажуватиме байт-код із бази даних. Настійно рекомендується залишати цей параметр увімкненим, інакше ви можете пропустити виявлення багатьох нових вірусів. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Set bytecode security level. Possible values: TrustSigned - trust bytecode loaded from signed .c[lv]d files and insert runtime safety checks for bytecode loaded from other sources, Paranoid - don&apos;t trust any bytecode, insert runtime checks for all. Recommended: TrustSigned, because bytecode in .cvd files already has these checks. Default: TrustSigned</source>
        <translation>Встановити рівень безпеки байт-коду. Можливі значення: TrustSigned — довіряти байткоду, завантаженому з підписаних файлів .c[lv]d, і вставляти перевірки безпеки під час виконання для байт-коду, завантаженого з інших джерел, Paranoid — не довіряти жодному байт-коду, вставляти перевірки під час виконання для всіх. Рекомендовано: TrustSigned, оскільки байт-код у файлах .cvd уже має ці перевірки. За замовчуванням: TrustSigned</translation>
    </message>
    <message>
        <source>Set bytecode timeout in milliseconds. Default: 10000</source>
        <translation>Встановити час очікування байт-коду в мілісекундах. Типове значення: 10000</translation>
    </message>
    <message>
        <source>Allow loading bytecode from outside digitally signed .c[lv]d files. **Caution**: You should NEVER run bytecode signatures from untrusted sources. Doing so may result in arbitrary code execution. Default: no</source>
        <translation>Дозволити завантажувати байт-код із зовнішніх файлів .c[lv]d із цифровим підписом. **Увага**: НІКОЛИ не слід запускати підписи байт-коду з ненадійних джерел. Це може призвести до виконання довільного коду. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Set bytecode execution mode. Possible values: Auto - automatically choose JIT if possible, fallback to in‐ terpreter ForceJIT - always choose JIT, fail if not possible ForceInterpreter - always choose interpreter Test - run with both JIT and interpreter and compare results. Make all failures fatal. Default: Auto</source>
        <translation>Встановити режим виконання байт-коду. Можливі значення: Auto — автоматично вибирати JIT, якщо це можливо, повернутися до інтерпретатора ForceJIT — завжди вибирати JIT, fail, якщо це неможливо ForceInterpreter — завжди вибирати інтерпретатор Test — запустити як з JIT, так і з інтерпретатором і порівняти результати. Зробіть усі невдачі фатальними. За замовчуванням: Авто</translation>
    </message>
    <message>
        <source>Detect Possibly Unwanted Applications. Default: No</source>
        <translation>Виявлення можливо небажаних програм. За замовчуванням: Ні</translation>
    </message>
    <message>
        <source>In some cases (eg. complex malware, exploits in graphic files, and others), ClamAV uses special algorithms to provide accurate detection. This option controls the algorithmic detection. Default: yes</source>
        <translation>У деяких випадках (наприклад, складне шкідливе програмне забезпечення, експлойти в графічних файлах тощо) ClamAV використовує спеціальні алгоритми для забезпечення точного виявлення. Ця опція керує алгоритмічним виявленням. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Allow heuristic match to take precedence. When enabled, if a heuristic scan (such as phishingScan) detects a possible virus/phishing it will stop scanning immediately. Recommended, saves CPU scan-time. When disabled, virus/phishing detected by heuristic scans will be reported only at the end of a scan. If an archive contains both a heuristically detected virus/phishing, and a real malware, the real malware will be reported. Keep this disabled if you intend to handle &quot;*.Heuristics.*&quot; viruses dif‐ ferently from &quot;real&quot; malware. If a non-heuristically-detected virus (signature-based) is found first, the scan is interrupted immediately, regardless of this config option. Default: no</source>
        <translation>Дозволити евристичному збігу мати пріоритет. Якщо ввімкнено, якщо евристичне сканування (наприклад, phishingScan) виявить можливий вірус/фішинг, воно негайно припинить сканування. Рекомендовано, економить час сканування ЦП. Якщо вимкнено, віруси/фішинг, виявлені під час евристичного сканування, повідомлятимуть лише наприкінці сканування. Якщо архів містить і евристично виявлений вірус/фішинг, і справжнє зловмисне програмне забезпечення, буде повідомлено про справжнє зловмисне програмне забезпечення. Вимкніть цю функцію, якщо ви збираєтеся обробляти віруси «*.Euristics.*» на відміну від «справжнього» шкідливого програмного забезпечення. Якщо першим знайдено неевристично виявлений вірус (на основі сигнатур), сканування негайно переривається, незалежно від цього параметра конфігурації. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>PE stands for Portable Executable - it&apos;s an executable file for‐ mat used in all 32 and 64-bit versions of Windows operating sys‐ tems. This option allows ClamAV to perform a deeper analysis of executable files and it&apos;s also required for decompression of pop‐ ular executable packers such as UPX. If you turn off this option, the original files will still be scanned, but without additional processing. Default: yes</source>
        <translation>PE означає Portable Executable — це формат виконуваного файлу, який використовується у всіх 32- та 64-розрядних версіях операційних систем Windows. Ця опція дозволяє ClamAV виконувати глибший аналіз виконуваних файлів, а також потрібна для декомпресії популярних пакувальників виконуваних файлів, таких як UPX. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Executable and Linking Format is a standard format for UN*X exe‐ cutables. This option allows you to control the scanning of ELF files. If you turn off this option, the original files will still be scanned, but without additional processing. Default: yes</source>
        <translation>Формат виконуваних файлів і зв’язків — це стандартний формат для виконуваних файлів UN*X. Цей параметр дозволяє контролювати сканування файлів ELF. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Enable scanning of mail files. If you turn off this option, the original files will still be scanned, but without parsing individual messages/attachments. Default: yes</source>
        <translation>Увімкнути сканування поштових файлів. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без аналізу окремих повідомлень/вкладень. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Scan RFC1341 messages split over many emails. You will need to periodically clean up $TemporaryDirectory/clamav-partial direc‐ tory. WARNING: This option may open your system to a DoS attack. Never use it on loaded servers. Default: no</source>
        <translation>Сканувати повідомлення RFC1341, розділені на багато листів. Вам потрібно буде періодично очищати каталог $TemporaryDirectory/clamav-partial. ПОПЕРЕДЖЕННЯ. Ця опція може відкрити вашу систему для DoS-атаки. Ніколи не використовуйте його на завантажених серверах. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Enable email signature-based phishing detection. Default: yes</source>
        <translation>Увімкнути виявлення фішингу електронної пошти на основі підпису. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Enable URL signature-based phishing detection (Heuristics.Phish‐ ing.Email.*) Default: yes</source>
        <translation>Увімкнути виявлення фішингу на основі підпису URL-адреси (Euristics.Phishing.Email.*) Типове значення: так</translation>
    </message>
    <message>
        <source>Enable the DLP module. Default: no</source>
        <translation>Увімкніть модуль DLP. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>This option sets the lowest number of Credit Card numbers found in a file to generate a detect. Default: 3</source>
        <translation>Цей параметр встановлює найменшу кількість номерів кредитних карток, знайдених у файлі, для створення виявлення. Типове значення: 3</translation>
    </message>
    <message>
        <source>With this option enabled the DLP module will search for valid Credit Card0umbers only. Debit and Private Label cards will not be searched. Default: No</source>
        <translation>Якщо цей параметр увімкнено, модуль DLP шукатиме лише дійсні номери кредитних карток. Дебетові картки та картки приватної марки не шукатимуться. За замовчуванням: Ні</translation>
    </message>
    <message>
        <source>This option sets the lowest number of Social Security Numbers found in a file to generate a detect. Default: 3</source>
        <translation>Цей параметр встановлює найменшу кількість номерів соціального страхування, знайдених у файлі, для створення виявлення. Типове значення: 3</translation>
    </message>
    <message>
        <source>With this option enabled the DLP module will search for valid SSNs formatted as xxx-yy-zzzz. Default: Yes</source>
        <translation>Якщо цей параметр увімкнено, модуль DLP шукатиме дійсні SSN у форматі xxx-yy-zzzz. За замовчуванням: Так</translation>
    </message>
    <message>
        <source>With this option enabled the DLP module will search for valid SSNs formatted as xxxyyzzzz. Default: No</source>
        <translation>Якщо цей параметр увімкнено, модуль DLP шукатиме дійсні SSN у форматі xxxyyzzzz. За замовчуванням: Ні</translation>
    </message>
    <message>
        <source>Perform HTML/JavaScript/ScriptEncoder normalisation and decryp‐ tion. If you turn off this option, the original files will still be scanned, but without additional processing. Default: yes</source>
        <translation>Виконайте нормалізацію та дешифрування HTML/JavaScript/Script Encoder. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>This option enables scanning of OLE2 files, such as Microsoft Of‐ fice documents and .msi files. If you turn off this option, the original files will still be scanned, but without additional processing. Default: yes</source>
        <translation>Цей параметр дозволяє сканувати файли OLE2, наприклад документи Microsoft Office і файли .msi. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>This option enables scanning within PDF files. If you turn off this option, the original files will still be scanned, but without additional processing. Default: yes</source>
        <translation>Ця опція дозволяє сканувати PDF-файли. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>This option enables scanning within SWF files. If you turn off this option, the original files will still be scanned, but without decoding and additional processing. Default: yes</source>
        <translation>Цей параметр дозволяє сканувати файли SWF. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без декодування та додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>This option enables scanning xml-based document files supported by libclamav. If you turn off this option, the original files will still be scanned, but without additional processing. Default: yes</source>
        <translation>Цей параметр дозволяє сканувати файли документів на основі xml, які підтримує libclamav. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>This option enables scanning HWP3 files. If you turn off this option, the original files will still be scanned, but without additional processing. Default: yes</source>
        <translation>Цей параметр дозволяє сканувати файли HWP3. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>This option enables scanning OneNote files. If you turn off this option, the original files will still be scanned, but without additional processing. Default: yes</source>
        <translation>Цей параметр дозволяє сканувати файли OneNote. Якщо вимкнути цю опцію, вихідні файли все одно скануватимуться, але без додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Scan within archives and compressed files. If you turn off this option, the original files will still be scanned, but without unpacking and additional processing. Default: yes</source>
        <translation>Сканування в архівах і стиснутих файлах. Якщо вимкнути цю опцію, оригінальні файли все одно будуть скануватися, але без розпакування та додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>This option enables scanning of image (graphics). If you turn off this option, the original files will still be scanned, but without unpacking and additional processing. Default: yes</source>
        <translation>Ця опція дозволяє сканувати зображення (графіку). Якщо вимкнути цю опцію, оригінальні файли все одно будуть скануватися, але без розпакування та додаткової обробки. За замовчуванням: так</translation>
    </message>
    <message>
        <source>This option enables detection by calculating a fuzzy hash of im‐ age (graphics) files. Signatures using image fuzzy hashes typi‐ cally match files and documents by identifying images embedded or attached to those files. If you turn off this option, then some files may no longer be de‐ tected. Default: yes</source>
        <translation>Цей параметр дозволяє виявлення шляхом обчислення нечіткого хешу файлів зображень (графіки). Підписи з використанням нечітких хешів зображень зазвичай відповідають файлам і документам, ідентифікуючи зображення, вбудовані або прикріплені до цих файлів. Якщо вимкнути цей параметр, деякі файли можуть більше не виявлятися. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Alert on broken executable files (PE &amp; ELF). Default: no</source>
        <translation>Сповіщення про пошкоджені виконувані файли (PE та ELF). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Alert on broken graphics files (JPEG, TIFF, PNG, GIF). Default: no</source>
        <translation>Сповіщення про пошкоджені графічні файли (JPEG, TIFF, PNG, GIF). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Alert on encrypted archives and documents (encrypted .zip, .7zip, .rar, .pdf). Default: no</source>
        <translation>Сповіщення про зашифровані архіви та документи (зашифровані .zip, .7zip, .rar, .pdf). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Alert on encrypted archives (encrypted .zip, .7zip, .rar). Default: no</source>
        <translation>Сповіщення про зашифровані архіви (зашифровані .zip, .7zip, .rar). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Alert on encrypted documents (encrypted .pdf). Default: no</source>
        <translation>Сповіщення про зашифровані документи (зашифровані .pdf). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Alert on OLE2 files containing VBA macros (Heuristics.OLE2.Con‐ tainsMacros). Default: no</source>
        <translation>Сповіщення про файли OLE2, що містять макроси VBA (Heuristics.OLE2.ContainsMacros). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>When AlertExceedsMax is set, files exceeding the MaxFileSize, MaxScanSize, or MaxRecursion limit will be flagged with the virus name starting with &quot;Heuristics.Limits.Exceeded&quot;. Default: no</source>
        <translation>Якщо встановлено AlertExceedMax, файли, що перевищують ліміт MaxFileSize, MaxScanSize або MaxRecursion, позначатимуться прапорцями з назвою вірусу, що починається з &quot;Euristics.Limits.Exceeded&quot;. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Alert on emails containing SSL mismatches in URLs (might lead to false positives!). Default: no</source>
        <translation>Сповіщення про електронні листи, які містять невідповідності SSL в URL-адресах (може призвести до помилкових спрацьовувань!). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Alert on emails containing cloaked URLs (might lead to some false positives). Default: no</source>
        <translation>Сповіщення про електронні листи, що містять приховані URL-адреси (може призвести до помилкових спрацьовувань). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Alert on raw DMG image files containing partition intersections. Default: no</source>
        <translation>Сповіщення про необроблені файли зображень DMG, які містять перетини розділів. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>This option allows you to disable the caching feature of the en‐ gine. By default, the engine will store an MD5 in a cache of any files that are not flagged as virus or that hit limits checks. Warning: Disabling the cache will have a negative performance impact on large scans. Default: no</source>
        <translation>Цей параметр дозволяє вимкнути функцію кешування двигуна. За замовчуванням механізм зберігатиме MD5 у кеш-пам’яті будь-яких файлів, які не позначено як вірус або які потрапили під обмеження. Попередження: вимкнення кешу матиме негативний вплив на продуктивність великих сканувань. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>This option allows you to set the number of entries the cache can store. The value should be a square number or will be rounded up to the nearest square number. Default: 65536</source>
        <translation>Цей параметр дозволяє встановити кількість записів, які може зберігати кеш. Значення має бути квадратним числом або буде округлено до найближчого квадратного числа. Типове значення: 65536</translation>
    </message>
    <message>
        <source>This option causes memory or nested map scans to dump the content to disk. If you turn on this option, more data is written to disk and is available when the leave-temps option is enabled at the cost of more disk writes. Default: no</source>
        <translation>Цей параметр змушує сканування пам’яті або вкладених карт створювати дамп вмісту на диск. Якщо ввімкнути цю опцію, на диск буде записано більше даних і стане доступним, якщо ввімкнуто параметр тимчасового відпустки, ціною збільшення кількості записів на диск. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>This option sets the maximum amount of time a scan may take to complete. The value is in milliseconds. The value of 0 disables the limit. WARNING: disabling this limit or setting it too high may result allow scanning of certain files to lock up the scan‐ ning process/threads resulting in a Denial of Service. Default: 120000</source>
        <translation>Ця опція встановлює максимальний час сканування. Значення в мілісекундах. Значення 0 вимикає обмеження. ПОПЕРЕДЖЕННЯ: вимкнення цього обмеження або встановлення його занадто високого рівня може призвести до дозволу сканування певних файлів, щоб заблокувати процес/потоки сканування, що призведе до відмови в обслуговуванні. Типове значення: 120000</translation>
    </message>
    <message>
        <source>Sets the maximum amount of data to be scanned for each input file. Archives and other containers are recursively extracted and scanned up to this value. The size of an archive plus the sum of the sizes of all files within archive count toward the scan size. For example, a 1M uncompressed archive containing a single 1M in‐ ner file counts as 2M toward the max scan size. Warning: dis‐ abling this limit or setting it too high may result in severe damage to the system. Default: 400M</source>
        <translation>Встановлює максимальний обсяг даних для сканування для кожного вхідного файлу. Архіви та інші контейнери рекурсивно витягуються та скануються до цього значення. Розмір архіву плюс сума розмірів усіх файлів в архіві враховуються до розміру сканування. Наприклад, 1 Мб нестисненого архіву, що містить один внутрішній файл розміром 1 Мб, зараховується як 2 Мб до максимального розміру сканування. Попередження: вимкнення цього обмеження або встановлення його занадто високого рівня може призвести до серйозних пошкоджень системи. За замовчуванням: 400 млн</translation>
    </message>
    <message>
        <source>Files larger than this limit won&apos;t be scanned. Affects the input file itself as well as files contained inside it (when the input file is an archive, a document or some other kind of container). Warning: disabling this limit or setting it too high may result in severe damage to the system. Technical design limitations pre‐ vent ClamAV from scanning files greater than 2 GB at this time. Default: 100M</source>
        <translation>Файли, розмір яких перевищує це обмеження, не скануватимуться. Впливає на сам вхідний файл, а також на файли, що містяться в ньому (якщо вхідний файл є архівом, документом або іншим типом контейнера). Попередження: вимкнення цього обмеження або його встановлення занадто високим може призвести до серйозних пошкоджень системи. Технічні обмеження дизайну перешкоджають ClamAV сканувати файли розміром понад 2 ГБ наразі. За замовчуванням: 100M</translation>
    </message>
    <message>
        <source>Nested archives are scanned recursively, e.g. if a Zip archive contains a RAR file, all files within it will also be scanned. This options specifies how deeply the process should be contin‐ ued. Warning: setting this limit too high may result in severe damage to the system. Default: 17</source>
        <translation>Вкладені архіви скануються рекурсивно, напр. якщо Zip-архів містить файл RAR, усі файли в ньому також будуть проскановані. Цей параметр визначає, наскільки глибоко має бути продовжений процес. Попередження: встановлення занадто високого обмеження може призвести до серйозних пошкоджень системи. Типове значення: 17</translation>
    </message>
    <message>
        <source>Number of files to be scanned within an archive, a document, or any other kind of container. Warning: disabling this limit or setting it too high may result in severe damage to the system. Default: 10000</source>
        <translation>Кількість файлів для сканування в архіві, документі чи будь-якому іншому контейнері. Попередження: вимкнення цього обмеження або його встановлення занадто високим може призвести до серйозних пошкоджень системи. Типове значення: 10000</translation>
    </message>
    <message>
        <source>This option sets the maximum size of a file to check for embedded PE. Files larger than this value will skip the additional analysis step. Negative values are not allowed. Default: 40M</source>
        <translation>Цей параметр встановлює максимальний розмір файлу для перевірки наявності вбудованого PE. Файли, розмір яких перевищує це значення, пропустять додатковий крок аналізу. Негативні значення не допускаються. За замовчуванням: 40M</translation>
    </message>
    <message>
        <source>This option sets the maximum size of a HTML file to normalize. HTML files larger than this value will not be normalized or scanned. Negative values are not allowed. Default: 40M</source>
        <translation>Цей параметр встановлює максимальний розмір файлу HTML для нормалізації. Файли HTML, розмір яких перевищує це значення, не будуть нормалізовані чи скановані. Негативні значення не допускаються. За замовчуванням: 40M</translation>
    </message>
    <message>
        <source>This option sets the maximum size of a normalized HTML file to scan. HTML files larger than this value after normalization will not be scanned. Negative values are not allowed. Default: 8M</source>
        <translation>Цей параметр встановлює максимальний розмір нормалізованого файлу HTML для сканування. Файли HTML, розмір яких перевищує це значення, після нормалізації не скануватимуться. Негативні значення не допускаються. За замовчуванням: 8M</translation>
    </message>
    <message>
        <source>This option sets the maximum size of a script file to normalize. Script content larger than this value will not be normalized or scanned. Negative values are not allowed. Default: 20M</source>
        <translation>Цей параметр встановлює максимальний розмір файлу сценарію для нормалізації. Вміст сценарію, більший за це значення, не нормалізується чи сканується. Негативні значення не допускаються. За замовчуванням: 20M</translation>
    </message>
    <message>
        <source>This option sets the maximum size of a ZIP file to reanalyze type recognition. ZIP files larger than this value will skip the step to poten‐ tially reanalyze as PE. Negative values are not allowed. WARNING: setting this limit too high may result in severe damage or impact performance. Default: 1M</source>
        <translation>Цей параметр встановлює максимальний розмір ZIP-файлу для повторного аналізу розпізнавання типу. ZIP-файли, розмір яких перевищує це значення, пропускатимуть крок можливого повторного аналізу як PE. Негативні значення не допускаються. ПОПЕРЕДЖЕННЯ: встановлення цього обмеження занадто високе може призвести до серйозних пошкоджень або негативних наслідків. За замовчуванням: 1M</translation>
    </message>
    <message>
        <source>This option sets the maximum number of partitions of a raw disk image to be scanned. Raw disk images with more partitions than this value will have up to the value partitions scanned. Negative values are not allowed. WARNING: setting this limit too high may result in severe damage or impact performance. Default: 50</source>
        <translation>Цей параметр встановлює максимальну кількість розділів необробленого образу диска, який потрібно сканувати. Необроблені образи дисків із більшою кількістю розділів, ніж це значення, матимуть до сканованих розділів значення. Негативні значення не допускаються. ПОПЕРЕДЖЕННЯ: встановлення цього обмеження занадто високе може призвести до серйозних пошкоджень або негативних наслідків. Типове значення: 50</translation>
    </message>
    <message>
        <source>This option sets the maximum number of icons within a PE to be scanned. PE files with more icons than this value will have up to the value number icons scanned. Negative values are not allowed. WARNING: setting this limit too high may result in severe damage or impact performance. Default: 100</source>
        <translation>Цей параметр встановлює максимальну кількість піктограм у PE, які потрібно сканувати. PE-файли з більшою кількістю піктограм, ніж це значення, матимуть скановані піктограми зі значенням. Негативні значення не допускаються. ПОПЕРЕДЖЕННЯ: встановлення цього обмеження занадто високе може призвести до серйозних пошкоджень або негативних наслідків. Типове значення: 100</translation>
    </message>
    <message>
        <source>This option sets the maximum recursive calls to HWP3 parsing function. HWP3 files using more than this limit will be terminated and alert the user. Scans will be unable to scan any HWP3 attachments if the recur‐ sive limit is reached. Negative values are not allowed. WARNING: setting this limit too high may result in severe damage or impact performance. Default: 16</source>
        <translation>Цей параметр встановлює максимальну кількість рекурсивних викликів функції аналізу HWP3. Файли HWP3, які використовують більше цього ліміту, будуть закриті, про що користувач попередить. Сканування не зможе сканувати будь-які вкладення HWP3, якщо досягнуто обмеження рекурсивності. Негативні значення не допускаються. ПОПЕРЕДЖЕННЯ: встановлення цього обмеження занадто високе може призвести до серйозних пошкоджень або негативних наслідків. Типове значення: 16</translation>
    </message>
    <message>
        <source>This option sets the maximum calls to the PCRE match function during an instance of regex matching. Instances using more than this limit will be terminated and alert the user but the scan will continue. For more information on match_limit, see the PCRE documentation. Negative values are not allowed. WARNING: setting this limit too high may severely impact perfor‐ mance. Default: 10000</source>
        <translation>Цей параметр встановлює максимальну кількість викликів функції збігу PCRE під час збігу регулярного виразу. Екземпляри, які використовують більше, ніж це обмеження, буде припинено та сповіщено користувача, але сканування продовжиться. Додаткову інформацію про match_limit див. у документації PCRE. Негативні значення не допускаються. ПОПЕРЕДЖЕННЯ: встановлення занадто високого обмеження може серйозно вплинути на продуктивність. Типове значення: 10000</translation>
    </message>
    <message>
        <source>This option sets the maximum recursive calls to the PCRE match function during an instance of regex matching. Instances using more than this limit will be terminated and alert the user but the scan will continue. For more information on match_limit_recursion, see the PCRE docu‐ mentation. Negative values are not allowed and values &gt; PCREMatchLimit are superfluous. WARNING: setting this limit too high may severely impact perfor‐ mance. Default: 2000</source>
        <translation>Цей параметр встановлює максимальну кількість рекурсивних викликів функції збігу PCRE під час зіставлення регулярного виразу. Екземпляри, які використовують більше, ніж це обмеження, буде припинено та сповіщено користувача, але сканування продовжиться. Додаткову інформацію про match_limit_recursion див. у документації PCRE. Від’ємні значення не допускаються, а значення &gt; PCREMatchLimit є зайвими. ПОПЕРЕДЖЕННЯ: встановлення занадто високого обмеження може серйозно вплинути на продуктивність. Типове значення: 2000</translation>
    </message>
    <message>
        <source>This option sets the maximum filesize for which PCRE subsigs will be executed. Files exceeding this limit will not have PCRE subsigs executed unless a subsig is encompassed to a smaller buffer. Negative values are not allowed. Setting this value to zero disables the limit. WARNING: setting this limit too high or disabling it may severely impact performance. Default: 100M</source>
        <translation>Цей параметр встановлює максимальний розмір файлу, для якого виконуватимуться субсиги PCRE. Файли, що перевищують це обмеження, не виконуватимуть субсиг PCRE, якщо субсиг не буде включено до меншого буфера. Негативні значення не допускаються. Встановлення цього значення на нуль вимикає обмеження. ПОПЕРЕДЖЕННЯ: встановлення занадто високого обмеження або його вимкнення може серйозно вплинути на продуктивність. За замовчуванням: 100M</translation>
    </message>
    <message>
        <source>With this option you can exclude the root UID (0). Processes run under root will be able to access all files without triggering scans or permission denied events. Note that if clamd cannot check the uid of the process that gen‐ erated an on-access scan event (e.g., because OnAccessPrevention was not enabled, and the process already exited), clamd will per‐ form a scan. Thus, setting OnAccessExcludeRootUID is not guaran‐ teed to prevent every access by the root user from triggering a scan (unless OnAccessPrevention is enabled). Default: no</source>
        <translation>За допомогою цього параметра ви можете виключити кореневий UID (0). Процеси, запущені під адміністратором, матимуть доступ до всіх файлів без ініціювання сканування або подій відмови у дозволі. Зауважте, що якщо clamd не може перевірити uid процесу, який згенерував подію сканування під час доступу (наприклад, через те, що OnAccessPrevention не було ввімкнено, і процес уже завершив роботу), clamd виконає сканування. Таким чином, налаштування OnAccessExcludeRootUID не гарантує запобігання запуску сканування кожним доступом користувача root (якщо не ввімкнено OnAccessPrevention). За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Files larger than this value will not be scanned in on access. Default: 5M</source>
        <translation>Файли, розмір яких перевищує це значення, не скануватимуться під час доступу. За замовчуванням: 5M</translation>
    </message>
    <message>
        <source>Max number of scanning threads to allocate to the OnAccess thread pool at startup. These threads are the ones responsible for cre‐ ating a connection with the daemon and kicking off scanning after an event has been processed. To prevent clamonacc from consuming all clamd&apos;s resources keep this lower than clamd&apos;s max threads. Default: 5</source>
        <translation>Максимальна кількість потоків сканування для виділення пулу потоків OnAccess під час запуску. Ці потоки відповідають за встановлення з’єднання з демоном і запуск сканування після обробки події. Щоб запобігти споживанню clamonacc усіх ресурсів clamd, тримайте це значення нижче максимального значення потоків clamd. Типове значення: 5</translation>
    </message>
    <message>
        <source>Max amount of time (in milliseconds) that the OnAccess client should spend for every connect, send, and receive attempt when communicating with clamd via curl. Default: 5000 (5 seconds)</source>
        <translation>Максимальний час (у мілісекундах), який клієнт OnAccess повинен витрачати на кожну спробу підключення, надсилання та отримання під час спілкування з clamd через curl. За замовчуванням: 5000 (5 секунд)</translation>
    </message>
    <message>
        <source>Specifies a mount point (including all files and directories un‐ der it), which should be scanned on access. This option can be used multiple times. Default: disabled</source>
        <translation>Визначає точку монтування (включно з усіма файлами та каталогами), яку слід сканувати під час доступу. Цю опцію можна використовувати кілька разів. За замовчуванням: вимкнено</translation>
    </message>
    <message>
        <source>Disables the dynamic directory determination system which allows for recursively watching include paths. Default: no</source>
        <translation>Вимикає систему динамічного визначення каталогу, яка дозволяє рекурсивно переглядати включені шляхи. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Enables fanotify blocking when malicious files are found. Default: disabled</source>
        <translation>Вмикає блокування fanotify у разі виявлення шкідливих файлів. За замовчуванням: вимкнено</translation>
    </message>
    <message>
        <source>Number of times the OnAccess client will retry a failed scan due to connection problems (or other issues). Default: 0</source>
        <translation>Скільки разів клієнт OnAccess повторює невдалу спробу сканування через проблеми з підключенням (або інші проблеми). Типове значення: 0</translation>
    </message>
    <message>
        <source>When using prevention, if this option is turned on, any errors that occur during scanning will result in the event attempt be‐ ing denied. This could potentially lead to unwanted system behav‐ iour with certain configurations, so the client defaults this to off and prefers allowing access events in case of scan or connec‐ tion error. Default: no</source>
        <translation>Під час використання запобігання, якщо цей параметр увімкнено, будь-які помилки, що виникають під час сканування, призведуть до відхилення спроби події. Це потенційно може призвести до небажаної поведінки системи з певними конфігураціями, тому клієнт за замовчуванням вимикає це значення та надає перевагу дозволу подій доступу у разі сканування або помилки з’єднання. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Toggles extra scanning and notifications when a file or directory is created or moved. Requires the DDD system to kick-off extra scans. Default: no</source>
        <translation>Перемикає додаткове сканування та сповіщення під час створення або переміщення файлу чи каталогу. Потрібна система DDD для запуску додаткових сканувань. За замовчуванням: немає</translation>
    </message>
    <message>
        <source>Enable libclamav&apos;s debug messages</source>
        <translation>Увімкнути повідомлення про налагодження libclamav.</translation>
    </message>
    <message>
        <source>Be verbose</source>
        <translation>Будьте багатослівними.</translation>
    </message>
    <message>
        <source>Only print infected files</source>
        <translation>Друкуйте лише інфіковані файли.</translation>
    </message>
    <message>
        <source>Sound bell on virus detection</source>
        <translation>Звуковий дзвінок при виявленні вірусу.</translation>
    </message>
    <message>
        <source>Create temporary files for nested file scans that would otherwise be in-memory only</source>
        <translation>Створіть тимчасові файли для сканування вкладених файлів, які інакше були б лише в пам’яті.</translation>
    </message>
    <message>
        <source>Continue scanning within file after finding a match</source>
        <translation>Продовжуйте сканувати файл після того, як знайдете збіг.</translation>
    </message>
    <message>
        <source>Show filenames inside scanned archives</source>
        <translation>Показувати назви файлів у сканованих архівах.</translation>
    </message>
    <message>
        <source>Only output error messages</source>
        <translation>Виводити лише повідомлення про помилки.</translation>
    </message>
    <message>
        <source>Disable summary at end of scanning</source>
        <translation>Вимкнути зведення в кінці сканування.</translation>
    </message>
    <message>
        <source>Skip printing OK files</source>
        <translation>Пропустити друк файлів OK.</translation>
    </message>
    <message>
        <source>Do not remove temporary files</source>
        <translation>Не видаляйте тимчасові файли.</translation>
    </message>
    <message>
        <source>Scan subdirectories recursively</source>
        <translation>Сканувати підкаталоги рекурсивно.</translation>
    </message>
    <message>
        <source>Detect Possibly Unwanted Applications</source>
        <translation>Виявлення можливо небажаних програм.</translation>
    </message>
    <message>
        <source>Scan files and directories on other filesystems</source>
        <translation>Сканувати файли та каталоги в інших файлових системах.</translation>
    </message>
    <message>
        <source>Scan mail files</source>
        <translation>Сканувати поштові файли.</translation>
    </message>
    <message>
        <source>Detect structured data (SSN, Credit Card)</source>
        <translation>Виявлення структурованих даних (SSN, кредитна картка).</translation>
    </message>
    <message>
        <source>Enable URL signature-based phishing detection</source>
        <translation>Увімкнути виявлення фішингу на основі підпису URL-адреси.</translation>
    </message>
    <message>
        <source>Stop scanning as soon as a heuristic match is found</source>
        <translation>Припиніть сканування, як тільки буде знайдено евристичний збіг.</translation>
    </message>
    <message>
        <source>Enable email signature-based phishing detection</source>
        <translation>Увімкнути виявлення фішингу електронної пошти на основі підпису.</translation>
    </message>
    <message>
        <source>Heuristic alerts</source>
        <translation>Евристичні сповіщення.</translation>
    </message>
    <message>
        <source>Normalize html, script, and text files. Use normalize=no for yara compatibility</source>
        <translation>Нормалізація html, сценаріїв і текстових файлів. Використовуйте normalize=no для сумісності з yara.</translation>
    </message>
    <message>
        <source>Scan PE files</source>
        <translation>Сканувати файли PE.</translation>
    </message>
    <message>
        <source>Scan ELF files</source>
        <translation>Сканування файлів ELF.</translation>
    </message>
    <message>
        <source>Scan OLE2 containers</source>
        <translation>Сканування контейнерів OLE2.</translation>
    </message>
    <message>
        <source>Scan PDF files</source>
        <translation>Сканувати файли PDF.</translation>
    </message>
    <message>
        <source>Scan SWF files</source>
        <translation>Сканувати файли SWF.</translation>
    </message>
    <message>
        <source>Scan HTML files</source>
        <translation>Сканувати файли HTML.</translation>
    </message>
    <message>
        <source>Scan xml-based document files</source>
        <translation>Сканувати файли документів на основі xml.</translation>
    </message>
    <message>
        <source>Scan HWP3 files</source>
        <translation>Сканувати файли HWP3.</translation>
    </message>
    <message>
        <source>Scan archive files (supported by libclamav)</source>
        <translation>Сканувати архівні файли (підтримується libclamav).</translation>
    </message>
    <message>
        <source>Alert on broken executable files (PE &amp; ELF).</source>
        <translation>Сповіщення про пошкоджені виконувані файли (PE та ELF).</translation>
    </message>
    <message>
        <source>Scan OneNote files</source>
        <translation>Сканування файлів OneNote.</translation>
    </message>
    <message>
        <source>Scan image (graphics) files</source>
        <translation>Сканувати файли зображень (графіки).</translation>
    </message>
    <message>
        <source>Detect files by calculating image (graphics) fuzzy hashes</source>
        <translation>Виявляйте файли шляхом обчислення нечітких хешів зображень (графіки).</translation>
    </message>
    <message>
        <source>Alert on encrypted archives and documents</source>
        <translation>Сповіщення про зашифровані архіви та документи.</translation>
    </message>
    <message>
        <source>Alert on encrypted documents.</source>
        <translation>Сповіщення про зашифровані документи.</translation>
    </message>
    <message>
        <source>Alert on OLE2 files containing VBA macros</source>
        <translation>Сповіщення про файли OLE2, що містять макроси VBA.</translation>
    </message>
    <message>
        <source>Alert on encrypted archives</source>
        <translation>Сповіщення про зашифровані архіви та документи.</translation>
    </message>
    <message>
        <source>Alert on files that exceed max file size, max scan size, or max recursion limit</source>
        <translation>Сповіщення про файли, які перевищують максимальний розмір файлу, максимальний розмір сканування або максимальний ліміт рекурсії.</translation>
    </message>
    <message>
        <source>Alert on emails containing cloaked URLs</source>
        <translation>Сповіщення про електронні листи, що містять приховані URL-адреси.</translation>
    </message>
    <message>
        <source>Disable authenticode certificate chain verification in PE files</source>
        <translation>Вимкнути перевірку ланцюжка сертифікатів автентикоду в PE-файлах.</translation>
    </message>
    <message>
        <source>Alert on broken graphics files (JPEG, TIFF, PNG, GIF)</source>
        <translation>Сповіщення про пошкоджені графічні файли (JPEG, TIFF, PNG, GIF).</translation>
    </message>
    <message>
        <source>Alert on emails containing SSL mismatches in URLs</source>
        <translation>Сповіщення про електронні листи, які містять невідповідності SSL в URL-адресах.</translation>
    </message>
    <message>
        <source>Alert on raw DMG image files containing partition intersections</source>
        <translation>Сповіщення про необроблені файли зображень DMG, які містять перетини розділів.</translation>
    </message>
    <message>
        <source>Sets the group ownership on the unix socket. Default: the primary group of the user running clamd</source>
        <translation>Встановлює групу власників сокета Unix. За замовчуванням: основна група користувача, який запускає clamd.</translation>
    </message>
    <message>
        <source>Enables the SHUTDOWN command. Setting this to no prevents a client to stop clamd via the protocol. When disabled, clamd responds to this command with COMMAND UN‐ AVAILABLE. Default: yes</source>
        <translation>Вмикає команду SHUTDOWN. Якщо встановити значення «ні», клієнт не зможе зупинити clamd через протокол. Якщо вимкнено, clamd відповідає на цю команду COMMAND UN-AVAILABLE. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Enables the RELOAD command. Setting this to no prevents a client to reload the database. When disabled, clamd responds to this command with COMMAND UN‐ AVAILABLE. Default: yes</source>
        <translation>Вмикає команду RELOAD. Якщо встановити значення «ні», клієнт не зможе перезавантажити базу даних. Якщо вимкнено, clamd відповідає на цю команду COMMAND UNAVAILABLE. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Enables the VERSION command. Setting this to no prevents a client from querying version information. When disabled, clamd responds to this command with COMMAND UN‐ AVAILABLE. Default: yes</source>
        <translation>Вмикає команду VERSION. Якщо встановити значення «ні», клієнт не зможе запитувати інформацію про версію. Якщо вимкнено, clamd відповідає на цю команду COMMAND UN-AVAILABLE. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Enables the STATS command. Setting this to no prevents a client from querying statistics. When disabled, clamd responds to this command with COMMAND UN‐ AVAILABLE. Default: yes</source>
        <translation>Вмикає команду STATS. Якщо встановити значення «ні», клієнт не зможе запитувати статистику. Якщо вимкнено, clamd відповідає на цю команду COMMAND UN-AVAILABLE. За замовчуванням: так</translation>
    </message>
    <message>
        <source>Exclude a specific PUA category. This directive can be used mul‐ tiple times. See https://docs.clamav.net/faq/faq-pua.html for the complete list of PUA categories. Default: disabled</source>
        <translation>Виключити певну категорію потенційно потенційно небезпечних застосувань (PUA). Цю директиву можна використовувати кілька разів. Повний список категорій потенційно небезпечних застосувань див. за посиланням https://docs.clamav.net/faq/faq-pua.html. За замовчуванням: вимкнено.</translation>
    </message>
    <message>
        <source>With this option you can exclude specific UIDs. Processes with these UIDs will be able to access all files without triggering scans or permission denied events. This option can be used multiple times (one per line). Note: using a value of 0 on any line will disable this option en‐ tirely. To exclude the root UID (0) please enable the OnAccessEx‐ cludeRootUID option. Also note that if clamd cannot check the uid of the process that generated an on-access scan event (e.g., because OnAccessPreven‐ tion was not enabled, and the process already exited), clamd will perform a scan. Thus, setting OnAccessExcludeUID is not guaran‐ teed to prevent every access by the specified uid from triggering a scan (unless OnAccessPrevention is enabled). Default: disabled</source>
        <translation>За допомогою цієї опції ви можете виключити певні UID. Процеси з цими UID зможуть отримувати доступ до всіх файлів без запуску сканування або подій відмови в доступі. Цю опцію можна використовувати кілька разів (по одному на рядок). Примітка: використання значення 0 у будь-якому рядку повністю вимкне цю опцію. Щоб виключити кореневий UID (0), увімкніть опцію OnAccessExcludeRootUID. Також зверніть увагу, що якщо clamd не може перевірити uid процесу, який генерував подію сканування під час доступу (наприклад, тому що OnAccessPrevention не було ввімкнено, а процес вже завершився), clamd виконає сканування. Таким чином, встановлення OnAccessExcludeUID не гарантує запобігання кожному доступу зазначеного uid запуску сканування (якщо OnAccessPrevention не ввімкнено). За замовчуванням: вимкнено</translation>
    </message>
    <message>
        <source>This option allows exclusions via user names when using the on- access scanning client. It can be used multiple times, and has the same potential race condition limitations of the OnAccessEx‐ cludeUID option. Default: disabled</source>
        <translation>Цей параметр дозволяє виключення за іменами користувачів під час використання клієнта сканування під час доступу. Його можна використовувати кілька разів і він має ті ж потенційні обмеження щодо умов змагання, що й параметр OnAccessExcludeUID. За замовчуванням: вимкнено.</translation>
    </message>
</context>
</TS>
