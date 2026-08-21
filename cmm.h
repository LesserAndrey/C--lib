#ifndef CMM_H
#define CMM_H

// ===== types =====
#define CMM_INT 0
#define CMM_STRING 1
#define CMM_FLOAT 2
#define CMM_CHAR 3
#define CMM_BOOLEAN 4

// ===== output =====
void cmm_say(const char* text);
void cmm_say_bang(const char* text);

// ===== string_functions =====
int cmm_strlen(const char* str);
void cmm_strupper(char* str);
void cmm_strlower(char* str);
void cmm_strtrim(char* str);

// ===== string functions (1.1) =====
char* cmm_strfind(const char* str, const char* sub);
int cmm_strfind_pos(const char* str, const char* sub);
void cmm_strdel(char* str, const char* sub);
void cmm_strdelspace(char* str);
void cmm_strcat(char* dst, const char* src);
void cmm_strcpy(char* dest, char* src);
int cmm_strtoint(const char* str);

// ===== input =====
int cmm_input(void* variable, int type);
void cmm_press();
void cmm_cls();

// ===== time =====
void cmm_ssleep(int seconds);
void cmm_msleep(int ms);

// ===== sizeof =====
int cmm_sizeof(void* str);

// ===== fatal =====
void cmm_fatal(const char* msg);

// ===== debugger =====
void cmm_debug_switch(int y_n);
void cmm_debug(const char* str);

// ===== stopwatch =====
float cmm_stop_watch(int y_n);

// ===== say_work =====
void cmm_say_work(const char* id, const char* txt);

// ===== terminal functions =====
void cmm_term_echo_on();
void cmm_term_echo_off();
void cmm_term_icanon_on();
void cmm_term_icanon_off();
char cmm_term_getch();
void cmm_term_goto(int x, int y);
void cmm_term_reset();
void cmm_term_color(const char* color);
void cmm_term_color_rgb(const char* r, const char* g, const char* b);
void cmm_term_color_hex(const char* hex);
void cmm_term_get_button(const char* key);
void cmm_term_tick();
void cmm_term_input_with(const char* symbol, const char* var, int type);

// ===== mem_* =====
void* cmm_mem_alloc(int type, int size);
void cmm_mem_free(void* ptr);
void cmm_mem_cpy(void* dst, void* src, int n);
int cmm_mem_cmp(void* a, void* b, int n);
void cmm_mem_set(void* dst, const char* chr, int n);
void cmm_mem_ccpy(void* dst, void* src, const char* chr, int n);

#endif
