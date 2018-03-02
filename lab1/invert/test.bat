set PROGRAM="%~1"

%PROGRAM%

rem 
if NOT ERRORLEVEL 1 GOTO err

rem 
%PROGRAM% matrix.txt
if ERRORLEVEL 1 GOTO err
rem fc.exe "%TEMP%\fox.txt" test-data\fox.txt >nul
rem if ERRORLEVEL 1 GOTO err

echo OK
exit 0

:err
echo Program testing failed
exit 1