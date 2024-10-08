#pragma once

// Can be used for writing labels in assembly
#if defined(__GNUC__)
#define GCC_SPLIT_BLOCK(str) __asm__("//\n\t// " str "\n\t//\n");
#elif defined(_WIN64)
// Only 64-bit windows forbid inline assembly
#define GCC_SPLIT_BLOCK(str)
#else
#define GCC_SPLIT_BLOCK(str) __asm {}
#endif
