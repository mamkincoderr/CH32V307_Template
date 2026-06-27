# CH32V307 Template

VSCode project template for **CH32V307** (RISC-V Qingke V4F) by WCH.  
Build system: **CMake + Ninja**. Toolchains: **MounRiver Studio 2** (GCC 15 / 12 / 8).

**Author:** Дима из Одессы — [@mamkincoderr](https://github.com/mamkincoderr)

---

## Features

- Three GCC presets selectable from VSCode status bar or `build.bat`
- `User/Lib/` — reusable utilities: `tick.c/h` (SysTick ms), `gpio_utils.h` (GPIO macros)
- One-line toolchain config via `CMakePresets.json`
- Build/Flash/Clean/Rebuild buttons via VsCodeTaskButtons
- Cortex-Debug + WCH OpenOCD integration

## Prerequisites

Install once (adds to PATH automatically):

```
winget install Kitware.CMake
winget install Ninja-build.Ninja
```

Also required:
- [MounRiver Studio 2](http://www.mounriver.com/) — provides GCC toolchains + OpenOCD
- VSCode extensions: `ms-vscode.cmake-tools`, `marus25.cortex-debug`, `ms-vscode.cpptools`, `spmeesseman.vscode-taskexplorer`

## Project structure

```
CH32V307_Template/
├── Core/              WCH core_riscv.c/h
├── Debug/             WCH debug.c/h (UART printf)
├── Peripheral/        WCH Standard Peripheral Library
│   ├── inc/
│   └── src/
├── Startup/           startup_ch32v30x_D8C.S / D8.S
├── Ld/                Link.ld
├── User/              Application code
│   ├── Lib/
│   │   ├── tick.c/h       SysTick ms counter
│   │   └── gpio_utils.h   GPIO helper macros
│   └── main.c
├── cmake/
│   └── toolchain.cmake
├── .vscode/
├── CMakeLists.txt
├── CMakePresets.json  ← единственный файл настройки тулчейнов
├── build.bat
└── openocd.cfg
```

## Building

### From VSCode

1. Open folder in VSCode
2. CMake Tools → select preset: **GCC 15.2.0 — MRS2** (status bar)
3. Click **Build** button (status bar)

### From command line

```bat
build.bat build            REM GCC15 по умолчанию
build.bat build gcc12      REM GCC12
build.bat build gcc8       REM GCC8
build.bat clean
build.bat rebuild
build.bat flash            REM прошить через WCH-Link
```

Output files: `obj/CH32V307_Template.elf`, `.hex`, `.bin`, `.map`

## Flashing & Debugging

- **Flash:** `build.bat flash` or VSCode task **Flash**
- **Debug:** F5 in VSCode → **Debug CH32V307 (GCC15)**  
  Requires WCH-Link or WCH-LinkE connected via USB.

> SVD file `doc/CH32V307.svd` — download from [openwch/ch32v307](https://github.com/openwch/ch32v307) for peripheral register view in debugger.

## License

MIT License — see [LICENSE](LICENSE).  
WCH SDK files (Core, Debug, Peripheral, Startup, Ld) retain original WCH copyright.
