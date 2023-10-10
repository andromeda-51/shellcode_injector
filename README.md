# shellcode_injector README.md
## Introduction
shellrunner is a simple Windows-based tool designed to load and execute a given shellcode from a binary file. This differs from blobrunner and other tools like it by simplifying the injection process.
Compile with debugging symbols. During dynamic analysis, inspect the `execute_shellcode` function and put a breakpoint on the instruction that calls the shellcode.

## Prerequisites
* A Windows environment.
* GCC compiler for Windows (like MinGW).

## Compilation
Use the following recommended GCC compiler command to compile the shellrunner:
```bash
gcc -O0 -g -o shellrunner.exe shellrunner.c
```

## Usage
```bash
shellrunner.exe <path to shellcode>
```

* <path to shellcode\>: Path to the binary file containing the shellcode you want to execute.

### Example
```bash
shellrunner.exe myshellcode.bin
```

## Important Notes

This tool directly interacts with the memory and executes arbitrary shellcode.
This tool is intended for educational or testing purposes only. Do not use it for illegal activities.
