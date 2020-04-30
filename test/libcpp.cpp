#include <iostream>

static const class CRC32 {
  unsigned long crctab[256];
  unsigned long reflect(unsigned long ref) const {
    const int bits = sizeof(unsigned long) * 8;
    unsigned long value = 0;
    // Swap bit 0 for bit 7, bit 1 for bit 6, etc.
    for (int i = 1; i < (bits + 1); i++) {
      if (ref & 1) value |= 1 << (bits - i);
      ref >>= 1;
    }
    return value;
  }

  public:
    CRC32() {
      const unsigned long Quotient = 0x04c11db7;
      unsigned long crc;
      for (int i = 0; i < 256; i++) {
        crc = i << 24;
        for (int j = 0; j < 8; j++) {
          crc = crc & 0x80000000 ? (crc << 1) ^ Quotient : crc << 1;
          crctab[i] = reflect(crc);
        }
      }
    }
    unsigned long compute(const void* data, unsigned int length) const {
      const unsigned char* bytes = static_cast<const unsigned char*>(data);
      unsigned long result = 0xFFFFFFFF;
      while (length --) result = (result >> 8) ^ crctab[(result & 0xFF) ^ *bytes++];
      return result ^ 0xFFFFFFFF;
    }
} crc32;

#if defined(__x86_64__)
extern void print(unsigned __int128  x) {
  union { unsigned __int128 n; struct { unsigned long long l, h; }; };
  n = x;
  std::cout << l << h;
}
#endif
extern void print(unsigned long long x) { std::cout << x; }
extern void print(unsigned long      x) { std::cout << x; }
extern void print(unsigned int       x) { std::cout << x; }
extern void print(unsigned short     x) { std::cout << x; }
extern void print(unsigned char      x) { std::cout << x; }

const unsigned int BUFFSIZE = 1024*1024;
static unsigned char bytes[BUFFSIZE];
static unsigned int byte_count = 0;

extern void flushprintb() {
  if (byte_count) {
    std::cout << crc32.compute(bytes, byte_count);
    byte_count = 0;
  }
}

static class FLUSH {
  public:
  ~FLUSH() { flushprintb(); }
} flush;

#define PRINTB(T)\
	extern void printb(T x) {\
	  if (byte_count + sizeof(T) > BUFFSIZE) flushprintb();\
	  *(T*)(bytes+byte_count) = x;\
	  byte_count += sizeof(T);\
	}

#if defined(__x86_64__)
PRINTB(unsigned __int128)
#endif
PRINTB(unsigned long long)
PRINTB(unsigned long)
PRINTB(unsigned int)
PRINTB(unsigned short)
PRINTB(unsigned char)

#if defined(__x86_64__)
#define SWAP(T)\
	extern void swap(T& a, unsigned __int128&  b) { unsigned __int128  c = a; a = b; b = c; }\
	extern void swap(T& a, unsigned long long& b) { unsigned long long c = a; a = b; b = c; }\
	extern void swap(T& a, unsigned long&      b) { unsigned long      c = a; a = b; b = c; }\
	extern void swap(T& a, unsigned int&       b) { unsigned int       c = a; a = b; b = c; }\
	extern void swap(T& a, unsigned short&     b) { unsigned short     c = a; a = b; b = c; }\
	extern void swap(T& a, unsigned char&      b) { unsigned char      c = a; a = b; b = c; }

#define VSWAP(T)\
	extern void swap(T& a, volatile unsigned __int128&  b) { unsigned __int128  c = a; a = b; b = c; }\
	extern void swap(T& a, volatile unsigned long long& b) { unsigned long long c = a; a = b; b = c; }\
	extern void swap(T& a, volatile unsigned long&      b) { unsigned long      c = a; a = b; b = c; }\
	extern void swap(T& a, volatile unsigned int&       b) { unsigned int       c = a; a = b; b = c; }\
	extern void swap(T& a, volatile unsigned short&     b) { unsigned short     c = a; a = b; b = c; }\
	extern void swap(T& a, volatile unsigned char&      b) { unsigned char      c = a; a = b; b = c; }
#else
#define SWAP(T)\
	extern void swap(T& a, unsigned long long& b) { unsigned long long c = a; a = b; b = c; }\
	extern void swap(T& a, unsigned long&      b) { unsigned long      c = a; a = b; b = c; }\
	extern void swap(T& a, unsigned int&       b) { unsigned int       c = a; a = b; b = c; }\
	extern void swap(T& a, unsigned short&     b) { unsigned short     c = a; a = b; b = c; }\
	extern void swap(T& a, unsigned char&      b) { unsigned char      c = a; a = b; b = c; }

#define VSWAP(T)\
	extern void swap(T& a, volatile unsigned long long& b) { unsigned long long c = a; a = b; b = c; }\
	extern void swap(T& a, volatile unsigned long&      b) { unsigned long      c = a; a = b; b = c; }\
	extern void swap(T& a, volatile unsigned int&       b) { unsigned int       c = a; a = b; b = c; }\
	extern void swap(T& a, volatile unsigned short&     b) { unsigned short     c = a; a = b; b = c; }\
	extern void swap(T& a, volatile unsigned char&      b) { unsigned char      c = a; a = b; b = c; }
#endif

#if defined(__x86_64__)
SWAP(unsigned __int128)
#endif
SWAP(unsigned long long)
SWAP(unsigned long)
SWAP(unsigned int)
SWAP(unsigned short)
SWAP(unsigned char)

#if defined(__x86_64__)
SWAP(volatile unsigned __int128)
#endif
SWAP(volatile unsigned long long)
SWAP(volatile unsigned long)
SWAP(volatile unsigned int)
SWAP(volatile unsigned short)
SWAP(volatile unsigned char)

#if defined(__x86_64__)
VSWAP(unsigned __int128)
#endif
VSWAP(unsigned long long)
VSWAP(unsigned long)
VSWAP(unsigned int)
VSWAP(unsigned short)
VSWAP(unsigned char)

#if defined(__x86_64__)
VSWAP(volatile unsigned __int128)
#endif
VSWAP(volatile unsigned long long)
VSWAP(volatile unsigned long)
VSWAP(volatile unsigned int)
VSWAP(volatile unsigned short)
VSWAP(volatile unsigned char)

#if defined(__x86_64__)
extern unsigned __int128  copy(unsigned __int128  x) { return x; }
#endif
extern unsigned long long copy(unsigned long long x) { return x; }
extern unsigned long      copy(unsigned long      x) { return x; }
extern unsigned int       copy(unsigned int       x) { return x; }
extern unsigned short     copy(unsigned short     x) { return x; }
extern unsigned char      copy(unsigned char      x) { return x; }


