set PROGRAM="%~1"

:: запуск без параметров
%PROGRAM% > nul
if NOT ERRORLEVEL 1 GOTO err

:: неверное имя входного файла
%PROGRAM% labyrinth.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: неверное имя выходного файла
%PROGRAM% labyrinth-1.txt output*.txt > nul
if NOT ERRORLEVEL 1 GOTO err

%PROGRAM% labyrinth-1.txt output.txt > nul
if ERRORLEVEL 1 GOTO err
fc.exe labyrinth-2.txt output.txt >nul
if ERRORLEVEL 1 goto err

%PROGRAM% labyrinth-3.txt output.txt > nul
if ERRORLEVEL 1 GOTO err
fc.exe labyrinth-3-check.txt output.txt > nul
if ERRORLEVEL 1 goto err

:: несколько стартовых точек
%PROGRAM% labyrinth-mlA.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: несколько финишных точек
%PROGRAM% labyrinth-mlB.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: без стартовых точек
%PROGRAM% labyrinth-noA.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: без финишных точек
%PROGRAM% labyrinth-noB.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: без возможного пути
%PROGRAM% labyrinth-noWay.txt output.txt > nul
if ERRORLEVEL 1 GOTO err
fc.exe labyrinth-noWay.txt output.txt > nul
if ERRORLEVEL 1 goto err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1
