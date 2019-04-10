#include <iostream>
#include <vector>
#include <fstream>

std::vector<int> vec;
std::vector<int> vec2;

void findBiggest() {
    auto *_buff = new int;
    auto *_iter = new int;
    *_iter = *_buff = 0;
    for (int i = 0; i < vec.size(); i++) { // petla szukajaca najwiekszej wartosci
        if (vec.at(i) >= *_buff) {
            *_buff = vec.at(i);
            *_iter = i;
        }
    }
    int *_tmp = new int;
    *_tmp = vec.at(0); // zamienia miejscami pierwszą wartośc z największą
    vec.at(0) = vec.at(static_cast<unsigned int>(*_iter));
    vec.at(static_cast<unsigned int>(*_iter)) = *_tmp;
    delete _buff;
    delete _iter;
    delete _tmp;
}

void heaping(int _iter) {
    auto *_lKidIter = new int;
    auto *_rKidIter = new int;
    *_lKidIter = (_iter * 2);
    *_rKidIter = (_iter * 2) + 1;
    if (*_lKidIter <= vec.size() && *_rKidIter <= vec.size()) {
        if (vec.at(static_cast<unsigned int>(_iter - 1)) < vec.at(static_cast<unsigned int>(*(_lKidIter) - 1))) {
            auto *_tmp = new int;
            *_tmp = vec.at(static_cast<unsigned int>(*(_lKidIter) - 1));
            vec.at(static_cast<unsigned int>(*(_lKidIter) - 1)) = vec.at(static_cast<unsigned int>(_iter - 1));
            vec.at(static_cast<unsigned int>(_iter - 1)) = *_tmp;
            delete _tmp;
            heaping(_iter);
        } else if (vec.at(static_cast<unsigned int>(_iter - 1)) > vec.at(static_cast<unsigned int>(*(_lKidIter) - 1))) {
            heaping(*_lKidIter);
        }
        if (vec.at(static_cast<unsigned int>(_iter - 1)) < vec.at(static_cast<unsigned int>(*(_rKidIter) - 1))) {
            auto *_tmp = new int;
            *_tmp = vec.at(static_cast<unsigned int>(*(_rKidIter) - 1));
            vec.at(static_cast<unsigned int>(*(_rKidIter) - 1)) = vec.at(static_cast<unsigned int>(_iter - 1));
            vec.at(static_cast<unsigned int>(_iter - 1)) = *_tmp;
            delete _tmp;
            heaping(_iter);
        } else if (vec.at(static_cast<unsigned int>(_iter - 1)) > vec.at(static_cast<unsigned int>(*(_rKidIter) - 1))) {
            heaping(*_rKidIter);
        }
    } else if (*_lKidIter <= vec.size() && *_rKidIter > vec.size()) {
        if (vec.at(static_cast<unsigned int>(_iter - 1)) < vec.at(static_cast<unsigned int>(*(_lKidIter) - 1))) {
            auto *_tmp = new int;
            *_tmp = vec.at(static_cast<unsigned int>(*(_lKidIter) - 1));
            vec.at(static_cast<unsigned int>(*(_lKidIter) - 1)) = vec.at(static_cast<unsigned int>(_iter - 1));
            vec.at(static_cast<unsigned int>(_iter - 1)) = *_tmp;
            delete _tmp;
            heaping(_iter);
        } else if (vec.at(static_cast<unsigned int>(_iter - 1)) > vec.at(static_cast<unsigned int>(*(_lKidIter) - 1))) {
            heaping(*_lKidIter);
        }
    }
    delete _lKidIter;
    delete _rKidIter;
}

void show() {
    for (auto i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

void saintSwap() {
    vec2.emplace_back(vec.at(0));
    vec.at(0) = vec.at(vec.size() - 1);
    vec.pop_back();
}

int main() {
    auto *_iteratio = new int;
    std::cin >> *_iteratio;
    /////////////////////////////////////////// WCZYTYWANIE
    for (int i = 0; i < *_iteratio; i++) { // petla dla liczby wykonan
        auto *_elements = new int;
        std::cin >> *_elements;
        for (int j = 0; j < *_elements; j++) { // petla dla konkretnej liczby elementow w wierszu
            auto *_buff = new int;
            std::cin >> *_buff;
            vec.emplace_back(*_buff);
            delete _buff;
        }
        /////////////////////////////////////////// OPERACJE NA KOPCU
        if (vec.size() < 2) {
            throw ("Ni ma co kopczyc");
        } else {
            for (int k = 0; k < *_elements; k++) {
                if (vec.size() == 2) {
                    findBiggest();
                    heaping(1);
                    show();
                    vec2.emplace_back(vec.at(0));
                    vec2.emplace_back(vec.at(1));
                    for (int m = vec2.size() - 1; m >= 0; m--) { // vec size -1 żeby iterowac od 0.
                        std::cout << vec2.at(m) << " ";
                    }
                    std::cout << "\n";
                    break;
                } else {
                    findBiggest();
                    heaping(1);
                    show();
                    saintSwap();
                }
            }
        }
        delete _elements;
        vec.clear();
        vec2.clear();
        std::cout << "\n";
    }
    delete _iteratio;
    return 0;
}