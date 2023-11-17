#pragma once 

#include "IShop.h"

class Appliances : virtual public IShop
{
public:
    Appliances(int _batteryCap);

    void Show() override;
protected:
    int _power—onsump;
};

class WashingMachine final : public Appliances
{
public:
    WashingMachine(int power—onsump, int maxVolume);
    void Show() override;
private:
    int _maxVolume;
};

class Hoover final : public Appliances
{
public:
    Hoover(int power—onsump, int tankVolume);

    void Show() override;
private:
    int _tankVolume;
};