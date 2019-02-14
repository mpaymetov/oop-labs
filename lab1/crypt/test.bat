set PROGRAM="%~1"

%PROGRAM% > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% recrypt input.txt output.txt 20 > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% crypt input.txt output.txt 283 > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% crypt input1.txt output.txt 20 > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% crypt input.txt out*put.txt 20 > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% crypt input.txt output.txt 20 > nul
if ERRORLEVEL 1 GOTO err
%PROGRAM% decrypt output.txt decrypt.txt 20 > nul
if ERRORLEVEL 1 GOTO err
fc.exe input.txt decrypt.txt > nul
if ERRORLEVEL 1 GOTO err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1