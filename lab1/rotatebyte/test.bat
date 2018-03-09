set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 256 2 R
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 3 256 L
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 3 2 H
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 3 2 L > test_out1.txt
if ERRORLEVEL 1 GOTO err
fc.exe test_out1.txt test_et1.txt > nul
if ERRORLEVEL 1 GOTO err

%PROGRAM% 192 4 R > test_out2.txt
if ERRORLEVEL 1 GOTO err
fc.exe test_out2.txt test_et2.txt > nul
if ERRORLEVEL 1 GOTO err

%PROGRAM% 5 8 R > test_out3.txt
if ERRORLEVEL 1 GOTO err
fc.exe test_out3.txt test_et3.txt > nul
if ERRORLEVEL 1 GOTO err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1