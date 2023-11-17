#pragma once
#include "Appliances.h"
#include "Portative.h" 

class FoldingHairDryer final : public Portative, Appliances
{
public:
    FoldingHairDryer(int batteryCap, int power—onsump);

    void Show() override;
};