cmake_minimum_required(VERSION 3.20)

project(CH32V307_Template C ASM)

# ---- Архитектура ----
set(CPU_ARCH "rv32imafc")
set(CPU_ABI  "ilp32")

option(USE_FPU  "Аппаратный FPU (требует rv32imafc)" ON)
option(USE_SPL  "WCH Standard Peripheral Library"     ON)
option(USE_OOCD "OOCD debug framework"                ON)

if(USE_SPL)  add_definitions(-DUSE_STDPERIPH_DRIVER) endif()
if(USE_FPU)  add_definitions(-DUSE_FPU)              endif()
if(USE_OOCD) add_definitions(-DOOCD_ENABLE)          endif()

# ---- Исходники ----
file(GLOB USER_SOURCES   CONFIGURE_DEPENDS "User/*.c" "User/Lib/*.c")
file(GLOB PERIPH_SOURCES CONFIGURE_DEPENDS "Peripheral/src/*.c")
file(GLOB CORE_SOURCES   CONFIGURE_DEPENDS "Core/*.c")
file(GLOB DEBUG_SOURCES  CONFIGURE_DEPENDS "Debug/*.c")

set(STARTUP Startup/startup_ch32v30x_D8C.S)

# ---- Оптимизация по папкам ----
set_source_files_properties(${USER_SOURCES}   PROPERTIES COMPILE_OPTIONS "-O0;-g3")
set_source_files_properties(${CORE_SOURCES}   PROPERTIES COMPILE_OPTIONS "-O0;-g3")
set_source_files_properties(${DEBUG_SOURCES}  PROPERTIES COMPILE_OPTIONS "-O2;-g2")
set_source_files_properties(${PERIPH_SOURCES} PROPERTIES COMPILE_OPTIONS "-O2;-g2")

# ---- Заголовки ----
set(INCLUDES
    User
    User/Lib
    Core
    Debug
    Peripheral/inc
    Ld
)

# ---- Цель ----
add_executable(${PROJECT_NAME}.elf
    ${USER_SOURCES}
    ${CORE_SOURCES}
    ${DEBUG_SOURCES}
    ${PERIPH_SOURCES}
    ${STARTUP}
)

target_include_directories(${PROJECT_NAME}.elf PRIVATE ${INCLUDES})

target_compile_options(${PROJECT_NAME}.elf PRIVATE
    -march=${CPU_ARCH}
    -mabi=${CPU_ABI}
    -Wall
    -fdata-sections
    -ffunction-sections
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
    -march=${CPU_ARCH}
    -mabi=${CPU_ABI}
    -T${CMAKE_SOURCE_DIR}/Ld/Link.ld
    -nostartfiles
    -Wl,--gc-sections
    -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map,--cref
    -Wl,--print-memory-usage
    --specs=nano.specs
    --specs=nosys.specs
    -lm
)

# ---- Post-build: .hex, .bin, size ----
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${PROJECT_NAME}.elf> ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} --format=berkeley $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Generating .hex .bin"
)
