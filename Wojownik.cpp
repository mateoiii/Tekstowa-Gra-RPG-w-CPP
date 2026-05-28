//Wojownik.cpp

#include "Wojownik.h"

Wojownik::Wojownik(std::string imie): Postac(imie), m_sila(10){
}

Wojownik::~Wojownik(){
}

void Wojownik::atakuj(Postac* cel){
    int obrazenia = losoweObrazenia(10, 20); 
    
    if(czyCiosKrytyczny(20)){
        obrazenia = losoweObrazenia(25,35);
        std::cout << m_imie << " zadaje KRYTYCZNY CIOS!" << std::endl;
    } 
    else std::cout << m_imie << " atakuje!" << std::endl;

    cel->otrzymajObrazenia(obrazenia); 
}