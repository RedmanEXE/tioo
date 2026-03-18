# TiOO source code style
This file describes some rules about code style in source files of this project

## General
- **Tab size**: 4 spaces
- Writen for **CMake**

## Headers and files
- Every header **contains this structure**:
    - `include`s block;
    - `macro`ses block;
    - `define`s block;
    - `internal function prototype`s block;
    - `external function prototype`s block;
    - ~~`global var`s block~~;
- **DO NOT USE global variables**! All vars must be declared in structures
- **Headers definitions for one-time include** naming: `HEADER_H_`

## Functions
- One function must be created only for one task (**single-responsibility**)
- If function contains more than one logic block – **divide it by tabs**
- Every function must be **DOCUMENTED** with some description before definition
- Every function **must have prototype**
- Functions naming: `Class_Class_FunctionName()`

## Types
- **Types** naming: `Class_TypeName`
- All types must be declared with `typedef`

## Variables
- Variables naming: `vars_name`
- All local variables must be declared in **begin of logic block**

## Constants and defines
- Constants and defines naming: `CONSTS_NAME`/`DEFINES`

## Directories
- *WIP*
