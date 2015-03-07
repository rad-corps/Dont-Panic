set PATH=%PATH%;C:\Program Files (x86)\7-Zip\
for /f "delims=" %%a in ('wmic OS Get localdatetime  ^| find "."') do set dt=%%a
set datestamp=%dt:~0,8%
set timestamp=%dt:~8,6%
set YYYY=%dt:~0,4%
set MM=%dt:~4,2%
set DD=%dt:~6,2%
set HH=%dt:~8,2%
set Min=%dt:~10,2%
set Sec=%dt:~12,2%

set stamp=%YYYY%-%MM%-%DD%--%HH%-%Min%
set dirName="DontPanic-%stamp%"

md ".\BuildOutput\%dirName%"
md ".\BuildOutput\%dirName%\resources"

Xcopy ".\Release\DontPanic2.exe" ".\BuildOutput\%dirName%" /y
XCopy ".\resources" ".\BuildOutput\%dirName%\resources" /y /i /s /e
XCopy ".\lib\*.dll" ".\BuildOutput\%dirName%" /y /i /s /e

7z a ".\BuildOutput\%dirName%.zip" ".\BuildOutput\%dirName%\"

RD /S /Q ".\BuildOutput\%dirName%"

XCopy ".\BuildOutput\%dirName%.zip" "G:\Dropbox2\Dropbox\DontPanic" /y 

pause