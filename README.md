# Group-7-Minesweeper-Game
## Installation

### Linux

Install the build tools and gtkmm 4:

**Ubuntu / Debian** (Ubuntu 22.04+ / Debian 12+)
```bash
sudo apt update
sudo apt install build-essential pkg-config libgtkmm-4.0-dev
```

**Fedora**
```bash
sudo dnf install gcc-c++ make pkgconf-pkg-config gtkmm4.0-devel
```

**Arch**
```bash
sudo pacman -S base-devel gtkmm-4.0
```

Then build and run:
```bash
make
./cppsweeper      # or: make run
```

### Windows (MSYS2)

1. Install MSYS2 from https://www.msys2.org
2. Open the **MSYS2 UCRT64** terminal and install the toolchain and gtkmm 4:
   ```bash
   pacman -Syu
   pacman -S make mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-pkgconf mingw-w64-ucrt-x86_64-gtkmm-4.0
   ```
3. `cd` to the project folder (e.g. `cd /c/Users/<you>/path/to/Group-7-Minesweeper-Game`) and build:
   ```bash
   make
   ./cppsweeper.exe   # or: make run
   ```

> Run the game from the UCRT64 terminal. To launch it from outside MSYS2, add
> `C:\msys64\ucrt64\bin` to your `PATH` so Windows can find the GTK DLLs.

### Cleaning
```bash
make clean
```