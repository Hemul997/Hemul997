set PROGRAM="%~1" 

%PROGRAM% Input\Matrix.txt Output\out1.txt
if %ERRORLEVEL% EQU 1 goto err
fc.exe Output\out1.txt References\BO1.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% Input\Matrix2.txt Output\out2.txt
if %ERRORLEVEL% EQU 1 goto err
fc.exe Output\out2.txt References\BO2.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% Input\Matrix3.txt Output\out3.txt
if %ERRORLEVEL% EQU 0 goto err
fc.exe Output\out3.txt References\BO3.txt
if %ERRORLEVEL% EQU 1 goto err

%PROGRAM% Input\Matrix4.txt Output\out4.txt
if %ERRORLEVEL% EQU 1 goto err
fc.exe Output\out4.txt References\BO4.txt
if %ERRORLEVEL% EQU 1 goto err

echo Program testing succeeded 
exit 0 

:err 
echo Program testing failed 
exit 1
