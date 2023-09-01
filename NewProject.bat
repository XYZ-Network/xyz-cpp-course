set ProjectName=NewProject
powershell.exe -ExecutionPolicy Bypass -File new_project.ps1 -NewProjectName %ProjectName% -SourceProjectDir "SFMLTemplate"
