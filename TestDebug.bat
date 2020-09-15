@echo off
SET INTERPETER="x64/Debug/Rockstar.exe"
SET TESTS="Tester/tests"
python Tester/tester.py %INTERPETER% %TESTS%
pause