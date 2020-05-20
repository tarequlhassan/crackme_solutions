#include <stdbool.h>
#include <stdint.h>
#include <windows.h>


void init() {}

void process_serial(char* name, char* serial_out) {
    BYTE hash_bytes[16] = { 0 };
    int namelen = lstrlen(name);
   
    wsprintf(serial_out, "fuck!");
}