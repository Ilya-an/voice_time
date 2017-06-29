/**@authors Илья Андреев
 * @version 1.2
 * @date 02.02.17
 * @brief Программа для озвучивания текущего времени
 */

#include <stdlib.h>
#include <time.h>

#include "voice_time.c"

/**
 * @fn main
 * @brief Функция для вызова функции set_time и вызова программы для озвучки того, что стало результатом работы первой функции
 * Принимает: параметр -s
 * Возвращает: "0", если всё хорошо и "1", если это не так
 */
int main(int argc, char *argv[])
{
	struct tm *t;
	const time_t timer = time (NULL);
	bool f_sec = false;
	
	if (argc == 2)
	{
		if (strcmp ("-s", argv [1]) == 0)
		{
			f_sec = true;
		}
	}
	
	t = localtime (&timer);
	set_time (t, f_sec);
	system ("festival -b '(begin (voice_msu_ru_nsh_clunits) (tts_file \"/tmp/voice_text.txt\"))'");
	return 0;
}
