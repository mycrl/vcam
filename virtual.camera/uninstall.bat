@echo off
@cd /d "%~dp0"

regsvr32.exe /u /s "%~dp0build\Debug\virtualcam-module64.dll"
