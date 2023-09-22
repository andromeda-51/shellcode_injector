#include <stdio.h>
#include <string.h>
#include <windows.h>

// Hardcoded address to inject to, if not specified by the user.
#define DEFAULT_ADDRESS 0x40000000

int main(int argc, char **argv) {
    unsigned char *shellcode;
    size_t shellcode_size;
    FILE *file;
    void *target_address = (void *)DEFAULT_ADDRESS;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path to shellcode> [address to inject to]\n", argv[0]);
        return 1;
    }

    if (argc == 3) {
        sscanf(argv[2], "%p", &target_address);
    }

    // Read the shellcode from the specified file
    file = fopen(argv[1], "rb");
    if (!file) {
        perror("Failed to open shellcode file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    shellcode_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    shellcode = (unsigned char *)malloc(shellcode_size);
    if (!shellcode) {
        perror("Failed to allocate memory for shellcode");
        fclose(file);
        return 1;
    }

    fread(shellcode, 1, shellcode_size, file);
    fclose(file);

    // Allocate memory for the shellcode
    void *allocated_memory = VirtualAlloc(target_address, shellcode_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (!allocated_memory) {
        perror("Failed to allocate memory at target address");
        free(shellcode);
        return 1;
    }

    // Copy the shellcode to the target memory region
    memcpy(allocated_memory, shellcode, shellcode_size);

    // Execute the shellcode
    void (*shellcode_function)() = (void (*)())allocated_memory;
    shellcode_function();

    // Cleanup
    VirtualFree(allocated_memory, 0, MEM_RELEASE);
    free(shellcode);
    return 0;
}
