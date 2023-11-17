#pragma once

#include "staticarray.h"

#define NAMELENGTH 30

typedef char Name[NAMELENGTH];

class SocialNetwork { // социальна€ сеть
    public:
        struct Human { // класс человека
            Human();
            Human(const Name _name, int _id);
            Human& operator=(const Human& other);
            Human(const Human& other);

            bool operator==(const Human& other);

            Name name; // им€

            friend class SocialNetwork;

            private:
                int id; // внутренний id
                
        };
        SocialNetwork();
        // добавление нового человека в сеть
        void addnewMan(const Name name);
        // удаление человека из сети
        void delMan(const Name name);
        // установка дружбы между двум€ людьми
        void addFriendship(const Name name_1, const Name name_2);
        // алгоритм поиска пар
        void showThreeHandshakes();

    private: // функции
        // €вл€ютс€ друзь€ми?
        bool are_friends(const Human& m1, const Human& m2);
        // есть ли человек с man_id
        bool man_exists_with_id(int man_id);
        // поиск по имени
        Human findManByName(const Name name);
    private: // пол€
        int friend_matrix[SIZE][SIZE]; // матрица дружбы
        StaticArray<Human> people; // список людей внутри сети
        StaticArray<bool> busyids; // зан€тые id
};
