#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "type_word.c"
#include "voice_time.h"


/**
 * @fn set_time
 * @brief Функция для определения времени, его корректной записи и внесения полученной записи в файл
 * 
 * Принимает: указатель на структуру tm - *t, флаг наличния параметра
 * Возвращает: ничего
 * 
 * @param *fd - указатель на открываемый файл
 * @param hour, minute, second - часы, минуты и секунды в числовом формате
 * @param hour_word - склонение слова "час"
 * @param min_word - склонение слова "минута"
 * @param sec_word - склонение слова "секунда"
 * @param str_hour_word - указатель на строку hour_word
 * @param str_min_word - указатель на строку min_word
 * @param str_sec_word - указатель на строку sec_word
 */
void set_time (struct tm *t, bool f_sec)
{
	FILE *fd;
	char hour [10], minute [60], second [70];
	char hour_word [15], min_word [15], sec_word [30];
	char *str_hour_word, *str_min_word, *str_sec_word;
	char *str_minute, *str_second;
	
		
	str_hour_word = hour_word;										/// Создаём указатели на те
	str_min_word = min_word;										/// строки, которые которые мы
	str_sec_word = sec_word;										/// планируем передавать в функции
	
	str_minute = minute;											
	str_minute = second;
	
	/**В следующем блоке кода мы определяем, в какой форме нужно употребить слова "час", "минута" и "секунда" в зависимости от
	 * того, сколько сейчас часов или минут, при помощи функций type_hour, type_min и type_sec. Например, 2 часа, или 12 часов.
	 */
	strftime (hour, 10, "%H", t);									/// Записываем в hour количество часов
	str_hour_word = type_hour (str_hour_word, atoi (hour));
	
	strftime (minute, 60, "%M", t);									/// Записываем в minute количество минут
	str_min_word = type_min (str_min_word, atoi (minute));	
	str_minute = transl_number (atoi (minute), str_minute);
	
	fd = fopen ("/tmp/voice_text.txt", "w");
	
	if (f_sec == false)
	{
		fprintf (fd, "Время - %d %s, %s %s", atoi (hour), str_hour_word, str_minute, str_min_word);
		/// atoi чтобы избавиться от нуля при времени 01
	}
	else
	{
		strftime (second, 60, "%S", t);								/// Записываем в second количество секунд
		str_sec_word = type_sec (str_sec_word, atoi (second));
		str_second = transl_number (atoi (second), str_second);
		
		fprintf (fd, "Время - %d %s, %s %s, %s %s", atoi (hour), str_hour_word, str_minute, str_min_word, str_second, str_sec_word);
	}
	
	fclose (fd);
	fflush (fd);
}

/**
 * @fn transl_number
 * (перевод числа) 
 * @brief Функция для преобразования числа, записанного в цифровом формате, в письменный вид
 * Функция преобразовывает значение строки, в которой хранится число в цифровом формате, в число, записанное в письменном виде.
 * Например, функция преобразует строку "05" в строку "пять", "12" - в "двеннадцать", "45" - в "сорок пять", "66" - в... а ни в чего, 
 * потому что стоит функция будет работать только с числами в диапазоне от 0 до 59, что заключено в рамках программы
 * 
 * Принимает - указатель на строку "str_num"
 * Возвращает:
 * 	1. указатель на строку "str_num", в которой хранится число словами, если всё прошло хорошо
 * 
 * Важно заметить, что для корректной работы функции, строке, на которую указывает указатель, было выделено не менее 60 байт памяти.
 * 
 * @param number - входящее число, преобразованное в тип int
 * @param first_dig, second_dig - первые и вторые цифры числа соответственно
 * @param *dec, *units, *dec_twen - указатели на массивы строк, в которых хранятся все необходимые нам слова 
 */
char* transl_number (int number, char* str_num)
{
	int first_dig, second_dig;
	const char *dec [] = {"десять", "двадцать", "тридцать", "сорок", "пятьдесят"};	
	//const char *units [] = {"ноль", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
	const char *units [] = {"ноль", "одна", "две", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"};
	const char *dec_twen [] = {"одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"};
				
	first_dig = number / 10;					/// В first_dig - первая цифра числа number
	second_dig = number - (first_dig * 10);		/// В second_dig - вторая цифра числа number
	if (first_dig != 0)
		strcpy (str_num, dec [first_dig - 1]);		/// Сначала копируем "десятки"
	else
		return strcpy (str_num, units [second_dig]);/// Если первая цифра равна 0, то можно сразу же возвращать единицы домой
	
	if (first_dig == 1 && second_dig != 0)			/// Проверяем на частный случай чисел диапазона от 11 до 19
		strcpy (str_num, dec_twen [second_dig - 1]);	
	else
		if (second_dig != 0)
		{
			strcat (str_num, " ");					/// Добавляем пробел
			strcat (str_num, units [second_dig]);	/// А затем дописываем единицы
		}
		else if (first_dig == 0)
				strcpy (str_num, units [0]);		/// Пишем 0, когда всё по нулям
	
	return str_num;
}
