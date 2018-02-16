set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 256
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% Hello
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 1 > %temp%\1.txt
fc.exe 1.txt %temp%\1.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 2 > %temp%\2.txt
fc.exe 2.txt %temp%\2.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 4 > %temp%\4.txt
fc.exe 4.txt %temp%\4.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 8 > %temp%\8.txt
fc.exe 8.txt %temp%\8.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 16 > %temp%\16.txt
fc.exe 16.txt %temp%\16.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 32 > %temp%\32.txt
fc.exe 32.txt %temp%\32.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 64 > %temp%\64.txt
fc.exe 64.txt %temp%\64.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 128 > %temp%\128.txt
fc.exe 128.txt %temp%\128.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 6
if ERRORLEVEL 1 GOTO err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1