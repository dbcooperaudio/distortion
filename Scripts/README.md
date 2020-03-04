# Scripts

A directory of helpful installation, project management, etc. scripts.

## install_linux_dependencies.sh

A script that will automatically install all required dependencies on Linux for
you.

## projucer.sh

A helpful utility to directly call the Projucer for this project from the
command line. If the Projucer in this project is not currently built this script
will build it for you before attempting to run.

_NOTE: This script will not update the Projucer if JUCE has been updated to a
newer version, you should delete the Projucer executable if you need an updated
Projucer._

```bash
# Starting from a clean install, the Projucer will be built and then called with
# the single command line argument "help"
$ ./Scripts/projucer.sh help
```

# export_template.sh

This command is used to generate a new project based off of this template.


```bash
$./Scripts/export_template.sh <project name> <project folder>
```

The
script will:

- Copy `Scripts/` (except `Scripts/export_template.sh`) into the target
- Copy `BinaryData/` into the target
- Copy `Modules/` into the target
- Copy `Source/` into the target
- Copy `template.jucer` into the target as `<project name>.jucer`
- Replace `template` in the `.jucer` file text with `<project name>`
- Initialize a git repository in `<project folder>`
- Set the remote `origin` in the repo to `git@github.com:dbcooperaudio/<project name>.git`
- Add JUCE as a shallow git submodule to the repo under `Modules/juce/`
- Add the `dbcooper` JUCE module as a git submodule to the repo under `Modules/dbcooper/`
- Commit the repo and push the initial commit to `master`
- Create and push branches `develop` and `alpha`
