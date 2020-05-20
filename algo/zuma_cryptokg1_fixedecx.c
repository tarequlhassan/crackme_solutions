#include <stdbool.h>
#include <stdint.h>
#include <windows.h>

typedef union {
    uint64_t rx;
    uint32_t ex;
    uint16_t x;
    struct {
        uint8_t lo, hi;
    } b;
} Register;


void init() {}

void process_serial(char* name, char* serial_out) {
    BYTE hash_bytes[16] = { 0 };
    int namelen = lstrlen(name);

    Register eax_,edx_;
    eax_.ex = namelen;
    edx_.ex = namelen;


    for (int i = 0; i < namelen; i++)
    {
        eax_.b.lo += name[i];
        eax_.ex += 0x7C80BDF6;
        eax_.ex *= edx_.ex;
        eax_.ex += eax_.ex;
        edx_.ex--;
    }
   
    wsprintf(serial_out, "fuck!");
}