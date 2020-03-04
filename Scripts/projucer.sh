#!/usr/bin/env bash

# A macOS/Linux utility for passing command line arguments directly to the
# Projucer. If the Projucer executable is not found this script will attempt to
# build it first.

set -e

PROJUCER_EXE="Modules/juce/extras/Projucer/Builds/"

if echo "$OSTYPE" | grep darwin > /dev/null; then
    PROJUCER_EXE+="MacOSX/build/Release/Projucer.app/Contents/MacOS/Projucer"

    if [ ! -f "$PROJUCER_EXE" ]; then
        pushd "Modules/juce/extras/Projucer/Builds/MacOSX/" > /dev/null
        xcodebuild -configuration Release
        popd > /dev/null
    fi
else
    PROJUCER_EXE+="LinuxMakefile/build/Release/Projucer"

    if [ ! -f "$PROJUCER_EXE" ]; then
        pushd "Modules/juce/extras/Projucer/Builds/LinuxMakefile/" > /dev/null
        make CONFIG=Release
        popd > /dev/null
    fi
fi

./$PROJUCER_EXE "$@"
