#ifndef IKM2_BALL_LIST_H
#define IKM2_BALL_LIST_H
#include <string>

struct Node {
    int color;
    Node* prev;
    Node* next;

    Node(int c) : color(c), prev(nullptr), next(nullptr) {}
};


class BallList {
private:
    Node* head;
    Node* tail;
    int count;

    void clear();

public:
    BallList();
    ~BallList();

    void push_back(int color);
    bool is_empty() const;
    int get_count() const;

    // основной алгоритм симуляции уничтожения шариков
    int simulate_game();

    // метод для вывода текущего состояния
    std::string to_string() const;
};


#endif //IKM2_BALL_LIST_H