@echo off

pushd ..

@set dir_bin=    build\debug\bin
@set dir_lib=    build\debug\lib
@set dir_obj=    build\debug\obj

@set cl_in=      engine\src\ifb-engine.cpp
@set cl_out=     /Fo:build\debug\obj\ItFliesBy.Engine.obj
@set cl_include= /Iengine\include /Iengine\internal /Iengine\src /Iengine\src\core /Iengine\src\file /Iengine\src\memory /Iengine\src\asset /Isld\include /Isld\vcpkg_installed\x64-windows\include
@set cl_flags=   /nologo /c /MD /LD /Z7 /EHs- /std:c++17 /Od /D_HAS_EXCEPTIONS=0

@set link_in=    ItFliesBy.Engine.obj user32.lib kernel32.lib SLD.Win32.lib Gdi32.lib imgui.lib opengl32.lib __imp_GetOpenFileNameA
@set link_out=   /OUT:build\debug\bin\ItFliesBy.Engine.dll /IMPLIB:build\debug\lib\ItFliesBy.Engine.lib
@set link_path=  /LIBPATH:build\debug\obj /LIBPATH:build\debug\lib /LIBPATH:sld\build\debug\lib /LIBPATH:sld\vcpkg_installed\x64-windows\lib
@set link_flags= /nologo /SUBSYSTEM:WINDOWS /DEBUG /DLL

@set cmd_cl=     cl.exe   %cl_in%      %cl_out%    %cl_include% %cl_flags%
@set cmd_link=   link.exe %link_flags% %link_path% %link_in%    %link_out%

IF NOT EXIST %dir_bin% mkdir %dir_bin%
IF NOT EXIST %dir_lib% mkdir %dir_lib%
IF NOT EXIST %dir_obj% mkdir %dir_obj%

call %cmd_cl%
call %cmd_link%

popd
