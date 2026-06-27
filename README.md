# CH32V307 Template

Шаблон проекта для микроконтроллера **CH32V307** (архитектура RISC-V).  
Сборка через **CMake + Ninja**, отладка через **VSCode + WCH-Link**.

**Автор:** Дима из Одессы — [@mamkincoderr](https://github.com/mamkincoderr)

---

## Содержание

1. [Необходимый софт](#1-необходимый-софт)
2. [Установка (один раз)](#2-установка-один-раз)
3. [Скачать проект](#3-скачать-проект)
4. [Открыть в VSCode](#4-открыть-в-vscode)
5. [Выбрать компилятор](#5-выбрать-компилятор)
6. [Собрать проект](#6-собрать-проект)
7. [Прошить процессор](#7-прошить-процессор)
8. [Отладка](#8-отладка)
9. [Структура проекта](#9-структура-проекта)
10. [Частые ошибки](#10-частые-ошибки)

---

## 1. Необходимый софт

| Программа | Назначение | Откуда |
|-----------|-----------|--------|
| **MounRiver Studio 2** | Компиляторы GCC + OpenOCD для прошивки | [mounriver.com](http://www.mounriver.com/) |
| **Visual Studio Code** | Редактор кода | [code.visualstudio.com](https://code.visualstudio.com/) |
| **CMake** | Система сборки | `winget` (команда ниже) |
| **Ninja** | Быстрый сборщик | `winget` (команда ниже) |
| **Git** | Скачать и обновлять проект | `winget` (команда ниже) |

> **Важно:** MounRiver Studio 2 должен быть установлен **до** открытия проекта —
> компиляторы и OpenOCD берутся из его папки.

---

## 2. Установка (один раз)

### 2.1 Установить MounRiver Studio 2

Скачать с официального сайта [mounriver.com](http://www.mounriver.com/) и установить
со всеми настройками по умолчанию.

Путь по умолчанию:
```
C:\MounRiver\MounRiver_Studio2\
```

### 2.2 Установить Visual Studio Code

Скачать с [code.visualstudio.com](https://code.visualstudio.com/) и установить.

> Примечание: MounRiver Studio 2 тоже основан на VSCode, но это **другая** программа.
> Для работы с этим шаблоном нужен обычный VSCode.

### 2.3 Установить CMake, Ninja и Git

Открыть **PowerShell** (Win+X → Windows PowerShell) и выполнить три команды:

```powershell
winget install Kitware.CMake
winget install Ninja-build.Ninja
winget install Git.Git
```

На каждую команду нажать `Y` если потребуется подтверждение.

После установки **перезапустить VSCode** (если был открыт).

### 2.4 Установить расширения VSCode

При первом открытии проекта VSCode автоматически предложит установить расширения:

![Extensions prompt](doc/img_ext_prompt.png)

Нажать **Install All** — и всё установится само.

Если запрос не появился — установить вручную (`Ctrl+Shift+X`):

| Расширение | ID |
|-----------|-----|
| C/C++ | `ms-vscode.cpptools` |
| CMake Tools | `ms-vscode.cmake-tools` |
| Cortex-Debug | `marus25.cortex-debug` |
| VSCode Task Buttons | `spmeesseman.vscode-taskbuttons` |

---

## 3. Скачать проект

### Вариант А — через Git (рекомендуется)

Открыть **PowerShell** и выполнить:

```powershell
git clone https://github.com/mamkincoderr/CH32V307_Template.git
```

Проект появится в папке `CH32V307_Template` там, где была открыта консоль.

### Вариант Б — скачать ZIP

1. Перейти на [github.com/mamkincoderr/CH32V307_Template](https://github.com/mamkincoderr/CH32V307_Template)
2. Нажать зелёную кнопку **Code → Download ZIP**
3. Распаковать архив в удобную папку

---

## 4. Открыть в VSCode

1. Запустить **Visual Studio Code**
2. **File → Open Folder** (`Ctrl+K, Ctrl+O`)
3. Выбрать папку `CH32V307_Template` и нажать **Select Folder**
4. Если VSCode спросит "Do you trust the authors?" — нажать **Yes, I trust**
5. Если появится уведомление об установке расширений — нажать **Install All**

---

## 5. Выбрать компилятор

В нижней строке VSCode (статусбар) найти надпись **[No Configure Preset Selected]**
и кликнуть по ней:

```
┌─────────────────────────────────────────────────────────┐
│  [No Configure Preset Selected]  ◄── кликнуть сюда     │
└─────────────────────────────────────────────────────────┘
```

Из выпадающего списка выбрать:

```
  GCC 15.2.0 — MRS2 (riscv32-wch-elf)   ◄── выбрать это
  GCC 12.2.0 — MRS2 (riscv-wch-elf)
  GCC 8.2.0  — MRS2 (riscv-none-embed)
```

Рекомендуется **GCC 15.2.0** — самый новый.

---

## 6. Собрать проект

Нажать кнопку **$(tools)  Собрать** в статусбаре:

```
┌──────────────────────────────────────────────────────────────────┐
│  $(tools) Собрать  $(zap) Прошить  $(trash) Очистить  ...       │
└──────────────────────────────────────────────────────────────────┘
```

Или нажать `Ctrl+Shift+B`.

В нижней панели откроется терминал и появится вывод компилятора.  
**Успешная сборка** заканчивается примерно так:

```
[35/35] Linking C executable CH32V307_Template.elf; Generating .hex .bin
Memory region    Used Size  Region Size  %age Used
       FLASH:       7712 B      288 KB      2.62%
         RAM:       2496 B       32 KB      7.62%
```

Готовые файлы появятся в папке `obj\`:
- `CH32V307_Template.hex` — для прошивки
- `CH32V307_Template.elf` — для отладки
- `CH32V307_Template.bin` — бинарный образ

---

## 7. Прошить процессор

### Подключение WCH-Link

Подключить WCH-Link (или WCH-LinkE) к ПК через USB, затем к плате:

```
WCH-Link        Плата CH32V307
──────────      ──────────────
  SWDIO    ──►   SWDIO
  SWCLK    ──►   SWCLK
  GND      ──►   GND
  3.3V     ──►   3.3V  (опционально, если нет внешнего питания)
```

### Прошить

Нажать кнопку **$(zap)  Прошить** в статусбаре.

Программа автоматически:
1. Пересоберёт проект (если были изменения)
2. Прошьёт hex-файл в память чипа
3. Верифицирует записанные данные
4. Сбросит процессор (запустит программу)

**Успешная прошивка** в терминале:

```
** Programming Started **
** Programming Finished **
** Verified OK **
** Resetting Target **
```

---

## 8. Отладка

1. Подключить WCH-Link к плате (см. раздел 7)
2. Нажать **F5** или перейти в **Run → Start Debugging**
3. Выбрать конфигурацию **Debug CH32V307 (GCC15)**
4. Отладчик остановится на функции `main()`

Доступны: точки останова, просмотр переменных, регистров процессора.

---

## 9. Структура проекта

```
CH32V307_Template/
├── Core/                   WCH: ядро RISC-V (core_riscv.c/h)
├── Debug/                  WCH: отладочный printf через UART (debug.c/h)
├── Peripheral/             WCH: стандартная библиотека периферии (SPL)
│   ├── inc/                    заголовочные файлы
│   └── src/                    исходники
├── Startup/                WCH: файл инициализации (.S)
├── Ld/                     WCH: скрипт линкера (Link.ld)
├── User/                   ← сюда писать свой код
│   ├── Lib/
│   │   ├── tick.c/h            миллисекундный таймер (SysTick)
│   │   └── gpio_utils.h        макросы для работы с GPIO
│   └── main.c
├── cmake/
│   └── toolchain.cmake
├── .vscode/                настройки редактора (не трогать)
├── obj/                    папка сборки (создаётся автоматически)
├── CMakeLists.txt          описание проекта для CMake
├── CMakePresets.json       ← настройки компиляторов (пути MRS2)
├── build.bat               скрипт сборки (используется кнопками)
└── openocd.cfg             настройка прошивальщика
```

**Папки для редактирования:**
- `User/` — основной код приложения
- `User/Lib/` — утилиты (tick, gpio_utils)

**Не изменять:** `Core/`, `Debug/`, `Peripheral/`, `Startup/`, `Ld/` — это SDK от WCH.

---

## 10. Частые ошибки

### `cmake: command not found`
CMake не установлен или VSCode открыт до установки.  
→ Выполнить `winget install Kitware.CMake`, перезапустить VSCode.

### `ninja: command not found`
→ Выполнить `winget install Ninja-build.Ninja`, перезапустить VSCode.

### `[No Configure Preset Selected]` не исчезает
CMake Tools не видит пресеты.  
→ `Ctrl+Shift+P` → "CMake: Select Configure Preset" → выбрать GCC 15.2.0.

### Кнопки Собрать/Прошить не видны в статусбаре
Расширение VSCode Task Buttons не установлено.  
→ `Ctrl+Shift+X` → найти `spmeesseman.vscode-taskbuttons` → Install.

### `WCH-Link not found` при прошивке
- WCH-Link не подключён к ПК
- Не установлен USB-драйвер WCH-Link (устанавливается вместе с MRS2)
- Попробовать отключить и подключить WCH-Link заново

### Ошибка компилятора `riscv32-wch-elf-gcc.exe: no such file`
MounRiver Studio 2 не установлен или установлен не по умолчанию.  
→ Проверить наличие папки `C:\MounRiver\MounRiver_Studio2\`  
→ Если путь другой — отредактировать `CMakePresets.json`

---

## Лицензия

Код в `User/`, `cmake/`, `build.bat` — [MIT License](LICENSE) © 2026 Дима из Одессы.  
Файлы WCH SDK (`Core/`, `Debug/`, `Peripheral/`, `Startup/`, `Ld/`) — © Nanjing Qinheng Microelectronics.
