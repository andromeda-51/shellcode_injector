# shellcode_injector README.md
##Introduction
shellrunner is a simple Windows-based tool designed to load and execute a given shellcode from a binary file. It allows users to specify the memory address to inject the shellcode, or it will use a default hardcoded address if not provided.

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
shellrunner.exe <path to shellcode> [address to inject to]
```

* <path to shellcode\>: Path to the binary file containing the shellcode you want to execute.
* [address to inject to]: (Optional) Memory address where you want to inject the shellcode. If not specified, a default address of 0x40000000 will be used.

### Example
```bash
shellrunner.exe myshellcode.bin
```

## Important Notes

This tool directly interacts with the memory and executes arbitrary shellcode.
This tool is intended for educational or testing purposes only. Do not use it for illegal activities.
