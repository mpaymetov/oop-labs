set PROGRAM="%~1"

%PROGRAM% input.txt
if ERRORLEVEL 1 GOTO err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1