#include <iostream> // Підключення бібліотеки для вводу/виводу (наприклад, std::cout, std::cin) (Connecting library for input/output (e.g., std::cout, std::cin))
#include <string>   // Підключення бібліотеки для роботи з рядками (std::string) (Connecting library for working with strings (std::string))
#include <vector>   // Підключення бібліотеки для роботи з динамічними масивами (векторами) (Connecting library for working with dynamic arrays (vectors))
#include <sstream>  // Підключення бібліотеки для роботи з рядковими потоками (для парсингу) (Connecting library for working with string streams (for parsing))
#include <map>      // Підключення бібліотеки для роботи зі словниками (асоціативними масивами) (Connecting library for working with maps (associative arrays))

// Функція для розділення рядка за заданим роздільником
// Function to split a string by a given delimiter
std::vector<std::string> split(const std::string& s, char delimiter) {
   std::vector<std::string> tokens; // Вектор для зберігання отриманих частин рядка (Vector to store the obtained parts of the string)
   std::string token; // Тимчасовий рядок для зберігання однієї частини (Temporary string to store one part)
   std::istringstream tokenStream(s); // Створення рядкового потоку з вхідного рядка (Creating a string stream from the input string)
   // Цикл для читання частин рядка до роздільника (Loop to read parts of the string up to the delimiter)
   while (std::getline(tokenStream, token, delimiter)) {
      tokens.push_back(token); // Додавання отриманої частини до вектору (Adding the obtained part to the vector)
   }
   return tokens; // Повернення вектору з частинами рядка (Returning the vector with parts of the string)
}

