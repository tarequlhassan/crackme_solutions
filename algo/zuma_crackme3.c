#include <stdbool.h>
#include <windows.h>

extern void _stdcall mars_setkey(DWORD* input, DWORD input_len);
extern void _stdcall mars_encrypt(DWORD* input, DWORD* output);

void init() {}

void process_serial(char *name, char *serial_out) {
  char* mars_key = "FEABCBFFFF183461";
  mars_setkey(mars_key, strlen(mars_key));
  char namestr[0x10] = {0}; //pad out blocksize to match block coming out, sym crypt 101
  char mars_out[0x10] = { 0 };
  int namelen = lstrlen(name);
  int namesum = 0;

  for (int i = 0; i < namelen; i++)
      namesum += name[i];
  wsprintf(namestr, "%lX", namesum);
  mars_encrypt(namestr, mars_out);

  wsprintf(serial_out, "you got my love");
}
