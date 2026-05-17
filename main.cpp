// main.cpp

#include <iostream>
#include <string>
#include <vector>
#include "Mag.h"
#include "Wojownik.h"

int main() {
    std::cout << "-----TWORZENIE ORYGINALU-----" << std::endl;
    Mag oryginalnyMag("Czarodziej Bozydar");
    oryginalnyMag.podniesPrzedmiot("Magiczna Rozdzka");
    oryginalnyMag.podniesPrzedmiot("Mikstura Many");
    oryginalnyMag.pokazPlecak();

    return 0;
}