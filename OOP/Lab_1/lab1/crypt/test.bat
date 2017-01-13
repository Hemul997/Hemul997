set PROGRAM="%~1"

rem check the number of arguments
%PROGRAM% crypt in.bin %TEMP%\out.bin
if %ERRORLEVEL% EQU 0 goto err
fc.exe %TEMP%\out.bin in.bin 
if %ERRORLEVEL% EQU 0 goto err

rem check opening a nonexistent file      
%PROGRAM% crypt fail.bin %TEMP%\out.bin 34
if %ERRORLEVEL% EQU 0 goto err
fc.exe %TEMP%\out.bin fail.bin 
if %ERRORLEVEL% EQU 0 goto err

rem check opening an empty file          
%PROGRAM% crypt empty.bin %TEMP%\out.bin 34
if %ERRORLEVEL% EQU 0 goto err
fc.exe %TEMP%\out.bin empty.bin 
if %ERRORLEVEL% EQU 1 goto err
                              

rem Operation Validation        
%PROGRAM% cry in.bin %TEMP%\out.bin 34
if %ERRORLEVEL% EQU 0 goto err
fc.exe %TEMP%\out.bin in.bin 
if %ERRORLEVEL% EQU 0 goto err


rem Key Validation         
%PROGRAM% crypt in.bin %TEMP%\out.bin 340
if %ERRORLEVEL% EQU 0 goto err
fc.exe %TEMP%\out.bin in.bin 
if %ERRORLEVEL% EQU 0 goto err


rem successful test          
%PROGRAM% crypt in.bin %TEMP%\outSuccess.bin 34
if %ERRORLEVEL% EQU 1 goto err
fc.exe %TEMP%\outSuccess.bin in.bin 
if %ERRORLEVEL% EQU 0 goto err
%PROGRAM% decrypt %TEMP%\outSuccess.bin out.bin 34
if %ERRORLEVEL% EQU 1 goto err
fc.exe  out.bin in.bin 
if %ERRORLEVEL% EQU 1 goto err


rem filled test          
%PROGRAM% crypt in.bin %TEMP%\outFilled.bin hi
if %ERRORLEVEL% EQU 0 goto err
fc.exe %TEMP%\outFilled.bin in.bin 
if %ERRORLEVEL% EQU 0 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1