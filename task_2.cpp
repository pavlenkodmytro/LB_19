#include <iostream> // Підключення бібліотеки для вводу/виводу (для std::cin, std::cout)
#include <string>   // Підключення бібліотеки для роботи з рядками (для std::string)

int main() {
    std::string password; // Рядок для зберігання введеного пароля

    // Запит та читання пароля (можна додати підказку)
    // std::cout << "Введіть пароль: "; // Підказка для користувача
    std::getline(std::cin, password); // Читаємо весь рядок

    // --- Змінні-прапорці для відстеження виконання правил ---
    bool has_upper = false;     // Прапорець: чи є велика літера
    bool has_lower = false;     // Прапорець: чи є маленька літера
    bool has_digit = false;     // Прапорець: чи є цифра
    bool has_special = false;   // Прапорець: чи є спеціальний символ

    // --- Перевірка символів у паролі ---
    // Цикл для перебору кожного символа 'c' у рядку 'password'
    // password.length() повертає довжину рядка
    for (size_t i = 0; i < password.length(); ++i) {
        char c = password[i]; // Отримуємо символ за індексом i

        // Перевірка, чи є символ великою літерою (від 'A' до 'Z')
        if (c >= 'A' && c <= 'Z') {
            has_upper = true; // Встановити прапорець
        }
        // Інакше, перевірка, чи є символ маленькою літерою (від 'a' до 'z')
        else if (c >= 'a' && c <= 'z') {
            has_lower = true; // Встановити прапорець
        }
        // Інакше, перевірка, чи є символ цифрою (від '0' до '9')
        else if (c >= '0' && c <= '9') {
            has_digit = true; // Встановити прапорець
        }
        // Інакше, вважаємо символ спеціальним, якщо він НЕ літера, НЕ цифра і НЕ пробіл/табуляція
        // Це спрощене визначення "спеціального символу" порівняно з ispunct
        else if ( !( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ' || c == '\t') ) {
            // Якщо символ НЕ (велика АБО маленька АБО цифра АБО пробіл АБО таб)
            has_special = true; // Встановити прапорець
        }
    }

    // --- Перевірка правил та виведення результату ---
    bool is_valid = true; // Загальний прапорець валідності пароля, спочатку вважаємо валідним

    // Перевірка довжини пароля (рівно 8 символів)
    // password.length() - метод класу std::string, повертає довжину рядка (кількість символів)
    if (password.length() != 8) {
        std::cout << "The password must be 8 characters long" << std::endl; // Вивести помилку довжини
        is_valid = false; // Пароль невалідний
    }
    // Перевірка наявності великої літери
    if (!has_upper) {
        std::cout << "The password must have at least one upper case letter" << std::endl; // Вивести помилку
        is_valid = false; // Пароль невалідний
    }
    // Перевірка наявності маленької літери
    if (!has_lower) {
        std::cout << "The password must have at least one lower case letter" << std::endl; // Вивести помилку
        is_valid = false; // Пароль невалідний
    }
    // Перевірка наявності цифри
    if (!has_digit) {
        std::cout << "The password must have at least one digit" << std::endl; // Вивести помилку
        is_valid = false; // Пароль невалідний
    }
    // Перевірка наявності спеціального символа
    if (!has_special) {
        std::cout << "The password must have at least one special character" << std::endl; // Вивести помилку
        is_valid = false; // Пароль невалідний
    }

    // Якщо після всіх перевірок прапорець is_valid залишився true, значить помилок не було
    if (is_valid) {
        std::cout << "The password is valid" << std::endl; // Вивести повідомлення про валідність
    }

    return 0; // Успішне завершення програми
}
