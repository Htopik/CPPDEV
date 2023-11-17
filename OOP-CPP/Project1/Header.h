#pragma once
#include <iostream>
using namespace std;

namespace module_oop
{
	class Snack {
	private:
		string name;
	public:
		Snack();
		Snack(string);
		string getName() const;
		void setName(string);
		void operator =(Snack&);
	};

	class SnackSlot {
	private:
		short number;
		short countOfSnacksInside;
		Snack* snacks;
	public:
		SnackSlot();
		SnackSlot(short);
		void operator =(SnackSlot&);
		short getNum() const;
		void setNum(short);
		void addSnack(Snack);
		~SnackSlot();
	};

	class VendingMachine {
	private:
		short number;
		short countOfSnackSlotsInside;
		SnackSlot* snackSlots;
	public:
		VendingMachine(short);
		short getNum() const;
		void setNum(short);
		void addSlot(SnackSlot);
		short getEmptySlotsCount();
		
		~VendingMachine();
	};


}