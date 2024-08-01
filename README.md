### Building
Dependencies:
- Visual Studio Build Tools (e.g. 2022) with additions:
    - MSVC
    - Win11 SDK
- OpenCV (e.g. `choco install opencv`)
- make (e.g. `choco install make`)

1. Check `Makefile` for include directories (if followed above, shouldn't be an issue)
1. Ensure developer shell (for `cl.exe` to be defined)
1. Run `make` to compile.
