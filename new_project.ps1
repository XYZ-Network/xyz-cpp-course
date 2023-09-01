param (
    [Parameter(Mandatory=$true)]
    [string]$SourceProjectDir,

    [Parameter(Mandatory=$true)]
    [string]$NewProjectName
)

# Check if sln file exist in current directory
if (-not (Test-Path "*.sln")) {
    Write-Error ".sln file was not found in current directory"
    exit
}

# Copy project directory
$destDir = Join-Path (Get-Location) $NewProjectName
Copy-Item -Recurse -Force $SourceProjectDir $destDir

# Rename .csproj.*
$sourceProjFile = Get-ChildItem -Path $SourceProjectDir -Filter "*.vcxproj" | Select-Object -First 1
Get-ChildItem -Path $destDir -Filter "*.vcxproj.*" | ForEach-Object {
    $newName = $_.Name -replace $sourceProjFile.BaseName, $NewProjectName
    Rename-Item -Path $_.FullName -NewName $newName
}

# Replace project name in .csproj
$targetProjFile = Get-ChildItem -Path $destDir -Filter "*.vcxproj" | Select-Object -First 1
$newProjectGuid = [guid]::NewGuid().ToString().ToUpper()
[xml]$projFileContent = Get-Content $sourceProjFile.FullName
$projFileContent.Project.PropertyGroup[0].ProjectGuid = $newProjectGuid
$projFileContent.Project.PropertyGroup[0].ProjectName = $NewProjectName
$projFileContent.Project.PropertyGroup[0].RootNamespace = $NewProjectName
$projFileContent.Save($targetProjFile.FullName)

# Add new project to .sln 
$slnContent = Get-Content "*.sln"

$projectExists = $slnContent | Select-String -Pattern $NewProjectName

if (-not $projectExists) {
    $newProject = 
@"
Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "$NewProjectName", "$NewProjectName\$NewProjectName.vcxproj", "{$newProjectGuid}"
EndProject
"@

    $newContent = $slnContent -replace "(^Global$)", "$newProject`r`nGlobal$1"
    Set-Content -Path "*.sln" -Value $newContent
}



Write-Host "Project $NewProjectName has been created!" -ForegroundColor Green
