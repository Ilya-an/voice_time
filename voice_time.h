#ifndef VOICE_TIME_H_INCLUDED
#define VOICE_TIME_H_INCLUDED

char* transl_number (char* str_num);
bool find_tail (char *line, char *tail);
char* replace_tail (char *line, char *tail);
char* type_hour (char* str_hour, char* hour);
char* type_min (char* str_min, char* minuts);
void settime (struct tm *u, struct tm *y);

#endif // VOICE_TIME_INCLUDED
