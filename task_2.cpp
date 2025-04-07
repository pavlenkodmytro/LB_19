#include <iostream> // Підключення бібліотеки для вводу/виводу (для std::cin, std::cout) (Connecting library for input/output (for std::cin, std::cout))
#include <string>   // Підключення бібліотеки для роботи з рядками (для std::string) (Connecting library for working with strings (for std::string))
#include <vector>   // Підключення бібліотеки для роботи з векторами (для зберігання списку помилок) (Connecting library for working with vectors (for storing the list of errors))
#include <cctype>   // Підключення бібліотеки для функцій перевірки типу символів (наприклад, isupper, islower, isdigit, ispunct) (Connecting library for character type checking functions (e.g., isupper, islower, isdigit, ispunct))

int main() {
    std::string password; // Рядок для зберігання введеного пароля (String to store the entered password)

    // Запит на введення пароля (Prompt for password input)
    // std::cout << "Enter password: "; // Можна додати підказку користувачу (You can add a prompt for the user)

    // Читання всього рядка (пароля) з стандартного вводу (Reading the entire line (password) from standard input)
    std::getline(std::cin, password);

    // --- Змінні-прапорці для відстеження виконання правил --- (Flag variables to track rule compliance)
    bool has_upper = false;   // Прапорець: чи є хоча б одна велика літера (Flag: is there at least one uppercase letter)
    bool has_lower = false;   // Прапорець: чи є хоча б одна маленька літера (Flag: is there at least one lowercase letter)
    bool has_digit = false;   // Прапорець: чи є хоча б одна цифра (Flag: is there at least one digit)
    bool has_special = false; // Прапорець: чи є хоча б один спеціальний символ (Flag: is there at least one special character)
    // Перевірка довжини пароля (Checking the password length)
    bool correct_length = (password.length() == 8); // Прапорець: чи правильна довжина пароля (рівно 8 символів) (Flag: is the password length correct (exactly 8 characters))

    // --- Перевірка символів у паролі --- (Checking characters in the password)
    // Цикл для перебору кожного символа 'c' у рядку 'password' (Loop to iterate over each character 'c' in the 'password' string)
    for (char c : password) {
        // Перевірка, чи є символ великою літерою (Check if the character is uppercase)
        if (std::isupper(c)) {
            has_upper = true; // Якщо так, встановити відповідний прапорець (If yes, set the corresponding flag)
        }
        // Інакше, перевірка, чи є символ маленькою літерою (Otherwise, check if the character is lowercase)
        else if (std::islower(c)) {
            has_lower = true; // Якщо так, встановити відповідний прапорець (If yes, set the corresponding flag)
        }
        // Інакше, перевірка, чи є символ цифрою (Otherwise, check if the character is a digit)
        else if (std::isdigit(c)) {
            has_digit = true; // Якщо так, встановити відповідний прапорець (If yes, set the corresponding flag)
        }
        // Інакше, перевірка, чи є символ розділовим знаком (вважаємо це спеціальним символом) (Otherwise, check if the character is a punctuation mark (consider this a special character))
        // ispunct перевіряє на символи типу !, ?, ., ,, #, [, ] тощо. (ispunct checks for characters like !, ?, ., ,, #, [, ], etc.)
        else if (std::ispunct(c)) {
            has_special = true; // Якщо так, встановити відповідний прапорець (If yes, set the corresponding flag)
        }
        // Можна додати інші перевірки для ширшого визначення "спеціальних символів", якщо потрібно
        // (You can add other checks for a broader definition of "special characters" if needed)
        // Наприклад, !std::isalnum(c) && !std::isspace(c) перевірить на будь-який символ, що не є літерою, цифрою або пробілом
        // (For example, !std::isalnum(c) && !std::isspace(c) checks for any character that is not a letter, digit, or space)
    }

    // --- Збір повідомлень про помилки --- (Collecting error messages)
    std::vector<std::string> errors; // Вектор (динамічний масив) для зберігання текстових повідомлень про помилки (Vector (dynamic array) to store textual error messages)

    // Додавання повідомлень про помилки до вектору, якщо відповідне правило не виконано (Adding error messages to the vector if the corresponding rule is not met)
    if (!correct_length) { // Якщо довжина неправильна (If the length is incorrect)
        errors.push_back("The password must be 8 characters long"); // Додати повідомлення про помилку довжини (Add the length error message)
    }
    if (!has_upper) { // Якщо немає великої літери (If there is no uppercase letter)
        errors.push_back("The password must have at least one upper case letter"); // Додати повідомлення про відсутність великої літери (Add the missing uppercase letter message)
    }
    if (!has_lower) { // Якщо немає маленької літери (If there is no lowercase letter)
        errors.push_back("The password must have at least one lower case letter"); // Додати повідомлення про відсутність маленької літери (Add the missing lowercase letter message)
    }
    if (!has_digit) { // Якщо немає цифри (If there is no digit)
        errors.push_back("The password must have at least one digit"); // Додати повідомлення про відсутність цифри (Add the missing digit message)
    }
    if (!has_special) { // Якщо немає спеціального символа (If there is no special character)
        errors.push_back("The password must have at least one special character"); // Додати повідомлення про відсутність спеціального символа (Add the missing special character message)
    }

    // --- Виведення результату валідації --- (Printing the validation result)
    // Перевірка, чи є помилки у векторі (Check if there are any errors in the vector)
    if (errors.empty()) {
        // Якщо вектор помилок порожній, це означає, що всі правила виконані і пароль валідний (If the error vector is empty, it means all rules are met and the password is valid)
        std::cout << "The password is valid" << std::endl; // Вивести повідомлення про валідність (Print the validity message)
    } else {
        // Інакше (якщо вектор помилок не порожній), вивести всі зібрані повідомлення про помилки (Otherwise (if the error vector is not empty), print all collected error messages)
        // Цикл для проходу по кожному рядку 'error' у векторі 'errors' (Loop to go through each string 'error' in the 'errors' vector)
        for (const std::string& error : errors) {
            std::cout << error << std::endl; // Вивести поточне повідомлення про помилку (Print the current error message)
        }
    }

    // Повернення 0 означає успішне завершення програми (Returning 0 indicates successful program termination)
    return 0;
}
