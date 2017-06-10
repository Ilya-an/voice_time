#ifndef VOICE_TIME_H_INCLUDED
#define VOICE_TIME_H_INCLUDED

//#include "tail.c"

char* transl_number (char* str_num);
char* type_hour (char* str_hour, char* hour);
char* type_min (char* str_min, char* minuts);
void settime (struct tm *u, struct tm *y);

#endif // VOICE_TIME_INCLUDED
