//Wojownik.cpp

#include "Wojownik.h"

Wojownik::Wojownik(std::string imie): Postac(imie), m_sila(10){
}

Wojownik::~Wojownik(){
}

void Wojownik::atakuj(){
        std::cout << m_imie << " uderz mieczem." << std::endl;
}