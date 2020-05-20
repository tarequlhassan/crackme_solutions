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

    int ecx_ = 0;
    int eax_ = 0xBEEFC0DE;
    ecx_ += eax_;
    eax_ =_byteswap_ulong(eax_);
    ecx_ += (eax_*6);
   
    wsprintf(serial_out, "fuck!");
}