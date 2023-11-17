#include "Portative.h"


Portative::Portative(int batteryCap) : _batteryCap(batteryCap)
{
}

void Portative::Show()
{
    cout << "Basic Fruit sugar: " << _batteryCap << endl;
}


Speaker::Speaker(int batteryCap, int maxVolume) : Portative(batteryCap), _maxVolume(maxVolume)
{
}

void Speaker::Show()
{
    cout << " Speaker, battery capacity: " << _batteryCap << " max volume: " << _maxVolume << endl;
}

Ebook::Ebook(int batteryCap, int memory) : Portative(batteryCap), _memory(memory)
{
}

void Ebook::Show()
{
    cout << " Ebook, memory: " << _memory << " battery capacity: " << _batteryCap << endl;
}