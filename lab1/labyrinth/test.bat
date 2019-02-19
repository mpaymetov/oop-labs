set PROGRAM="%~1"

:: ������ ��� ����������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 GOTO err

:: �������� ��� �������� �����
%PROGRAM% labyrinth.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: �������� ��� ��������� �����
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

:: ��������� ��������� �����
%PROGRAM% labyrinth-mlA.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: ��������� �������� �����
%PROGRAM% labyrinth-mlB.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: ��� ��������� �����
%PROGRAM% labyrinth-noA.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: ��� �������� �����
%PROGRAM% labyrinth-noB.txt output.txt > nul
if NOT ERRORLEVEL 1 GOTO err

:: ��� ���������� ����
%PROGRAM% labyrinth-noWay.txt output.txt > nul
if ERRORLEVEL 1 GOTO err
fc.exe labyrinth-noWay.txt output.txt > nul
if ERRORLEVEL 1 goto err

echo OK
exit /B 0

:err
echo Program testing failed
exit 1
