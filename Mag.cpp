//Mag.cpp

#include "Mag.h"

Mag::Mag(std::string imie): Postac(imie), m_mana(100){
}

Mag::~Mag(){
}

void Mag::atakuj(Postac* cel){
    std::cout << m_imie << " rzuca Fire Ball na "<< cel << std::endl;
    cel->otrzymajObrazenia(losoweObrazenia(10,20));
}