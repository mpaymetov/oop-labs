set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 GOTO err

::неверный параметр шифрования
%PROGRAM% recrypt input.txt output.txt 20 > nul
if NOT ERRORLEVEL 1 GOTO err

::несуществующий входной файл
%PROGRAM% crypt input1.txt output.txt 20 > nul
if NOT ERRORLEVEL 1 GOTO err

::неправильное имя выходного файла
%PROGRAM% crypt input.txt output*.txt 20 > nul
if NOT ERRORLEVEL 1 GOTO err

::неверный ключ шифрования
%PROGRAM% crypt input.txt output.txt 283 > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% crypt input.txt output.txt 20 > nul
if ERRORLEVEL 1 GOTO err
%PROGRAM% decrypt output.txt decrypt.txt 20 > nul
if ERRORLEVEL 1 GOTO err
fc.exe /b input.txt decrypt.txt > nul
if ERRORLEVEL 1 GOTO err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1