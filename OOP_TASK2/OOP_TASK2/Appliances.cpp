#include "Appliances.h"


Appliances::Appliances(int power—onsump) : _power—onsump(power—onsump)
{
}

void Appliances::Show()
{
    cout << "Basic power consumption: " << _power—onsump << endl;
}


WashingMachine::WashingMachine(int power—onsump, int maxVolume) : Appliances(power—onsump), _maxVolume(maxVolume)
{
}

void WashingMachine::Show()
{
    cout << " Washing Machine, power consumption: " << _power—onsump << " max volume: " << _maxVolume << endl;
}

Hoover::Hoover(int power—onsump, int tankVolume) : Appliances(power—onsump), _tankVolume(tankVolume)
{
}

void Hoover::Show()
{
    cout << " Hoover, tank volume: " << _tankVolume << " power consumption: " << _power—onsump << endl;
}