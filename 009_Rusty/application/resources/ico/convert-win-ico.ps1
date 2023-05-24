Write-Host "Creating icon for the application from icon-*.png."
Write-Host "Make sure you have ImageMagick installed and added to the PATH."
magick.exe convert icon-16.png icon-32.png icon-256.png rusty.ico
