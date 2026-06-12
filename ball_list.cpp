#include "ball_list.h"
#include <iostream>
#include <sstream>
BallList::BallList() : head(nullptr), tail(nullptr), count(0) {}

BallList::~BallList() {
    clear();
}

void BallList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = tail = nullptr;
    count = 0;
}

void BallList::push_back(int color) {
    if (color < 0 || color > 9) {
        throw std::invalid_argument("Ошибка: цвет шарика должен быть цифрой от 0 до 9.\n");
    }
    Node* newNode = new Node(color);
    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

bool BallList::is_empty() const {
    return head == nullptr;
}

int BallList::get_count() const {
    return count;
}

std::string BallList::to_string() const {
    if (is_empty()) { return  "[Пусто]"; }
    std::stringstream ss;
    Node* current = head;
    while (current != nullptr) {
        ss << current->color << " ";
        current = current->next;
    }
    return ss.str();
}

// алгоритм уничтожения шариков
int BallList::simulate_game() {
    int destroyed_total = 0;
    bool triggered = true;

    while (triggered) {
        triggered = false;
        Node* current = head;

        while (current != nullptr) {
            Node* run = current;
            int match_count = 0;

            // счет длины непрерывной цепочки одного цвета
            while (run != nullptr && run->color == current->color) {
                match_count++;
                run = run->next;
            }

            // если нашли 3 или более шариков одного цвета
            if (match_count >= 3) {
                destroyed_total += match_count;
                count -= match_count;
                triggered = true;

                Node* match_start = current;
                Node* match_end = run ? run->prev : tail;

                // перестановка указателя в обход удаляемой цепочки
                if (match_start->prev) {
                    match_start->prev->next = run;
                } else {
                    head = run; // удаление с начала
                }

                if (run) {
                    run->prev = match_start->prev;
                } else {
                    tail = match_start->prev; // удаление с конца
                }

                // очистка узлов из памяти
                Node* del = match_start;
                while (del != run) {
                    Node* next_del = del->next;
                    delete del;
                    del = next_del;
                }

                // указатель возвращается назад, чтообы далее проверять
                if (run && run->prev) {
                    current = run->prev;
                } else {
                    current = head;
                }

                // брейк для начала нового прохода по обновленному списку
                break;
            }

            current = current->next;
        }
    }

    return destroyed_total;
}

