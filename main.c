/**@authors Илья Андреев
 * @version 1.0
 * @date 02.02.17
 * @brief Программа для озвучивания текущего времени
 */

#include <stdlib.h>
#include <time.h>

#include "voice_time.c"

/**
 * @fn main
 * @brief Функция для вызова функции settime и вызова программы для озвучки того, что стало результатом работы первой функции
 * Принимает: ничего
 * Возвращает: "0", если всё хорошо и "1", если это не так
 */
int main()
{
	struct tm *u, *y;
	const time_t timer = time (NULL);
	u = localtime (&timer);
	y = localtime (&timer);
	set_time (u, y);
	system ("festival -b '(begin (voice_msu_ru_nsh_clunits) (tts_file \"/tmp/voice_text.txt\"))'");
	return 0;
}
