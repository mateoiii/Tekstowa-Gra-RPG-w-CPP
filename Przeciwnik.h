//Przeciwnik.h

#pragma once
#include "Postac.h"

class Przeciwnik:public Postac{

protected:

    static std::string wylosujImie();

public:

    Przeciwnik();

    ~Przeciwnik();

    void atakuj(Postac* cel) override;

};