int main() {
    // --- Читання вхідних даних --- (Reading input data)
    std::string values_line; // Рядок для зберігання першого рядка вводу (пар ім'я-значення) (String to store the first input line (name-value pairs))
    // Читання першого рядка цілком (включно з пробілами) (Reading the first line entirely (including spaces))
    std::getline(std::cin, values_line);

    std::string template_str; // Рядок для зберігання другого рядка вводу (шаблону) (String to store the second input line (the template))
    // Читання другого рядка цілком (Reading the second line entirely)
    std::getline(std::cin, template_str);

    // --- Обробка пар ім'я-значення --- (Processing name-value pairs)
    std::map<std::string, std::string> values_map; // Створення словника (map) для зберігання пар ім'я-значення (Creating a map to store name-value pairs)
    // Розділення першого рядка на окремі пари за допомогою коми (Splitting the first line into individual pairs using a comma)
    std::vector<std::string> pairs = split(values_line, ',');

    // Цикл для обробки кожної пари (Loop to process each pair)
    for (const std::string& pair_str : pairs) {
        size_t separator_pos = std::string::npos; // Позиція роздільника ('-' або '=') (Position of the separator ('-' or '='))
        // Спочатку шукаємо роздільник '-' (First, search for the '-' separator)
        separator_pos = pair_str.find('-');
        // Якщо '-' не знайдено, шукаємо роздільник '=' (If '-' is not found, search for the '=' separator)
        if (separator_pos == std::string::npos) {
            separator_pos = pair_str.find('=');
        }

        // Перевірка, чи знайдено роздільник (Checking if a separator was found)
        if (separator_pos != std::string::npos) {
            // Виділення імені (частина рядка до роздільника) (Extracting the name (part of the string before the separator))
            std::string name = pair_str.substr(0, separator_pos);
            // Виділення значення (частина рядка після роздільника) (Extracting the value (part of the string after the separator))
            std::string value = pair_str.substr(separator_pos + 1);

            // --- Видалення зайвих пробілів (необов'язково, але корисно) --- (Removing extra spaces (optional, but useful))
            // Пошук першого символу, який не є пробілом (Finding the first non-space character)
            size_t first_char = name.find_first_not_of(" \t");
            // Якщо такі символи є, видаляємо пробіли на початку (If such characters exist, remove leading spaces)
            if (std::string::npos != first_char) {
                name = name.substr(first_char);
            }
             // Пошук останнього символу, який не є пробілом (Finding the last non-space character)
            size_t last_char = name.find_last_not_of(" \t");
             // Якщо такі символи є, видаляємо пробіли в кінці (If such characters exist, remove trailing spaces)
            if (std::string::npos != last_char) {
                name = name.substr(0, last_char + 1);
            }
            // Повторюємо для значення (Repeat for the value)
            first_char = value.find_first_not_of(" \t");
            if (std::string::npos != first_char) {
                value = value.substr(first_char);
            }
            last_char = value.find_last_not_of(" \t");
            if (std::string::npos != last_char) {
                value = value.substr(0, last_char + 1);
            }
            // --- Кінець видалення пробілів --- (End of space removal)

            // Додавання пари ім'я-значення до словника (Adding the name-value pair to the map)
            values_map[name] = value;
        }
        // Якщо роздільник не знайдено в парі, ігноруємо цю пару (If the separator is not found in the pair, ignore this pair)
    }

    // --- Заповнення шаблону --- (Filling the template)
    std::string result = ""; // Рядок для формування кінцевого результату (String to build the final result)
    size_t current_pos = 0; // Поточна позиція для обробки рядка шаблону (Current position for processing the template string)

    // Цикл обробки рядка шаблону (Loop for processing the template string)
    while (current_pos < template_str.length()) {
        // Пошук позиції наступної відкриваючої дужки '[' починаючи з поточної позиції (Finding the position of the next opening bracket '[' starting from the current position)
        size_t open_bracket_pos = template_str.find('[', current_pos);

        // Якщо відкриваючу дужку не знайдено до кінця рядка (If the opening bracket is not found until the end of the string)
        if (open_bracket_pos == std::string::npos) {
            // Додати залишок рядка шаблону до результату (Append the remainder of the template string to the result)
            result += template_str.substr(current_pos);
            // Завершити цикл (Terminate the loop)
            break;
        } else {
             // Додати текст, що знаходиться перед відкриваючою дужкою, до результату (Append the text located before the opening bracket to the result)
            result += template_str.substr(current_pos, open_bracket_pos - current_pos);

            // Пошук позиції відповідної закриваючої дужки ']' після відкриваючої (Finding the position of the corresponding closing bracket ']' after the opening one)
            size_t close_bracket_pos = template_str.find(']', open_bracket_pos + 1);

            // Якщо закриваючу дужку не знайдено (If the closing bracket is not found)
            if (close_bracket_pos == std::string::npos) {
                // Вважаємо відкриваючу дужку звичайним символом і додаємо її до результату (Consider the opening bracket as a regular character and add it to the result)
                result += '[';
                // Оновлюємо поточну позицію, щоб продовжити пошук після цієї дужки (Update the current position to continue searching after this bracket)
                current_pos = open_bracket_pos + 1;
            } else {
                // Якщо знайдено обидві дужки - виділяємо ім'я плейсхолдера (If both brackets are found - extract the placeholder name)
                std::string placeholder_name = template_str.substr(open_bracket_pos + 1, close_bracket_pos - open_bracket_pos - 1);

                // Пошук імені плейсхолдера у словнику значень (Searching for the placeholder name in the values map)
                // values_map.find() повертає ітератор на елемент, якщо знайдено, або values_map.end(), якщо не знайдено (values_map.find() returns an iterator to the element if found, or values_map.end() if not found)
                auto it = values_map.find(placeholder_name);

                // Перевірка, чи знайдено ім'я у словнику (Checking if the name was found in the map)
                if (it != values_map.end()) {
                    // Якщо знайдено, додати відповідне значення (з словника) до результату (If found, append the corresponding value (from the map) to the result)
                    // it->second - це значення, що відповідає ключу (it->second is the value corresponding to the key)
                    result += it->second;
                } else {
                    // Якщо ім'я НЕ знайдено у словнику (If the name is NOT found in the map)
                    // Додати оригінальний плейсхолдер (включно з дужками) до результату (Append the original placeholder (including brackets) to the result)
                     result += template_str.substr(open_bracket_pos, close_bracket_pos - open_bracket_pos + 1);
                }
                // Оновлюємо поточну позицію, щоб продовжити пошук після обробленого плейсхолдера (Update the current position to continue searching after the processed placeholder)
                current_pos = close_bracket_pos + 1;
            }
        }
    }

    // --- Виведення результату --- (Printing the result)
    // Виведення кінцевого рядка з переведенням на новий рядок (Printing the final string followed by a newline)
    std::cout << result << std::endl; // std::endl також очищує буфер виводу (std::endl also flushes the output buffer)

    // Повернення 0 означає успішне завершення програми (Returning 0 indicates successful program termination)
    return 0;
}
