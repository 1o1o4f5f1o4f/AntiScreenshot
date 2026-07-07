@echo off
if not exist build mkdir build

echo ----- Building resources -----
windres src\Resource.rc -o build\Resource.o || exit /b 1

echo ----- Building executable -----
g++ src\main.cpp build\Resource.o -o build\antiscreenshot.exe -mwindows -static -Wall -Oz || exit /b 1

echo ----- Running executable -----
build\antiscreenshot.exe