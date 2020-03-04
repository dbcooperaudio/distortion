# distortion

<!--Project description-->

## Installation

`git clone --shallow-submodules --recurse-submodules <url>`

## Dependencies

JUCE 5.4.7 has been included as a git submodule

### macOS

- Xcode 9.0+

### Windows

- Visual Studio 2015+

### Linux

The following list has been compiled from [this discussion](https://forum.juce.com/t/list-of-juce-dependencies-under-linux/15121).

Running the shell script `Scripts/install_linux_dependencies.sh` will install the following for you:

- clang
- git
- ladspa-sdk
- freeglut3-dev
- g++
- libasound2-dev
- libcurl4-openssl-dev
- libfreetype6-dev
- libjack-jackd2-dev
- libx11-dev
- libxcomposite-dev
- libxcursor-dev
- libxinerama-dev
- libxrandr-dev
- mesa-common-dev
- webkit2gtk-4.0
- juce-tools

## Building

For macOS and Linux, you can run the following commands to get the project set up immediately and ready for compiling:

#### Quickstart macOS

```bash
$ ./Scripts/projucer.sh --resave *.jucer
$ open Builds/MacOSX/*.xcodeproject
```

### Quickstart Linux

```bash
$ ./Scripts/projucer.sh --resave *.jucer
$ cd Builds/LinuxMakeFile
$ make
```

### Manually

The Projucer is required as part of this project's build system, and can be found in `Modules/juce/extras/Projucer/Builds/<target>` where `<target>` is your relevant operating system / IDE:

- LinuxMakefile
- MacOSX
- VisualStudio2015
- VisualStudio2017
- VisualStudio2019

These folders will contain an IDE project or Makefile allowing you to compile the Projucer. It is recommended you compile the Projucer for the "Release" configuration.

With the Projucer built you can open the `*.jucer` file in this repository and select "Save And Open In IDE" (macOS, Windows). This will generate the needed files for you in `Builds/` and `JuceLibraryCode/`.
