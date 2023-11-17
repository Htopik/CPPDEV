#pragma once 

#include "IShop.h"

class Portative : virtual public IShop
{
public:
    Portative(int _batteryCap);

    void Show() override;
protected:
    int _batteryCap;
};

class Speaker final : public Portative
{
public:
    Speaker(int batteryCap, int maxVolume);
    void Show() override;
private:
    int _maxVolume;
};

class Ebook final : public Portative
{
public:
    Ebook(int batteryCap, int memory);

    void Show() override;
private:
    int _memory;
};