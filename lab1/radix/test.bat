rem %1 - �������� ������� ��������� ��������� ������ bat-����� (����� �� ����)
rem %~1 - �������� ������� ��������� ��������� ������ bat-����� � ��������� ����������� ������� (���� ��� ����)

rem ���������� PROGRAM ����� ������� ������ �������� ��������� ������ ����������� � �������
set PROGRAM="%~1"

:: ���� � ����� � ��������� ������� ���������
set OUT="%TEMP%\out.txt"

rem ��� ������� ��� ���������� ��������� ��������� ��� ��������
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

::
%PROGRAM% 10 10 12 > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "out.txt" > nul
if ERRORLEVEL 1 goto err

%PROGRAM% 16 10 1F > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% "out2.txt"
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1