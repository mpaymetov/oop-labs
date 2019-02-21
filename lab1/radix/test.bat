rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

:: Путь к файлу с выходными данными программы
set OUT="%TEMP%\out.txt"

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 10 12 > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "out.txt" > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 16 10 1F > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "out2.txt" > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 10 10 1F > %OUT%
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 1 10 1F > %OUT%
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 37 17 > %OUT%
if NOT ERRORLEVEL 1 goto err

::sourse radix - stoi argument out of range
%PROGRAM% 4294967296 10 1F > %OUT%
if NOT ERRORLEVEL 1 goto err

::sourse radix - not a number
%PROGRAM% ab 10 6 > %OUT%
if NOT ERRORLEVEL 1 goto err

::UMAX_INT
%PROGRAM% 16 10 FFFFFFFF > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "umaxint.txt" > nul
if ERRORLEVEL 1 goto err

::-UMAX_INT
%PROGRAM% 16 10 -FFFFFFFF > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "mumaxint.txt" > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 16 10 FFFFFFFF1 > %OUT%
if NOT ERRORLEVEL 1 goto err

%PROGRAM% 10 8 -35 > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "m43.txt" > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 10 8 0 > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "out3.txt" > nul
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1