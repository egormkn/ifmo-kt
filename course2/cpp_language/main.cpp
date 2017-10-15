#include <cstddef>
#include <cstdio>
#include <cstring>
#include <emmintrin.h>
#include <cstdint>

void *memcpy(void *dst, void const *src, size_t size) {
    __m128i tmp;
    __asm__ volatile (
    "1:"
        "movdqa\t(%0), %3\n"
        "movntdq\t%3, (%1)\n"
        "add\t%0, 16\n"
        "add\t%1, 16\n"
        "sub\t%2, 16\n"
        "jne\t%2, 16\n"
        : "=r"(dst), "=r"(src), "=r"(size), "=x"(tmp)
        : "0"(dst), "1"(src), "2"(size)
        : "memory"
    );
/*
    for(int i = 0, m = size / sizeof(uint32_t); i < m; i++)  // копируем основную часть блоками по 4 или 8 байт
        *(wdst++) = *(wsrc++);                     // (в зависимости от платформы)

    cdst = (unsigned char*)wdst;
    csrc = (unsigned char*)wsrc;

    for(int i = 0, m = size % sizeof(uint32_t); i < m; i++)             // остаток копируем побайтно
        *(cdst++) = *(csrc++);

    return dst;*/
}

int main() {
    const char *string = "Hello, world!";
    char array[100];
    memcpy(array, string, strlen(string));

    printf("%d\n", strlen(string));

    //for (int i = 0; i < strlen(string); i++) {
    printf(">%c<", array[0]);
    //}

}

//      "movdqa      xmm0,xmmword ptr [edx + 0]\n"
//      "movdqa      xmm1,xmmword ptr [edx + 16]\n"
//      "movdqa      xmm2,xmmword ptr [edx + 32]\n"
