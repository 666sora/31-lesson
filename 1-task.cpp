#include <iostream>
#include <string>


class Toy {
    std::string toyName = "";

public:
    Toy(std::string inName) : toyName(inName) {};
    Toy() : toyName("default") {};    
};

class shared_ptr_toy {
    Toy* toyPtr = nullptr;
    size_t* counterPtr = nullptr;

public:
    shared_ptr_toy() {
        if (toyPtr != nullptr) {
            if ((*counterPtr) == 1) {
                delete toyPtr;
                toyPtr = nullptr;
                delete counterPtr;
                counterPtr = nullptr;
            }
            else {
                (*counterPtr)--;
            }
        }

        toyPtr = new Toy();
        counterPtr = new size_t(1);
    }
    shared_ptr_toy(const std::string& inName) {
        if (toyPtr != nullptr) {
            if ((*counterPtr) == 1) {
                delete toyPtr;
                toyPtr = nullptr;
                delete counterPtr;
                counterPtr = nullptr;
            }
            else {
                (*counterPtr)--;
            }
        }

        toyPtr = new Toy(inName);
        counterPtr = new size_t(1);
    }
    shared_ptr_toy(const Toy& othToy) {
        if (toyPtr != nullptr) {
            if ((*counterPtr) == 1) {
                delete toyPtr;
                toyPtr = nullptr;
                delete counterPtr;
                counterPtr = nullptr;
            }
            else {
                (*counterPtr)--;
            }
        }
        
        toyPtr = new Toy(othToy);
        counterPtr = new size_t(1);
    }
    shared_ptr_toy(const shared_ptr_toy& othToyPtr) {
        if (toyPtr != nullptr) {
            if ((*counterPtr) == 1) {
                delete toyPtr;
                toyPtr = nullptr;
                delete counterPtr;
                counterPtr = nullptr;
            }
            else {
                (*counterPtr)--;
            }
        }
        
        toyPtr = othToyPtr.toyPtr;
        counterPtr = &(*othToyPtr.counterPtr); // надо проверить
        (*counterPtr)++;
    }
    shared_ptr_toy& operator=(const shared_ptr_toy& othToyPtr) {
        if (this == &othToyPtr) {
            return *this;
        }
        if (toyPtr != nullptr) {
            if ((*counterPtr) == 1) {
                delete toyPtr;
                toyPtr = nullptr;
                delete counterPtr;
                counterPtr = nullptr;
            }
            else {
                (*counterPtr)--;
            }
        }

        toyPtr = othToyPtr.toyPtr;
        counterPtr = &(*othToyPtr.counterPtr); // надо проверить
        (*counterPtr)++;
        return *this;
    }

    ~shared_ptr_toy() {
        if (counterPtr != nullptr) {
            if ((*counterPtr) == 1) {
                delete toyPtr;
                delete counterPtr;
            }
            else {
                (*counterPtr)--;
            }
        }
    }
};

shared_ptr_toy make_shared_toy(const std::string& inName) {
    return shared_ptr_toy(Toy(inName));
}

shared_ptr_toy make_shared_toy(const Toy& InToy) {
    return shared_ptr_toy(Toy(InToy));
}


int main() {
    Toy ballToy("ball");
    shared_ptr_toy ptr_1;
    shared_ptr_toy ptr_2("ball");
    shared_ptr_toy ptr_3(ballToy);
    shared_ptr_toy ptr_4(ptr_2);
    shared_ptr_toy ptr_5 = make_shared_toy("bone");
    shared_ptr_toy ptr_6 = make_shared_toy(ballToy);
    
    ptr_1 = ptr_2;
    
} 

/*
Реализуйте умный указатель shared_ptr_toy с распределённым доступом и механикой подсчёта 
ссылок для класса Toy, реализованного в задании. Указатель должен иметь все стандартные 
методы класса и быть функциональной заменой использованию shared_ptr<Toy>. 
Реализуйте свободную функцию make_shared_toy, которая принимает набор аргументов 
и конструирует игрушку или от названия, или при помощи копии другой игрушки.
*/