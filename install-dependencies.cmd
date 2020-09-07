:: WARNING MUST BE CALLED FROM VS DevTools CMD Prompt
@ECHO off

IF EXIST dependencies (
	RMDIR /S /Q dependencies
)

git submodule update --recursive --init

IF EXIST dependencies\lib\librocket-deps.lib ( EXIT ) ELSE (
  CD dependencies
  @call build.cmd
  CD ..
  MD install >NUL
  XCOPY /S /Q /H /Y dependencies\install\* install\
  RMDIR /S /Q dependencies
  RENAME install dependencies
)

ECHO ///-- Ready to launch --///