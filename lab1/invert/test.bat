set PROGRAM="%~1"

%PROGRAM%

rem 
if NOT ERRORLEVEL 1 GOTO err

rem 
%PROGRAM% matrix_in1.txt > matrix_out_1.txt
if ERRORLEVEL 1 GOTO err
fc.exe matrix_out_1.txt matrix_out_et1.txt > nul
if ERRORLEVEL 1 GOTO err

rem 
%PROGRAM% matrix_in2.txt > matrix_out_2.txt"
if ERRORLEVEL 1 GOTO err
fc.exe matrix_out_2.txt matrix_out_et2.txt
if ERRORLEVEL 1 GOTO err

echo OK
exit 0

:err
echo Program testing failed
exit 1