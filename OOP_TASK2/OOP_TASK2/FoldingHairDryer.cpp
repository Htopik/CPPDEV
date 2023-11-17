#include "FoldingHairDryer.h"

FoldingHairDryer::FoldingHairDryer(int batteryCap, int power—onsump) : Appliances(batteryCap), Portative(power—onsump)
{
}

void FoldingHairDryer::Show()
{
    cout << " Avocado: battery Òapacity " << _batteryCap << " power consumption " << _power—onsump << endl;
}