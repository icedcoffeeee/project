@echo off
goto :init

:setup
  set OUT_DIR=build
  set OUT_EXE=%OUT_DIR%/example.exe
  set INCLUDES=/Iimgui /Iimgui\backends /IC:\tools\opencv\build\include
  set SOURCES=*.cpp imgui\backends\imgui_impl_opengl3.cpp imgui\backends\imgui_impl_win32.cpp imgui\imgui*.cpp
  set LIBS=/LIBPATH:C:\tools\opencv\build\x64\vc16\lib /LIBPATH:C:\tools\opencv\build\x64\vc16\bin opengl32.lib opencv_world4100.lib

  if defined RELEASE (set MULTI=/MD) else set MULTI=/MT

  set CMD=cl /nologo /Zi %MULTI% /EHsc /std:c++17 /utf-8 %INCLUDES% /D UNICODE /D _UNICODE %SOURCES% /Fe%OUT_EXE% /Fo%OUT_DIR%/ /link %LIBS%
  goto :run

:help
  echo Building project. Requires MSVC 'cl' compiler.
  echo Run with '-r' to run after building.
  echo Run with '-c' to generate clangd config.
  echo Run with '-R' to create release build.
  echo.
  goto :setup

:init
  set "args="
  goto :parse

:parse
  if "%~1" == "-r" set "RUN=yes"
  if "%~1" == "-c" set "CLANGD=yes"
  if "%~1" == "-R" set "RELEASE=yes"
  if "%~1" == "" (
    if "%args%"==""  (goto :help) else (goto :setup)
  )

  set "args=%args%%~1"
  shift
  goto :parse

:run
  if defined CLANGD (goto :clangd) else (
    %CMD%
    if defined RUN "./%OUT_EXE%"
  )
  exit /B

:clangd
  set i=0
  setlocal EnableDelayedExpansion
  echo CompileFlags: > .clangd
  for %%c in (%CMD%) do (
    set /A i+=1
    if "!i!" == "1" (
      echo(  Compiler: >> .clangd
      echo(    %%c >> .clangd
    ) else if "!i!" == "2" (
        echo(  Add: [ >> .clangd
    ) else (
      echo(    %%c, >> .clangd
    )
  )
  echo(  ] >> .clangd
  exit /B
