set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 256
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% Hello World
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% test_in1.txt test_out1.txt
if ERRORLEVEL 1 GOTO err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1