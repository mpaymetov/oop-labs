set PROGRAM="%~1"

%PROGRAM%
if NOT ERRORLEVEL 1 GOTO err

rem 
%PROGRAM% matrix1.txt matrix2.txt
if NOT ERRORLEVEL 1 GOTO err

rem 
%PROGRAM% matrix_er1.txt matrix_in2.txt 
if NOT ERRORLEVEL 1 GOTO err

rem 
%PROGRAM% matrix_in1.txt matrix_er2.txt
if NOT ERRORLEVEL 1 GOTO err

rem 
%PROGRAM% matrix_in1.txt matrix_in2.txt > matrix_out.txt
if ERRORLEVEL 1 GOTO err
fc.exe matrix_out.txt matrix_out_et.txt > nul
if ERRORLEVEL 1 GOTO err

echo OK
exit 0

:err
echo Program testing failed
exit 1