# simple-text-parser

С++ Полезные функции для работы с текстом с поддержкой UTF8

## Преобразование UTF8 в нижний или верхний регистр

```cpp
std::cout << simple_text_parser::utf8_to_upr_utf8(u8"Вот Это Прикол! That's funny!") << std::endl;
std::cout << simple_text_parser::utf8_to_lwr_utf8(u8"Вот Это Прикол! That's funny!") << std::endl;
```

## Разбиение строки на слова

```cpp
std::string text = u8"Bla Bla Bla\n. Simple text parser";
std::vector<std::string> temp = simple_text_parser::split(text);
for (auto &item : temp) {
	std::cout << item << std::endl;
}
```

## Алгоритм Расстояния Левенштейна с поддержкой UTF8

Расстояние Левенштейна- это строковая метрика для измерения разности между двумя последовательностями. Расстояние Левенштейна между двумя словами-это минимальное количество односимвольных правок (т. е. вставок, удалений или замен), необходимых для изменения одного слова в другое. 

```cpp
std::cout << "date | data: " << simple_text_parser::calc_levenshtein_distance("date", "data") << std::endl;
std::cout << "matata | meta: " << simple_text_parser::calc_levenshtein_distance("matata", "meta") << std::endl;
```

## Сравнение слов в UTF8

```cpp
std::cout << "#0 date | data: " << simple_text_parser::compare_word("date", "data", 0) << std::endl;
std::cout << "#1 date | data: " << simple_text_parser::compare_word("date", "data", 0.1) << std::endl;
std::cout << "#2 botatananima | batatananime: " << simple_text_parser::compare_word("botatananima", "batatananime", 0.15) << std::endl;
std::cout << "#3 botatananima | banatananime: " << simple_text_parser::compare_word("botatananima", "banatananime", 0.15) << std::endl;
```