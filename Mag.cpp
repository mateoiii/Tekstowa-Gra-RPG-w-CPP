//Mag.cpp

#include "Mag.h"

Mag::Mag(std::string imie): Postac(imie), m_mana(100){
}

Mag::~Mag(){
}

void Mag::atakuj(){
    std::cout << m_imie << " rzuca Fire Ball." << std::endl;
}