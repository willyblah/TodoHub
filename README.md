# Todo Hub

## About

**Todo Hub** is a command-based terminal to-do list manager.

## Features

- Basic to-do list managing
- Saves your to-do list to a file

## Screenshot

```
TODO HUB 1.0.0
--------------

1. Task A
2. Task B
3. Task C
4. Task D [COMPLETED]
5. Task E [COMPLETED]

> rm 5
```

## Installation

### Direct download

**Only Windows and Linux binaries are provided.**

1. Download `TodoHub-vX.X.X.zip` from the
    [latest release](https://github.com/willyblah/TodoHub/releases/latest).
2. Extract `TodoHub-vX.X.X.zip`.
3. Run `TodoHub.exe`.
    - The Windows binary is located in `build/windows-release`.
    - The Linux binary is located in `build/linux-release`.
4. It is recommended to create a shortcut to Todo Hub for easy access.

### Build from source

**Requirements**

- GCC (Windows/Linux) or Clang (macOS)
- CMake 3.10 or later

**Steps**

1. Download the source code from the [latest release](https://github.com/willyblah/TodoHub/releases/latest).
2. Extract the source code.
3. Run the build script for your system.
    - Windows: `build-windows.bat`
    - macOS: `build-macos.sh`
    - Linux: `build-linux.sh`
4. Run `TodoHub.exe`.
    - The Windows binary is located in `build/windows-release`.
    - The Linux binary is located in `build/linux-release`.
5. It is recommended to create a shortcut to Todo Hub for easy access.

## Support

Help content can be found in `help.txt`. You can also access help by typing the
`help` command in Todo Hub.
