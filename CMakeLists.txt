cmake_minimum_required(VERSION 3.20)
project("TiOO" C ASM)

set(CMAKE_C_STANDARD 90)

function(add_kernel_arch ARCH_NAME ARCH_DIR PLATFORM_FLAGS)
    set(ARCH_SRC_BUILD_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/build/${ARCH_DIR}")
    set(ARCH_SRC_BOOT_DIR       "${CMAKE_CURRENT_SOURCE_DIR}/boot/${ARCH_DIR}")
    set(ARCH_SRC_MEM_DIR        "${CMAKE_CURRENT_SOURCE_DIR}/mem/${ARCH_DIR}")
    set(ARCH_SRC_SYSCALLS_DIR   "${CMAKE_CURRENT_SOURCE_DIR}/syscalls/${ARCH_DIR}")
    # Setup for linker script
    set(LINKER_SCRIPT           "${ARCH_SRC_BUILD_DIR}/linker.ld")

    # Setup for sources
    set(SOURCES
        "${ARCH_SRC_BOOT_DIR}/startup.c"
        "${ARCH_SRC_SYSCALLS_DIR}/syscall_handler.s"

        "${CMAKE_CURRENT_SOURCE_DIR}/boot/main.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/syscalls/syscalls.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/syscalls/api.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/mem/mem.c"
    )
    add_executable(${ARCH_NAME} ${SOURCES})

    separate_arguments(PLATFORM_FLAGS_LIST UNIX_COMMAND "${PLATFORM_FLAGS}")
    # Setup for C and ASM
    target_compile_options(${ARCH_NAME} PRIVATE
        ${PLATFORM_FLAGS_LIST}
        $<$<COMPILE_LANGUAGE:C>:-ffreestanding -O1 -g3 -Wall -Wextra -Werror>
        $<$<COMPILE_LANGUAGE:ASM>:-g3 -x assembler-with-cpp>
    )
    # Setup for linker
    target_link_options(${ARCH_NAME} PRIVATE
        ${PLATFORM_FLAGS_LIST}
        -T ${LINKER_SCRIPT}
        -nostartfiles
        -nostdlib
        -Wl,-Map=${ARCH_NAME}.map
    )

    target_include_directories(${ARCH_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}

        ${ARCH_SRC_BOOT_DIR}
        ${ARCH_SRC_BUILD_DIR}
        ${ARCH_SRC_MEM_DIR}
        ${ARCH_SRC_SYSCALLS_DIR}
    )

    add_custom_command(TARGET ${ARCH_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary ${ARCH_NAME} ${CMAKE_PROJECT_NAME}_${ARCH_NAME}.bin
        COMMAND ${CMAKE_SIZE} ${ARCH_NAME}
        COMMENT ".bin creation and print for sizes"
    )
endfunction()

add_kernel_arch(ARMv7 "armv7" "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
