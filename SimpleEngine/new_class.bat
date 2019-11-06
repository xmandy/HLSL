@echo off
cd Samples\EngineHelper
set /p args=project,class:
echo %args%
python ClassTemplate.py -args %args%
