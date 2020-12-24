@ECHO OFF


IF NOT EXIST dependencies\lib\librocket-deps.lib (
	@call install-dependencies.cmd
)

IF EXIST target (
	RMDIR /S /Q target
)
MKDIR target

CD target

cmake -D CMAKE_INSTALL_PREFIX=distribution ../src
devenv rocket.sln /build Release

