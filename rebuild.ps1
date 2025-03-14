# Delete the build directory if it exists
if (Test-Path -Path "build") {
    Remove-Item -Path "build" -Recurse -Force
}

# Recreate the build directory and navigate into it
New-Item -Path "build" -ItemType Directory
Set-Location -Path "build"

# Reconfigure the project with Debug mode
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Build the project
cmake --build .

# Run tests if the build succeeded
if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful. Running tests..."
    
    # Run the test executable
    if (Test-Path -Path "Debug/json_parser_tests.exe") {
        & "./Debug/json_parser_tests.exe"
    } else {
        # Try alternative path format that some CMake generators might use
        if (Test-Path -Path "json_parser_tests.exe") {
            & "./json_parser_tests.exe"
        } else {
            Write-Host "Error: Test executable not found." -ForegroundColor Red
        }
    }
} else {
    Write-Host "Build failed. Tests not run." -ForegroundColor Red
}

# Return to the original directory
Set-Location -Path ".."



#powershell version of build_project.sh   