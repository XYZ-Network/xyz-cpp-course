set ProjectName=%1
powershell.exe -ExecutionPolicy Bypass -File new_project.ps1 -NewProjectName %ProjectName% -SourceProjectDir "SFMLTemplate"
