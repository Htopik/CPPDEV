#pragma once

#include <iostream>
using namespace std;

class IShop
{
public:
    virtual void Show() = 0;
    virtual ~IShop() = default;
};