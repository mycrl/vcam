@echo off
@cd /d "%~dp0"

regsvr32.exe /i /s "%~dp0build\Debug\virtualcam-module64.dll"