set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 256
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% Hello
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% 6
if ERRORLEVEL 1 GOTO err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1