#include <iostream>
#include "windows.h"
#include "ball_list.h"

void print_menu();


// обработка исключений/ошибок ввода
int get_safe_int(const std::string& input) {
    int value;
    while (true) {
        std::cout << input;
        if (std::cin >> value) {
            return value;
        } else {
            std::cout << "Ошибка ввода. Введите корректное число.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            print_menu();
        }
    }
}

void print_menu() {
    std::cout << "МЕНЮ: \n";
    std::cout << "1. Ввести новую цепочку шариков вручную\n";
    std::cout << "0. Выход из программы\n";
}

// основной алгоритм симуляции уничтожения шариков
void run_simulation(BallList& list) {
    std::cout << "Исходная последовательность: " << list.to_string() << "\n";
    int result = list.simulate_game();
    std::cout << "Количество уничтоженных шариков: " << result << "\n";
    std::cout << "Оставшаяся последовательность: " << list.to_string() << "\n\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int choice;

    do {
        print_menu();
        choice = get_safe_int("Выберите пункт меню: ");

        switch (choice) {

            case 1: {
                BallList user_list;
                int count = get_safe_int("Введите количество шариков: ");
                if (count <= 0 || count > 100000) {
                    std::cout << "Количество должно быть больше 0 или не более 10^5.\n";
                    continue;
                }

                std::cout << "Введите " << count << " цветов (цифры от 0 до 9 через пробел): ";
                bool input_error = false;

                for (int i = 0; i < count; i++) {
                    std::string token;
                    std::cin >> token;

                    // валидация: строка должна состоять ровно из 1 символа и этот символ должен быть цифрой
                    if (token.length() != 1 || token[0] < '0' || token[0] > '9') {
                        std::cout << "\nОшибка: обнаружен некорректный элемент '" << token << "'. Цвет должен быть цифрой от 0 до 9.\n";
                        input_error = true;

                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        break;
                    }

                    int color = token[0] - '0'; // перевод символа в число

                    try {
                        user_list.push_back(color);
                    } catch (const std::invalid_argument& e) {
                        std::cout << "\n" << e.what() << "\n";
                        input_error = true;

                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        break;
                    }
                }

                if (!input_error) {
                    run_simulation(user_list);
                } else {
                    std::cout << "Попробуйте ввести цепочку заново.\n";
                }
            }
            case 0: {
                std::cout << "Программа завершена.\n";
                break;
            }
            default:
                std::cout << "Неверный пункт меню. Попробуйте снова.\n";;
        }
    } while (choice != 0);
}