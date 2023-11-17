#include "Header.h"
namespace module_oop
{
	Snack::Snack() {
	}
	Snack::Snack(string name) {
		this->name = name;
	}
	string Snack::getName() const {
		return this->name;
	}
	void Snack::setName(string value) {
		name = value;
	}
	void Snack::operator =(Snack& snack) {
		setName(snack.getName());
	}

	SnackSlot::SnackSlot() {
	}
	SnackSlot::SnackSlot(short number) {
		this->number = number;
		snacks = new Snack [number];
		countOfSnacksInside = 0;
	}
	short SnackSlot::getNum() const {
		return this->number;
	}
	void SnackSlot::setNum(short value) {
		number = value;
	}
	void SnackSlot::operator =(SnackSlot& snackSlot) {
		setNum(snackSlot.getNum());
		this->snacks = snackSlot.snacks;
		this->countOfSnacksInside = snackSlot.countOfSnacksInside;
	}
	void SnackSlot::addSnack(Snack snack) {
		snacks[countOfSnacksInside] = snack;
		countOfSnacksInside++;
	}
	SnackSlot::~SnackSlot() {
	}

	VendingMachine::VendingMachine(short number) {
		this->number = number;
		snackSlots = new SnackSlot[number];
		countOfSnackSlotsInside = 0;
	}
	short VendingMachine::getNum() const {
		return this->number;
	}
	void VendingMachine::setNum(short value) {
		number = value;
	}
	void VendingMachine::addSlot(SnackSlot snackSlot) {
		snackSlots[countOfSnackSlotsInside] = snackSlot;
		countOfSnackSlotsInside++;
	}
	short VendingMachine::getEmptySlotsCount() {
		return number - countOfSnackSlotsInside;
	}
	VendingMachine::~VendingMachine() {
	}
}
