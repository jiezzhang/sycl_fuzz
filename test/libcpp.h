#if defined(__x86_64__)
extern void print(unsigned __int128);
#endif
extern void print(unsigned long long);
extern void print(unsigned long);
extern void print(unsigned int);
extern void print(unsigned short);
extern void print(unsigned char);

#if defined(__x86_64__)
extern void printb(unsigned __int128);
#endif
extern void printb(unsigned long long);
extern void printb(unsigned long);
extern void printb(unsigned int);
extern void printb(unsigned short);
extern void printb(unsigned char);
extern void flushprintb();

#if defined(__x86_64__)
#define SWAP(T)\
	extern void swap(T&, unsigned __int128& );\
	extern void swap(T&, unsigned long long&);\
	extern void swap(T&, unsigned long&     );\
	extern void swap(T&, unsigned int&      );\
	extern void swap(T&, unsigned short&    );\
	extern void swap(T&, unsigned char&     );

#define VSWAP(T)\
	extern void swap(T&, volatile unsigned __int128& );\
	extern void swap(T&, volatile unsigned long long&);\
	extern void swap(T&, volatile unsigned long&     );\
	extern void swap(T&, volatile unsigned int&      );\
	extern void swap(T&, volatile unsigned short&    );\
	extern void swap(T&, volatile unsigned char&     );
#else
#define SWAP(T)\
	extern void swap(T&, unsigned long long&);\
	extern void swap(T&, unsigned long&     );\
	extern void swap(T&, unsigned int&      );\
	extern void swap(T&, unsigned short&    );\
	extern void swap(T&, unsigned char&     );

#define VSWAP(T)\
	extern void swap(T&, volatile unsigned long long&);\
	extern void swap(T&, volatile unsigned long&     );\
	extern void swap(T&, volatile unsigned int&      );\
	extern void swap(T&, volatile unsigned short&    );\
	extern void swap(T&, volatile unsigned char&     );
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
extern unsigned __int128  copy(unsigned __int128);
#endif
extern unsigned long long copy(unsigned long long);
extern unsigned long      copy(unsigned long);
extern unsigned int       copy(unsigned int);
extern unsigned short     copy(unsigned short);
extern unsigned char      copy(unsigned char);

