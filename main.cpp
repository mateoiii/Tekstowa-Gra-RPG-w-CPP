#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "Mag.h"
#include "Wojownik.h"
#include "Przeciwnik.h" 

template <typename T>
void wypiszNaglowek(T tekst) {
    std::cout << "\n======================================" << std::endl;
    std::cout << "            " << tekst << std::endl;
    std::cout << "======================================\n" << std::endl;
}

void rysujPasekHP(std::string imie, int hp, int max_hp) {
    if (hp < 0) hp = 0; 
    
    int iloscKratek = (hp * 20) / max_hp; 
    
    std::cout << imie << "\n[";
    for (int i = 0; i < 20; i++) {
        if (i < iloscKratek) {
            std::cout << "#"; 
        } else {
            std::cout << "-"; 
        }
    }
    std::cout << "] " << hp << "/" << max_hp << " HP\n";
}


int main() {
    wypiszNaglowek("MENU GLOWNE");
    

    std::string imieBohatera;
    std::cout << "Podaj imie swojego bohatera: ";
    std::cin >> imieBohatera;

    std::cout << "\nWybierz klase postaci:" << std::endl;
    std::cout << "1. Wojownik" << std::endl;
    std::cout << "2. Mag" << std::endl;
    std::cout << "Twoj wybor (1 lub 2): ";
    
    char wyborKlasy = '1';
    std::cin >> wyborKlasy;

    Postac* gracz = nullptr;    //pusty wskażnik na postać, który zostanie przypisany do konkretnej klasy w zależności od wyboru gracza

    if (wyborKlasy == '2') {
        gracz = new Mag(imieBohatera);
        std::cout << "\nStworzyles Maga o imieniu " << imieBohatera << std::endl;
    } 
    else{
        gracz = new Wojownik(imieBohatera);
        std::cout << "\nStworzyles Wojownika o imieniu " << imieBohatera << std::endl;
    }

    std::cout << "\nCzy chcesz wczytac poprzedni zapis gry dla tej postaci? (1-Tak, 2-Nie): ";
    char wyborOdczytu = '0';
    std::cin >> wyborOdczytu;

    if (wyborOdczytu == '1') {
        try {
            if (gracz->wczytajBohatera()) {
                std::cout << *gracz << std::endl;
            }
        } 
        catch (const std::runtime_error& b) {
            std::cout << "BLAD: " << b.what() << std::endl;
            std::cout << "Rozpoczynamy z domyslnymi statystykami" << std::endl;
        }
    }
    else {
        std::cout << "Zaczynamy nowa gre jako Geralt!" << std::endl;
    }

    
    bool eksploracja = true;

    while (eksploracja && gracz->czyZyje()) {
        Postac* wrog = new Przeciwnik(); 
        
        int tura = 1; 

        while (gracz->czyZyje() && wrog->czyZyje()) { 
            system("clear");                                          

            std::cout << "\n======================================" << std::endl;
            std::cout << "               TURA " << tura << std::endl;
            std::cout << "======================================" << std::endl;
            
            rysujPasekHP(gracz->pobierzImie(), gracz->pobierzHP(), gracz->pobierzMaxHP());
            std::cout << "                  VS                  \n";
            rysujPasekHP(wrog->pobierzImie(), wrog->pobierzHP(), wrog->pobierzMaxHP());
            std::cout << "======================================\n" << std::endl;

            std::cout << "Wybierz akcje: " << std::endl;
            std::cout << "1. Atak" << std::endl;
            std::cout << "2. Plecak" << std::endl;
            std::cout << "3. Ulecz sie" << std::endl;

            char wyborAkcji = '0';
            std::cin >> wyborAkcji;

            std::cout << "\n-----WYNIK AKCJI-----" << std::endl;

            switch (wyborAkcji) {
            case '1':
                gracz->atakuj(wrog);
                break;
            case '2':
                gracz->pokazPlecak();
                std::cout << "\nNacisnij ENTER, aby wrocic do walki...";
                std::cin.ignore(1000, '\n'); 
                std::cin.get(); 
                continue; 
            case '3':
                gracz->uzyjMikstury();
                break;
            default:
                std::cout << "Zly wybor! Sprobuj ponownie." << std::endl;
                std::cout << "\nNacisnij ENTER, aby sprobowac jeszcze raz...";
                std::cin.ignore(1000, '\n'); 
                std::cin.get(); 
                continue; 
            }

            if (wrog->czyZyje()) {
                std::cout << "\n-----RUCH PRZECIWNIKA-----" << std::endl;
                wrog->atakuj(gracz);
            }

            std::cout << "\nNacisnij ENTER, aby przejsc do kolejnej tury...";
            std::cin.ignore(1000, '\n'); 
            std::cin.get(); 

            tura++; 
        }

        system("clear");
        
        if (gracz->czyZyje()) {
            std::cout << "\nZwyciestwo!" << std::endl;
            
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> expDrop(30, 60);
            gracz->zdobadzDoswiadczenie(expDrop(gen));

            std::vector<std::string> tablicaLupow = {"Zelazny Miecz", "Skorzany Pancerz", "Zloty Pierscien", "Tajemniczy Zwoj", "Stary But"};
            std::uniform_int_distribution<> rzutOPrzedmiot(0, tablicaLupow.size() - 1);
            
            std::string zdobytyPrzedmiot = tablicaLupow[rzutOPrzedmiot(gen)];
            std::cout << "Z pokonanego wroga wypada: [" << zdobytyPrzedmiot << "]!" << std::endl;
            gracz->podniesPrzedmiot(zdobytyPrzedmiot);
            
            std::cout << "\nOdpoczywasz chwile. Co robisz dalej?" << std::endl;
            std::cout << "1. Ide dalej w glab lasu (Nastepny potwor)" << std::endl;
            std::cout << "2. Zapisuje gre i wracam do miasta (Koniec)" << std::endl;
            char decyzja = '0';
            std::cin >> decyzja;
            
            if (decyzja == '2') {
                eksploracja = false;
                gracz->zapiszBohatera();
            }
        } else std::cout << "\nPolegles w walce... Koniec gry." << std::endl;

        delete wrog;
    }

    delete gracz;
    return 0;
}