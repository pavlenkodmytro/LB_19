#include <string>   // Подключаем библиотеку для работы со строками (клас std::string)
#include <iostream> // Подключаем библиотеку для ввода/вывода (std::cin, std::cout)

// --- Вспомогательная функция для удаления пробелов в начале и конце строки ---
// Эта функция принимает строку и возвращает новую строку без лишних пробелов по краям.
std::string manual_trim(const std::string& str) { // Объявляем функцию manual_trim, принимающую константную ссылку на строку str
    if (str.empty()) {                          // Проверяем, не пустая ли строка
        return "";                              // Если строка пустая, возвращаем пустую строку
    }
    size_t first = 0;                           // Создаем переменную first (индекс первого символа) и инициализируем нулем

    // Ищем индекс первого символа, который не является пробелом или табуляцией
    // std::string::length() - возвращает длину строки (количество символов)
    while (first < str.length() && (str[first] == ' ' || str[first] == '\t')) { // Цикл: пока first меньше длины строки И символ str[first] - это пробел ИЛИ табуляция
        first++;                                // Увеличиваем first на 1, переходя к следующему символу
    }

    // Если вся строка состояла из пробелов, first станет равен длине строки
    if (first == str.length()) {                // Проверяем, дошли ли мы до конца строки, не найдя непробельных символов
        return "";                              // Если да, значит строка была пустой или из одних пробелов, возвращаем пустую строку
    }

    size_t last = str.length() - 1;             // Создаем переменную last (индекс последнего символа) и инициализируем последним индексом строки

    // Ищем индекс последнего символа, который не является пробелом или табуляцией (двигаясь с конца)
    // Условие last > first важно, чтобы индексы не "пересеклись", если непробельный символ всего один
    while (last > first && (str[last] == ' ' || str[last] == '\t')) { // Цикл: пока last больше first И символ str[last] - это пробел ИЛИ табуляция
        last--;                                 // Уменьшаем last на 1, переходя к предыдущему символу
    }

    // std::string::substr(pos, count) - возвращает подстроку, начиная с индекса pos длиной count символов.
    // Здесь мы вырезаем часть строки от первого непробельного символа (first) до последнего (last).
    // Длина подстроки вычисляется как (last - first + 1).
    return str.substr(first, last - first + 1); // Возвращаем подстроку от first до last включительно
}

