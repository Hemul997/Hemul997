set PROGRAM="%~1"

rem проверяем программу, когда на входе
rem не правильное кол-во аргументов
%PROGRAM% unknow.txt
if NOT ERRORLEVEL 1 goto err

rem проверяем программу, когда неправильно введено имя файла
%PROGRAM% unknow.txt unknow.txt
if NOT ERRORLEVEL 1 goto err

rem нет конечной точки
%PROGRAM% Input\no_end_point.txt Output\no_end_point_output.txt
if NOT ERRORLEVEL 1 goto err

rem нет начальной точки
%PROGRAM% Input\no_start_point.txt Output\no_start_point_output.txt
if NOT ERRORLEVEL 1 goto err

rem нет пути
%PROGRAM% Input\no_path.txt Output\no_path_output.txt
if ERRORLEVEL 1 goto err

rem находим кратчайший путь
%PROGRAM% Input\labirinth_test.txt Output\labirinth_test_output.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1