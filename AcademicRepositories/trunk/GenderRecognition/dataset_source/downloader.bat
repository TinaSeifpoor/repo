@echo off
FOR /F "tokens=*" %%i IN (plain_list_females.txt) DO call:download "%%i" "D:\Dropbox\Gender\females"
FOR /F "tokens=*" %%i IN (plain_list_males.txt)   DO call:download "%%i" "D:\Dropbox\Gender\males"
echo Finished
pause
exit

::--------------------------------------------------------
:download
MD %~2 2> nul
echo %~1
call "./TextToImage/TextToImage.exe" "%~1" %~2 100000 1>nul 2>&1
goto:eof 