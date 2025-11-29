# Wolfi Breakout

A breakout game made in **C++** using the ASTU library, Box2D and SDL. This game was created during the Game Programming course at the University of Applied Sciences in Hagenberg.

## Installation

This repository contains the AST-Utilities repository and ASTU-Box2D as a submodule. It is recommended to check out the repository with the command:

`git clone --recurse-submodules https://github.com/Woife5/wolfi-breakout-astu.git`.

The boilerplate code requires to have SDL 2.0 (Simple Direct Layer) installed. On macOS this is assumed to be located at "/Library/Frameworks/SDL2.framework/Versions/A/SDL2" by astu.

Generate and compile the project by running:

```bash
cmake .
make
```

## Acknowledgement

### Simple DirectMedia Layer

Copyright (C) 1997-2021 Sam Lantinga. You can find SDL 2.0 on [GitHub](https://github.com/libsdl-org/SDL)

### ASTU

Copyright (c) 2021 Roman Divotkey.

### ASTU-Box2D Integration

Copyright (c) 2021 Roman Divotkey.

ASTU-Box2D integration contains entity components and entity systems that correspond to the physics abstraction layer in AST-Utilities. You can find ASTU-Box2D on [Github](https://github.com/divotkey/astu-box2d).

### Box2D

Copyright (c) 2019 Erin Catto

Box2D is a free open source 2-dimensional physics simulator engine written in C++ by Erin Catto and published under the MIT license. You can find Box2D on [GitHub](https://github.com/erincatto/box2d).

## Disclaimer

THIS LIBRARY IS PROVIDED AS EDUCATIONAL MATERIAL AND NOT INTENDED TO ADDRESS ALL REAL-WORLD PROBLEMS AND ISSUES IN DETAIL.