// --- Вспомогательная функция для поиска значения по ключу в строке пар "ключ-значение" ---
// Эта функция ищет ключ key_to_find в строке values_line, которая содержит пары вида "ключ=значение" или "ключ-значение", разделенные запятыми.
// Она возвращает найденное значение (уже "оттримленное").
// Параметр found (передается по ссылке) устанавливается в true, если ключ был найден, иначе остается false.
std::string find_value_manually(const std::string& values_line, // Входная строка с парами ключ-значение
                                const std::string& key_to_find, // Ключ, который мы ищем
                                bool& found)                   // Флаг (передается по ссылке), указывающий, найден ли ключ
{
    size_t current_pos = 0;                      // Индекс, с которого начинаем поиск следующей пары (изначально 0)
    found = false;                               // Сбрасываем флаг "найдено" в false перед началом поиска

    // Цикл продолжается, пока мы не обработаем всю строку values_line
    while (current_pos < values_line.length()) { // Пока текущая позиция меньше длины строки

        // --- Ищем конец текущей пары (запятую или конец строки) ---
        // std::string::find(char, pos) - ищет первое вхождение символа char, начиная с позиции pos.
        // Возвращает индекс найденного символа или специальное значение std::string::npos, если символ не найден.
        size_t comma_pos = values_line.find(',', current_pos); // Ищем запятую, начиная с current_pos

        if (comma_pos == std::string::npos) {   // Если запятая не найдена (find вернул npos)
            comma_pos = values_line.length();   // Считаем концом пары конец всей строки values_line
        }

        // --- Извлекаем подстроку, содержащую текущую пару ---
        // std::string::substr(pos, count) - извлекает подстроку с индекса pos длиной count.
        std::string pair_str = values_line.substr(current_pos, comma_pos - current_pos); // Вырезаем подстроку от current_pos до comma_pos

        // --- Ищем разделитель ('-' или '=') внутри извлеченной пары ---
        size_t sep_pos = std::string::npos;     // Инициализируем позицию разделителя как "не найдено" (npos)
        // Ищем '-' в подстроке pair_str, начиная с индекса 0
        size_t dash_pos = pair_str.find('-');
        // Ищем '=' в подстроке pair_str, начиная с индекса 0
        size_t equals_pos = pair_str.find('=');

        // Определяем реальную позицию разделителя (берем тот, что раньше, если есть оба)
        if (dash_pos != std::string::npos && equals_pos != std::string::npos) { // Если найдены и '-' и '='
            sep_pos = (dash_pos < equals_pos) ? dash_pos : equals_pos; // Выбираем тот, который находится левее (меньший индекс)
        } else if (dash_pos != std::string::npos) { // Если найден только '-'
            sep_pos = dash_pos;                 // Используем позицию '-'
        } else {                                // Иначе (если найден только '=' или ни один не найден)
            sep_pos = equals_pos;               // Используем позицию '=' (может быть npos, если и его нет)
        }

        // --- Если разделитель найден, извлекаем ключ и значение ---
        if (sep_pos != std::string::npos) {     // Проверяем, был ли найден разделитель ('-' или '=')
            // Извлекаем ключ: подстрока от начала pair_str до разделителя sep_pos
            std::string current_key_raw = pair_str.substr(0, sep_pos);
            // Извлекаем значение: подстрока от символа ПОСЛЕ разделителя (sep_pos + 1) до конца pair_str
            std::string current_value_raw = pair_str.substr(sep_pos + 1);

            // Очищаем ключ и значение от лишних пробелов с помощью нашей функции manual_trim
            std::string current_key = manual_trim(current_key_raw);
            std::string current_value = manual_trim(current_value_raw);

            // --- Сравниваем найденный ключ с тем, который мы ищем ---
            // Проверяем, что ключ не пустой после очистки И он совпадает с искомым key_to_find
            if (!current_key.empty() && current_key == key_to_find) {
                found = true;                   // Устанавливаем флаг "найдено" в true
                return current_value;           // Возвращаем найденное и очищенное значение (и выходим из функции)
            }
        }

        // --- Переходим к началу следующей пары ---
        current_pos = comma_pos + 1;             // Устанавливаем текущую позицию на символ после найденной запятой

        // Пропускаем возможные пробелы после запятой, чтобы следующая итерация началась с символа пары
        while (current_pos < values_line.length() && values_line[current_pos] == ' ') { // Пока не конец строки и текущий символ пробел
             current_pos++;                      // Передвигаем позицию вперед
        }
    }

    // Если мы прошли весь цикл и не вышли из функции раньше (через return), значит ключ не был найден
    return "";                                   // Возвращаем пустую строку, так как значение не найдено (found останется false)
}


