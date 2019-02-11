rem %1 - значение первого аргумента командной строки bat-файла (какой он есть)
rem %~1 - значение первого аргумента командной строки bat-файла с удалением обрамляющих кавычек (если они были)

rem Переменная PROGRAM будет хранить первый аргумент командной строки заключённый в кавычки
set PROGRAM="%~1"

:: Путь к файлу с выходными данными программы
set OUT="%TEMP%\out.txt"

rem При запуске без параметров ожидается ненулевой код возврата
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

::
%PROGRAM% 10 10 12 > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "out.txt" > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 16 10 1F > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "out2.txt"
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1