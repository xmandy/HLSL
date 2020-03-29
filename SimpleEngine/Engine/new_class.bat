@echo off
cd Samples\EngineHelper
set /p args=project,[group,]class:
echo %args%
python ClassTemplate.py -args %args%
pause