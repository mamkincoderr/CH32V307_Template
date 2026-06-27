# AI Instruction — CH32V307_Template

## Project overview

Embedded C template for WCH CH32V307 (RISC-V Qingke V4F, RV32IMAFCXW).  
Build: CMake 3.20+ + Ninja. IDE: VSCode.

## Toolchain paths (MounRiver Studio 2, Windows)

Base: `C:/MounRiver/MounRiver_Studio2/resources/app/resources/win32/components/WCH`

| Preset | GCC path (relative to base) | Prefix |
|--------|------------------------------|--------|
| gcc15  | `Toolchain/RISC-V Embedded GCC15/bin` | `riscv32-wch-elf-` |
| gcc12  | `Toolchain/RISC-V Embedded GCC12/bin` | `riscv-wch-elf-`   |
| gcc8   | `Toolchain/RISC-V Embedded GCC/bin`   | `riscv-none-embed-`|

OpenOCD: `OpenOCD/OpenOCD/bin/openocd.exe`  
wch-riscv.cfg: `OpenOCD/OpenOCD/bin/wch-riscv.cfg`  
GDB (GCC15): `Toolchain/RISC-V Embedded GCC15/bin/riscv32-wch-elf-gdb.exe`

## Build system

- **CMakePresets.json** — единственный файл настройки тулчейна (3 пресета)
- Пресет устанавливает env `RISCV_TOOLCHAIN` и `RISCV_PREFIX`
- **cmake/toolchain.cmake** читает только из ENV (нет .env файла)
- Build dir: `obj/`  Binary: `obj/CH32V307_Template.elf/.hex/.bin`
- Generator: Ninja

## Critical rules

- Task Buttons key: `VsCodeTaskButtons.tasks` (НЕ `taskButtons.tasks`)
- OpenOCD пути — только прямые слэши `/`
- НЕ добавлять флаг `-mfp16-format=none` (GCC12 не поддерживает)
- НЕ использовать PlatformIO
- НЕ добавлять SEGGER RTT без явного запроса (совместимость с WCH-Link не подтверждена)
- WCH SDK файлы (Core/, Debug/, Peripheral/, Startup/, Ld/) имеют оригинальные заголовки WCH — НЕ изменять их

## File headers (наши файлы)

```c
/******************************************************************************
 * @file     filename.c
 * @author   Дима из Одессы (mamkincoderr)
 * @brief    Brief description
 * @repo     https://github.com/mamkincoderr/CH32V307_Template
 * @license  MIT License — see LICENSE in repository root
 * Copyright (c) 2026 Дима из Одессы
 *****************************************************************************/
```

## Source structure

```
User/         — пользовательский код (O0, g3)
User/Lib/     — утилиты: tick.c/h (SysTick), gpio_utils.h (макросы GPIO)
Core/         — WCH core_riscv.c/h
Debug/        — WCH debug.c/h (printf через UART)
Peripheral/   — WCH SPL (src/*.c + inc/*.h), O2
Startup/      — startup_ch32v30x_D8C.S
Ld/           — Link.ld
```

## Architecture

- `rv32imafc`, `ilp32` — стандартные для CH32V307
- USE_FPU=ON → аппаратный FPU, define USE_FPU
- USE_SPL=ON → USE_STDPERIPH_DRIVER
- CH32V30x_D8C — вариант с USB HS + Ethernet

## GitHub

Repo: `github.com/mamkincoderr/CH32V307_Template`  
Author alias: `Дима из Одессы`  
License: MIT (наш код) + WCH original (SDK)
