set PROGRAM="%~1"

%PROGRAM% > nul

rem 
if NOT ERRORLEVEL 1 GOTO err

rem
%PROGRAM% 6
if ERRORLEVEL 1 GOTO err

echo OK
exit 0

:err
echo Program testing failed
exit 1