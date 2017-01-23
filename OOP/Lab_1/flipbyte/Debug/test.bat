set PROGRAM=flipbyte.exe
echo %PROGRAM%

%PROGRAM% "6"> "%TEMP%\Include_value.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\Include_value.txt" Include_value.txt
if ERRORLEVEL 1 goto err

%PROGRAM% "256"> "%TEMP%\not_include_value.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\not_include_value" not_include_value.txt
if ERRORLEVEL 1 goto err

%PROGRAM% "fff"> "%TEMP%\not_number.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\not_number.txt" not_number.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1