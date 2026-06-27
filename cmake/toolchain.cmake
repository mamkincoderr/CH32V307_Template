cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(NOT DEFINED ENV{RISCV_TOOLCHAIN} OR NOT DEFINED ENV{RISCV_PREFIX})
    message(FATAL_ERROR
        "Выберите пресет сборки: gcc15 / gcc12 / gcc8\n"
        "  cmake --preset gcc15\n"
        "  или выберите пресет в строке статуса VSCode (CMake Tools)"
    )
endif()

set(TOOLCHAIN "$ENV{RISCV_TOOLCHAIN}/bin")
set(PREFIX    "$ENV{RISCV_PREFIX}")

set(CMAKE_C_COMPILER   "${TOOLCHAIN}/${PREFIX}gcc.exe" CACHE FILEPATH "C compiler")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN}/${PREFIX}gcc.exe" CACHE FILEPATH "ASM compiler")
set(CMAKE_OBJCOPY      "${TOOLCHAIN}/${PREFIX}objcopy.exe")
set(CMAKE_OBJDUMP      "${TOOLCHAIN}/${PREFIX}objdump.exe")
set(CMAKE_SIZE         "${TOOLCHAIN}/${PREFIX}size.exe")

message(STATUS "Toolchain : ${TOOLCHAIN}/${PREFIX}gcc.exe")
