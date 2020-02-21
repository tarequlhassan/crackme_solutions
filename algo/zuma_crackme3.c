#include <stdbool.h>
#include <windows.h>

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
  char mars_tbl[0x40] = { 0 };
  int namesum = 0;
  for (int i = 0; i < namelen; i++)
      namesum += name[i];
  wsprintf(namestr, "%lX", namesum);

  mars_encrypt(namestr, mars_out);

  DWORD* mars_ptr = mars_out;
  DWORD marsstrptr = mars_tbl;
  for (int i = 0; i < 0x20; i += 4)
  {
      wsprintf(&mars_tbl[i*2], "%d", *mars_ptr);
      mars_ptr++;
  }

  int marstbloutlen = strlen(mars_tbl);

 

  wsprintf(serial_out, "you got my love");
}
