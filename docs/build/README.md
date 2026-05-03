# How to build kernel?

## Prerequirements
- Install `cmake` (>= 3.20)
- Install `make`
- ...and some tools for your CPU architecture

## General information
There's two ways:
1. Use preset for specified MCU
2. Create your custom preset

We recommend use 1st way, if your MCU is supported by the kernel. Otherwise, try to set up kernel for your platform and pull request your configs, please:3 

## Way 1: Presets
All presets for MCUs available in [`CMakePresets.json`](/CMakePresets.json) and can be used via CMake.\
To use this presets, just specify `--preset` with preset name in CMake build command.

### Table with available presets
| MCU         | CPU architecture     | CMake preset name   |        Support status        |
|-------------|----------------------|---------------------|:----------------------------:|
| CH32V30x    | RISC-V, 32bit, IMAFC | "ch32v30x-rv32i"    | `0.9.0` (rv32i arch frezzed) |
| STM32F103xB | ARMv7E               | "stm32f103xb-armv7" |           `1.0.0`            |
| STM32F411xE | ARMv7E, FPU          | "stm32f411xe-armv7" |           `1.0.0`            |

## Way 2: Build "from scratch"
To create your own platform configuration, you need to check CPU architecture. TiOO for now created only for these architectures:

### Table with available CPU architectures
| CPU architecture | ARCH_DIR | Support status  |
|------------------|----------|:---------------:|
| RISC-V, 32bit, I | "rv32i"  |     `0.9.0`     |
| ARMv7E           | "armv7"  |     `1.0.0`     |

Found your architecture? Cool! If no, you can create [full port](PORTING.md) for TiOO.\
Let's continue. CMake script requires 4 parameters to build kernel properly:
- `MCU_DIR`: name of directory, that need to be created in `build/` directory and where must be placed settings for your MCU.
- `ARCH_DIR`: just select architecture from table and enter value from "ARCH_DIR" column into this parameter.
- `PLATFORM_FLAGS`: flags for builder.
- `CMAKE_TOOLCHAIN_FILE`: mini-script for CMake to specify tools for build. More info you can get in toolchains, which already created and in Internet.

**About `MCU_DIR`**:
In `build/$MCU_DIR` you need to create few files:
- `linker.ld`: memory map for linker. More about this files you can read in Internet.
- `platform_constants.h`: some constants to be used in the kernel's code. Just copy and change it in your own way.
- `settings.h`: similar to the `platform_constants.h` file.

After this, you finally can build kernel!\
Just use CMake to generate build files (with your own values):
```shell
cmake -B "./cache" -DMCU_DIR="" -DARCH_DIR="" -DPLATFORM_FLAGS="" -DCMAKE_TOOLCHAIN_FILE=""
```
