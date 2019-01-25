msbuild rpn.vcxproj /t:Rebuild /p:Configuration=Release /p:Platform=x64
if errorlevel=1 goto end
copy .\x64\Release\rpn.exe ..\x64\release
:end