set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 256 > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% Hello > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 1 > %temp%\1.txt
if ERRORLEVEL 1 GOTO err
fc.exe 1.txt %temp%\1.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 3 > %temp%\3.txt
if ERRORLEVEL 1 GOTO err
fc.exe 3.txt %temp%\3.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 7 > %temp%\7.txt
if ERRORLEVEL 1 GOTO err
fc.exe 7.txt %temp%\7.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 15 > %temp%\15.txt
if ERRORLEVEL 1 GOTO err
fc.exe 15.txt %temp%\15.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 31 > %temp%\31.txt
if ERRORLEVEL 1 GOTO err
fc.exe 31.txt %temp%\31.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 63 > %temp%\63.txt
if ERRORLEVEL 1 GOTO err
fc.exe 63.txt %temp%\63.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 127 > %temp%\127.txt
if ERRORLEVEL 1 GOTO err
fc.exe 127.txt %temp%\127.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 255 > %temp%\255.txt
if ERRORLEVEL 1 GOTO err
fc.exe 255.txt %temp%\255.txt
if ERRORLEVEL 1 GOTO err

%PROGRAM% 147 > %temp%\147.txt
if ERRORLEVEL 1 GOTO err
fc.exe 147.txt %temp%\147.txt
if ERRORLEVEL 1 GOTO err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1