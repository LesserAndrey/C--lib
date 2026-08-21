#include "cmm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <termios.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX_WORK_STRINGS 10
#define MAX_ID_LENGTH 50
#define MAX_TEXT_LENGTH 200

typedef struct {
    char id[MAX_ID_LENGTH];
    char text[MAX_TEXT_LENGTH];
    int line;
} WorkString;

static WorkString work_strings[MAX_WORK_STRINGS];
static int work_count = 0;

int debug_enabled = 0;

// ===== OUTPUT =====
void cmm_say(const char* text) {
    printf("%s", text);
}

void cmm_say_bang(const char* text) {
    printf("%s\n", text);
}

// ===== STRING FUNCTIONS =====
int cmm_strlen(const char* str) {
    return strlen(str);
}

void cmm_strupper(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

void cmm_strlower(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

void cmm_strtrim(char* str) {
    if (str == NULL || str[0] == '\0') {
        return;
    }
    
    int start = 0;
    int end = strlen(str) - 1;
    
    while (str[start] != '\0' && isspace(str[start])) {
        start++;
    }
    
    if (str[start] == '\0') {
        str[0] = '\0';
        return;
    }
    
    while (end > start && isspace(str[end])) {
        end--;
    }
    
    int i;
    for (i = 0; i <= end - start; i++) {
        str[i] = str[start + i];
    }
    str[i] = '\0';
}

// ===== STRING FUNCTIONS (1.1) =====
char* cmm_strfind(const char* str, const char* sub) {
    return strstr(str, sub);
}

int cmm_strfind_pos(const char* str, const char* sub) {
    if (str == NULL || sub == NULL || sub[0] == '\0') {
        return -1;
    }
    
    char* found = strstr(str, sub);
    
    if (found == NULL) {
        return -1;
    }
    
    return found - str;
}

void cmm_strdel(char* str, const char* sub) {
    char* found = strstr(str, sub);
    if (found != NULL) {
        int sub_len = strlen(sub);
        int rest_len = strlen(found + sub_len);
        memmove(found, found + sub_len, rest_len + 1);
    }
}

void cmm_strdelspace(char* str) {
    if (str == NULL) {
        return;
    }
    
    int j = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isspace(str[i])) {
            str[j] = str[i];
            j++;
        }
    }
    
    str[j] = '\0';
}

void cmm_strcat(char* dst, const char* src) {
    strcat(dst, src);
}

void cmm_strcpy(char* dest, char* src) {
    strcpy(dest, src);
}

int cmm_strtoint(const char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10);
    
    if (*endptr != '\0' || endptr == str) {
        printf("GlobalFail Signal 5 (SIGTOSTRING)\n");
        return -1;
    }
    
    return (int)value;
}

// ===== INPUT =====
int cmm_input(void* variable, int type) {
    if (type == CMM_INT) {
        return scanf("%d", (int*)variable);
    }
    else if (type == CMM_STRING) {
        return scanf("%s", (char*)variable);
    }
    else if (type == CMM_FLOAT) {
        return scanf("%f", (float*)variable);
    }
    else if (type == CMM_CHAR) {
        return scanf(" %c", (char*)variable);
    }
    else if (type == CMM_BOOLEAN) {
        char buffer[10];
        int result = scanf("%s", buffer);
        
        if (result == 1) {
            if (strcmp(buffer, "true") == 0) {
                *(int*)variable = 1;
            } else if (strcmp(buffer, "false") == 0) {
                *(int*)variable = 0;
            }
        }
        
        return result;
    }
    else {
        return -1;
    }
}

void cmm_press() {
    while (getchar() != '\n');
}

void cmm_cls() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ===== TIME =====
void cmm_ssleep(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

void cmm_msleep(int ms) {
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

// ===== SIZEOF =====
int cmm_sizeof(void* str) {
    return sizeof(str);
}

// ===== FATAL =====
void cmm_fatal(const char* text) {
    printf("%s\n", text);
    exit(1);
}

// ===== DEBUGGER =====
void cmm_debug_switch(int y_n) {
    if (y_n == 1) {
        debug_enabled = 1;
    }
    else if (y_n == 0) {
        debug_enabled = 0;
    }
}

void cmm_debug(const char* text) {
    if (debug_enabled == 1) {
        printf("%s\n", text);
    }
}

// ===== SAY_WORK =====
void cmm_say_work(const char* id, const char* text) {
    for (int i = 0; i < work_count; i++) {
        if (strcmp(work_strings[i].id, id) == 0) {
            int lines_up = work_count - i;
            
            printf("\033[s");
            printf("\033[%dA", lines_up);
            printf("\r");
            printf("\033[K%s", text);
            printf("\033[u");
            
            fflush(stdout);
            strcpy(work_strings[i].text, text);
            return;
        }
    }
    
    if (work_count < MAX_WORK_STRINGS) {
        strcpy(work_strings[work_count].id, id);
        strcpy(work_strings[work_count].text, text);
        work_strings[work_count].line = work_count;
        work_count++;
        
        printf("%s\n", text);
        fflush(stdout);
    }
}

// ===== TERMINAL =====
void cmm_term_goto(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void cmm_term_tick() {
    printf("\a");
    fflush(stdout);
}

void cmm_term_echo_off() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &term);
}

void cmm_term_echo_on() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ECHO;
    tcsetattr(0, TCSANOW, &term);
}

