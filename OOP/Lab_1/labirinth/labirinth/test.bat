set PROGRAM="%~1"

rem ��������� ���������, ����� �� �����
rem �� ���������� ���-�� ����������
%PROGRAM% unknow.txt
if NOT ERRORLEVEL 1 goto err

rem ��������� ���������, ����� ����������� ������� ��� �����
%PROGRAM% unknow.txt unknow.txt
if NOT ERRORLEVEL 1 goto err

rem ��� �������� �����
%PROGRAM% Input\no_end_point.txt Output\no_end_point_output.txt
if NOT ERRORLEVEL 1 goto err

rem ��� ��������� �����
%PROGRAM% Input\no_start_point.txt Output\no_start_point_output.txt
if NOT ERRORLEVEL 1 goto err

rem ��� ����
%PROGRAM% Input\no_path.txt Output\no_path_output.txt
if ERRORLEVEL 1 goto err

rem ������� ���������� ����
%PROGRAM% Input\labirinth_test.txt Output\labirinth_test_output.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1