#include <stdbool.h>
#include <windows.h>
#include <stdint.h>

extern void _stdcall mars_setkey(DWORD* input, DWORD input_len);
extern void _stdcall mars_encrypt(DWORD* input, DWORD* output);

void init() {}

void process_serial(char *name, char *serial_out) {
  int namelen = lstrlen(name);
  char* mars_key = "FEABCBFFFF183461";
  mars_setkey(mars_key, strlen(mars_key));
  //pad out blocksize to match block coming out, sym crypt 101
  char namestr[0x10] = {0}; 
  char mars_out[0x20] = { 0 };
  char mars_tbl[0x50] = { 0 };

  char magic[0x6] = { 0 };
  int namesum = 0;
  for (int i = 0; i < namelen; i++)
      namesum += name[i];
  wsprintf(namestr, "%lX", namesum);

  mars_encrypt(namestr, mars_out);

  DWORD* mars_ptr = mars_out;
  BYTE* marsstrptr = mars_tbl;
  marsstrptr += 6;
  for (int i = 0; i < 0x20; i += 4)
  {
      wsprintf(&marsstrptr[i*2], "%d", *mars_ptr);
      mars_ptr++;
  }

  int marstbloutlen = strlen(marsstrptr);
  magic[0] = mars_tbl[5 + marstbloutlen];
  magic[1] = mars_tbl[4 + marstbloutlen];
  magic[2] = mars_tbl[3 + marstbloutlen];
  magic[3] = mars_tbl[1 + marstbloutlen];
  magic[4] = mars_tbl[marstbloutlen];

  //solving this is fucking pointless.
  //uint16_t shit2 = ( 'E' ^ 'S') * 0x4B32;
  //it all comes out the same every single time.

 

  wsprintf(serial_out, "%s-55600",magic);
}
