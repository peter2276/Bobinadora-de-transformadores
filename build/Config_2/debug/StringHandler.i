# 1 "StringHandler.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/Applications/microchip/mplabx/v6.00/packs/Microchip/PIC18F-K_DFP/1.5.114/xc8/pic/include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "StringHandler.c" 2

# 1 "/Applications/microchip/xc8/v2.36/pic/include/c99/stdlib.h" 1 3



# 1 "/Applications/microchip/xc8/v2.36/pic/include/c99/musl_xc8.h" 1 3
# 5 "/Applications/microchip/xc8/v2.36/pic/include/c99/stdlib.h" 2 3





# 1 "/Applications/microchip/xc8/v2.36/pic/include/c99/features.h" 1 3
# 11 "/Applications/microchip/xc8/v2.36/pic/include/c99/stdlib.h" 2 3
# 21 "/Applications/microchip/xc8/v2.36/pic/include/c99/stdlib.h" 3
# 1 "/Applications/microchip/xc8/v2.36/pic/include/c99/bits/alltypes.h" 1 3
# 18 "/Applications/microchip/xc8/v2.36/pic/include/c99/bits/alltypes.h" 3
typedef long int wchar_t;
# 122 "/Applications/microchip/xc8/v2.36/pic/include/c99/bits/alltypes.h" 3
typedef unsigned size_t;
# 168 "/Applications/microchip/xc8/v2.36/pic/include/c99/bits/alltypes.h" 3
typedef __int24 int24_t;
# 204 "/Applications/microchip/xc8/v2.36/pic/include/c99/bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 22 "/Applications/microchip/xc8/v2.36/pic/include/c99/stdlib.h" 2 3

int atoi (const char *);
long atol (const char *);
long long atoll (const char *);
double atof (const char *);

float strtof (const char *restrict, char **restrict);
double strtod (const char *restrict, char **restrict);
long double strtold (const char *restrict, char **restrict);



long strtol (const char *restrict, char **restrict, int);
unsigned long strtoul (const char *restrict, char **restrict, int);
long long strtoll (const char *restrict, char **restrict, int);
unsigned long long strtoull (const char *restrict, char **restrict, int);

int rand (void);
void srand (unsigned);

void *malloc (size_t);
void *calloc (size_t, size_t);
void *realloc (void *, size_t);
void free (void *);

          void abort (void);
int atexit (void (*) (void));
          void exit (int);
          void _Exit (int);

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));







__attribute__((nonreentrant)) void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

int abs (int);
long labs (long);
long long llabs (long long);

typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;
typedef struct { long long quot, rem; } lldiv_t;

div_t div (int, int);
ldiv_t ldiv (long, long);
lldiv_t lldiv (long long, long long);

typedef struct { unsigned int quot, rem; } udiv_t;
typedef struct { unsigned long quot, rem; } uldiv_t;
udiv_t udiv (unsigned int, unsigned int);
uldiv_t uldiv (unsigned long, unsigned long);
# 3 "StringHandler.c" 2
# 1 "/Applications/microchip/xc8/v2.36/pic/include/c99/string.h" 1 3
# 25 "/Applications/microchip/xc8/v2.36/pic/include/c99/string.h" 3
# 1 "/Applications/microchip/xc8/v2.36/pic/include/c99/bits/alltypes.h" 1 3
# 411 "/Applications/microchip/xc8/v2.36/pic/include/c99/bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 26 "/Applications/microchip/xc8/v2.36/pic/include/c99/string.h" 2 3

void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);
# 65 "/Applications/microchip/xc8/v2.36/pic/include/c99/string.h" 3
char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 4 "StringHandler.c" 2

# 1 "./GCODE.h" 1
# 14 "./GCODE.h"
    typedef struct Comando_T{
       char code;
       float number;
    }Comando_T;
    void G_00(Comando_T* axis, int n);
    void G_53(Comando_T* axis, int n);
# 6 "StringHandler.c" 2

int getTokens(char** token,char* str){
   char s[2]=" ";
   char buffer[20];
   strcpy(buffer,str);
   sprintf(buffer,"%s",str);

   token[0] = strtok(str, s);
   if(token[0]==((void*)0)) return 0;
   int i=0;

   while( token[i] != ((void*)0)) {

      i++;
      token[i] = strtok(((void*)0), s);
   }
   return i+1;
}

void getComands(Comando_T* comandos, char** tokens, int size){
   char buff[10];
   for(int i=0;i<size;i++){
      comandos[i].code=tokens[i][0];
      strcpy(buff, &tokens[i][1]);
 comandos[i].number=strtof(buff,((void*)0));
   }
   return;
}
