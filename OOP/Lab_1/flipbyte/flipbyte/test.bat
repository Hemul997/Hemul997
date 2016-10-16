set PROGRAM="%~1"
echo %PROGRAM%

%PROGRAM% "6"> "%TEMP%\Include_value_first.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\Include_value.txt" Include_value.txt
if ERRORLEVEL 1 goto err

rem -1, 0, 1, 128, 255, 256, gf, ""
%PROGRAM% "0"> "%TEMP%\Include_value_second.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\Include_value.txt" Include_value.txt
if ERRORLEVEL 1 goto err

%PROGRAM% "-1"
if NOT ERRORLEVEL 1 goto err

%PROGRAM% "128"> "%TEMP%\include_value_third.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\include_value_third.txt" Include_value_third.txt
if ERRORLEVEL 1 goto err

%PROGRAM% "1"> "%TEMP%\include_value_fourth.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\include_value_fourth.txt" Include_value_fourth.txt
if ERRORLEVEL 1 goto err

%PROGRAM% "255">"%TEMP%\include_value_fifth.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\Include_value_fifth.txt" Include_value_fifth.txt
if ERRORLEVEL 1 goto err

%PROGRAM% "256"
if NOT ERRORLEVEL 1 goto err


%PROGRAM% "gf"
if NOT ERRORLEVEL 1 goto err

%PROGRAM% ""
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1