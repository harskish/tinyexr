#!/bin/bash

# Convert RGB exr to single channel (Y) using ImageMagick
"/c/Program Files/mrViewer-v4.3.5-Windows-64/bin/convert.exe" broken.exr +repage -define exr:color-type=Y -compress Piz broken.exr
read -p "Press enter to continue"