void cmm_term_icanon_off() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term);
}

void cmm_term_icanon_on() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON;
    tcsetattr(0, TCSANOW, &term);
}

char cmm_term_getch() {
    struct termios old, term;
    tcgetattr(0, &old);
    term = old;
    term.c_lflag &= ~ECHO;
    term.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term);
    
    char c = getchar();
    
    tcsetattr(0, TCSANOW, &old);
    
    return c;
}

void cmm_term_reset() {
    printf("\033[0m");
    fflush(stdout);
}

void cmm_term_color(const char* color) {
    if (strcmp(color, "red") == 0) printf("\033[31m");
    else if (strcmp(color, "green") == 0) printf("\033[32m");
    else if (strcmp(color, "orange") == 0) printf("\033[33m");
    else if (strcmp(color, "blue") == 0) printf("\033[34m");
    else if (strcmp(color, "purple") == 0) printf("\033[35m");
    else if (strcmp(color, "pink") == 0) printf("\033[95m");
    else if (strcmp(color, "cyan") == 0) printf("\033[36m");
    else if (strcmp(color, "gray") == 0) printf("\033[90m");
    else if (strcmp(color, "white") == 0) printf("\033[37m");
    else if (strcmp(color, "0") == 0) printf("\033[0m");
}

void cmm_term_color_rgb(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void cmm_term_color_hex(const char* hex) {
    if (hex[0] == '#') hex++;
    
    int r, g, b;
    sscanf(hex, "%02x%02x%02x", &r, &g, &b);
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void cmm_term_input_with(const char* symbol, const char* var, int type) {
    struct termios old, term;
    tcgetattr(0, &old);
    term = old;
    term.c_lflag &= ~ECHO;
    tcsetattr(0, TCSANOW, &term);
    
    char buffer[500];
    int i = 0;
    char ch;
    
    while ((ch = getchar()) != '\n' && i < 499) {
        buffer[i] = ch;
        i++;
        printf("%s", symbol);
        fflush(stdout);
    }
    
    buffer[i] = '\0';
    
    tcsetattr(0, TCSANOW, &old);
    printf("\n");
    
    if (type == CMM_INT) {
        *(int*)var = atoi(buffer);
    }
    else if (type == CMM_STRING) {
        strcpy((char*)var, buffer);
    }
    else if (type == CMM_FLOAT) {
        *(float*)var = atof(buffer);
    }
    else if (type == CMM_CHAR) {
        *(char*)var = buffer[0];
    }
}

// ===== MEM_* =====
void* cmm_mem_alloc(int type, int size) {
    int type_size = 0;
    
    if (type == CMM_INT) type_size = sizeof(int);
    else if (type == CMM_STRING) type_size = sizeof(char);
    else if (type == CMM_FLOAT) type_size = sizeof(float);
    else if (type == CMM_CHAR) type_size = sizeof(char);
    else if (type == CMM_BOOLEAN) type_size = sizeof(bool);
    
    return malloc(type_size * size);
}

void cmm_mem_free(void* ptr) {
    free(ptr);
}

void cmm_mem_cpy(void* dst, void* src, int n) {
    memcpy(dst, src, n);
}

int cmm_mem_cmp(void* a, void* b, int n) {
    return memcmp(a, b, n);
}

void cmm_mem_set(void* dst, const char* chr, int n) {
    memset(dst, chr[0], n);
}

void cmm_mem_ccpy(void* dst, void* src, const char* chr, int n) {
    char* d = (char*)dst;
    char* s = (char*)src;
    char stop = chr[0];
    
    for (int i = 0; i < n; i++) {
        d[i] = s[i];
        if (s[i] == stop) break;
    }
}

// ===== STOPWATCH =====
float cmm_stop_watch(int y_n) {
    static clock_t start_time = 0;
    
    if (y_n == 1) {
        start_time = clock();
        return 0;
    }
    else if (y_n == 0) {
        clock_t end_time = clock();
        float elapsed = (float)(end_time - start_time) / CLOCKS_PER_SEC;
        return elapsed;
    }
    
    return -1;
}
