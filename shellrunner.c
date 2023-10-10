#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void execute_shellcode(unsigned char* shellcode, size_t size) {
    void *exec_memory = VirtualAlloc(0, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    if (!exec_memory) {
        fprintf(stderr, "Memory allocation failed!\n");
        return;
    }
    memcpy(exec_memory, shellcode, size);

    void (*func)();
    func = (void (*)())exec_memory;

    func();

    VirtualFree(exec_memory, 0, MEM_RELEASE);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path_to_shellcode_file>\n", argv[0]);
        return 1;
    }

    FILE* fp = fopen(argv[1], "rb");
    if (!fp) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    fseek(fp, 0L, SEEK_END);
    size_t fsize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(fsize);
    fread(buffer, 1, fsize, fp);
    fclose(fp);

    execute_shellcode(buffer, fsize);

    free(buffer);
    return 0;
}
