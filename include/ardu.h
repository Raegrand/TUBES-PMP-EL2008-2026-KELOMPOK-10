// wrapper.h
#ifndef ARDU_H
#define ARDU_H

#ifdef __cplusplus
extern "C" {
#endif

void init_hardware(void);
void c_print(const char* text);
void c_println(const char* text);

#ifdef __cplusplus
}
#endif

#endif