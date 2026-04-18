cmake_minimum_required(VERSION 3.20)
project("TiOO" C ASM)

set(CMAKE_C_STANDARD 90)

set(MCU_SRC_BUILD_DIR       "${CMAKE_CURRENT_SOURCE_DIR}/build/${MCU_DIR}")
set(ARCH_SRC_BOOT_DIR       "${CMAKE_CURRENT_SOURCE_DIR}/boot/${ARCH_DIR}")
set(ARCH_SRC_MEM_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/mem/${ARCH_DIR}")
set(ARCH_SRC_SYSCALLS_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/syscalls/${ARCH_DIR}")
set(ARCH_SRC_TASKS_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/tasks/${ARCH_DIR}")
# Setup for linker script
set(LINKER_SCRIPT           "${MCU_SRC_BUILD_DIR}/linker.ld")

# Setup for sources
set(SOURCES
    "${ARCH_SRC_BOOT_DIR}/vectors.c"
    "${ARCH_SRC_BOOT_DIR}/startup.S"
    "${ARCH_SRC_SYSCALLS_DIR}/syscall_handler.S"
    "${ARCH_SRC_TASKS_DIR}/context.S"
    "${ARCH_SRC_TASKS_DIR}/manager.S"

    "${CMAKE_CURRENT_SOURCE_DIR}/boot/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/syscalls/syscalls.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/syscalls/api.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/mem/mem.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/tasks/tasks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/tasks/tasks_manager.c"
)
add_executable(Kernel ${SOURCES})

separate_arguments(PLATFORM_FLAGS_LIST UNIX_COMMAND "${PLATFORM_FLAGS}")
# Setup for C and ASM
target_compile_options(Kernel PRIVATE
    ${PLATFORM_FLAGS_LIST}
    $<$<COMPILE_LANGUAGE:C>:-ffreestanding -O1 -g3 -Wall -Wextra -Werror>
    $<$<COMPILE_LANGUAGE:ASM>:-g3 -x assembler-with-cpp>
)
# Setup for linker
target_link_options(Kernel PRIVATE
    ${PLATFORM_FLAGS_LIST}
    -T ${LINKER_SCRIPT}
    -nostartfiles
    -nostdlib
    -Wl,-Map=Kernel.map
)

target_include_directories(Kernel PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}

    ${ARCH_SRC_BOOT_DIR}
    ${MCU_SRC_BUILD_DIR}
    ${ARCH_SRC_MEM_DIR}
    ${ARCH_SRC_SYSCALLS_DIR}
    ${ARCH_SRC_TASKS_DIR}
)

add_custom_command(TARGET Kernel POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary Kernel tioo_${MCU_DIR}_${ARCH_DIR}.bin
    COMMAND ${CMAKE_SIZE} Kernel
    COMMENT ".bin creation and print for sizes"
)