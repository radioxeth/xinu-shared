void print(unsigned char c, unsigned char* x, unsigned long long xlen) {
  unsigned long long i;
  kprintf("%c[%d]=", c, (int)xlen);
  for (i = 0; i < xlen; ++i) printf("%02x", x[i]);
  kprintf("\n");
}
void init_buffer(unsigned char *buffer, unsigned long long numbytes) {
  unsigned long long i;
  for (i = 0; i < numbytes; i++) buffer[i] = (unsigned char)i;
}