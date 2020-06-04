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
    //each member of the lut equals a number
    //so X = 1, Z = 2 and so on
    const char lut[6] = { 'X','Z','M','A','J','K' };
    char hash_bytes[16] = "XXZXAAJ-XZJXKXJ";
    //zuma555
    //XXZXAAJ - XZJXKXJ

    int namelen = lstrlen(name);

    Register hasheax_,namelen_ha;
    hasheax_.ex = namelen_ha.ex = namelen;

    //the checksum hash
    for (int i = 0; i < namelen; i++)
    {
        hasheax_.b.lo += name[i];
        hasheax_.ex += 0x7C80BDF6;
        hasheax_.ex *= namelen_ha.ex;
        hasheax_.ex += hasheax_.ex;
        namelen_ha.ex--;
    }
    hasheax_.ex = hasheax_.b.lo * 2;

    Register eax_ = { 0 }, edx_ = { 0 }, ebx_ = { 0 };


    //first portion
    for (int i = 0; i < namelen; i++)
    {
        for (int j = 0; j < 6; j++)
            if (hash_bytes[i] == lut[j])
            {
                hash_bytes[i] = j;
                break;
            } 
    }

    //second round
    for (int i = 0; i < namelen; i++)
    {
        for (int j = 0; j < 6; j++)
            if (hash_bytes[i+(namelen+1)] == lut[j])
            {
                hash_bytes[i +(namelen+1)] = j;
                break;
            }
    }
    wsprintf(serial_out, "fuck!");
}