// --- Основная функция программы ---
int main() {
    std::string values_line;                     // Объявляем строку для хранения первой строки ввода (пары ключ-значение)
    // std::getline(std::cin, str) - читает всю строку из стандартного ввода (cin) до символа новой строки '\n' и сохраняет ее в строку str.
    std::getline(std::cin, values_line);         // Читаем первую строку ввода

    std::string template_str;                    // Объявляем строку для хранения второй строки ввода (шаблона)
    std::getline(std::cin, template_str);        // Читаем вторую строку ввода

    std::string result = "";                     // Объявляем строку для формирования итогового результата, инициализируем пустой строкой
    size_t current_pos = 0;                      // Индекс в строке шаблона, с которого начинаем обработку на каждой итерации

    // --- Цикл обработки строки шаблона ---
    while (current_pos < template_str.length()) { // Пока текущая позиция меньше длины шаблона

        // --- Ищем следующую открывающую квадратную скобку '[' ---
        // template_str.find('[', current_pos) - ищет '[' начиная с позиции current_pos
        size_t open_bracket_pos = template_str.find('[', current_pos);

        // --- Если '[' не найдена ---
        if (open_bracket_pos == std::string::npos) { // Проверяем, вернул ли find значение npos (не найдено)
            // Добавляем оставшуюся часть шаблона к результату
            // template_str.substr(current_pos) - возвращает подстроку от current_pos до конца строки
            result += template_str.substr(current_pos); // Дописываем хвост шаблона в результат
            break;                                  // Выходим из цикла while, так как больше плейсхолдеров нет
        }
        // --- Если '[' найдена ---
        else {
            // --- Добавляем текст перед '[' к результату ---
            // template_str.substr(current_pos, count) - возвращает подстроку от current_pos длиной count символов
            // Длина текста перед скобкой: open_bracket_pos - current_pos
            result += template_str.substr(current_pos, open_bracket_pos - current_pos); // Дописываем текст до '['

            // --- Ищем соответствующую закрывающую скобку ']' ---
            // template_str.find(']', pos) - ищет ']' начиная с позиции pos.
            // Ищем ПОСЛЕ открывающей скобки, поэтому начинаем с open_bracket_pos + 1
            size_t close_bracket_pos = template_str.find(']', open_bracket_pos + 1);

            // --- Если ']' не найдена после '[' ---
            if (close_bracket_pos == std::string::npos) { // Проверяем, найдена ли закрывающая скобка
                // Считаем '[' обычным символом и добавляем его к результату
                result += '[';                      // Добавляем сам символ '[' в результат
                // Обновляем текущую позицию, чтобы продолжить поиск ПОСЛЕ этого символа '['
                current_pos = open_bracket_pos + 1; // Передвигаем позицию за обработанный '['
            }
            // --- Если найдены и '[' и ']' ---
            else {
                // --- Извлекаем имя плейсхолдера (текст между скобками) ---
                // Длина имени: close_bracket_pos - (open_bracket_pos + 1)
                //               = close_bracket_pos - open_bracket_pos - 1
                std::string placeholder_name = template_str.substr(open_bracket_pos + 1, close_bracket_pos - open_bracket_pos - 1);

                // --- Ищем значение для этого плейсхолдера в строке values_line ---
                bool key_was_found = false;         // Флаг для функции find_value_manually
                // Вызываем нашу вспомогательную функцию для поиска значения
                std::string value_to_insert = find_value_manually(values_line, placeholder_name, key_was_found);

                // --- Добавляем значение или сам плейсхолдер в результат ---
                if (key_was_found) {                // Если функция поиска установила флаг found в true
                    result += value_to_insert;      // Добавляем найденное значение в результат
                } else {                            // Если ключ не был найден
                    // Добавляем оригинальный плейсхолдер (включая скобки) обратно в результат
                    // template_str.substr(pos, count) - извлекаем подстроку от '[' до ']' включительно
                    // Длина: close_bracket_pos - open_bracket_pos + 1
                    result += template_str.substr(open_bracket_pos, close_bracket_pos - open_bracket_pos + 1);
                }

                // --- Обновляем текущую позицию для следующей итерации ---
                // Устанавливаем позицию на символ ПОСЛЕ закрывающей скобки ']'
                current_pos = close_bracket_pos + 1; // Передвигаем позицию за обработанный плейсхолдер
            }
        }
    }

    // --- Вывод результата ---
    // std::cout << ... - выводит данные в стандартный вывод (консоль)
    // std::endl - выводит символ новой строки и сбрасывает буфер вывода (гарантирует, что все будет выведено сразу)
    std::cout << result << std::endl;           // Печатаем итоговую строку в консоль

    return 0;                                    // Возвращаем 0 из main, что означает успешное завершение программы
}
