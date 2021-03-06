#ifndef __menu_h
#define __menu_h

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "menu_component.h"
#include "composite_iterator.h"
#include "stl_iterator_adapter.h"

class Menu: public MenuComponent {
private:
	std::vector<std::shared_ptr<MenuComponent>> menuComponents; 
	std::string name;
	std::string description;
  
public:
	Menu(std::string name, std::string description) {
		this->name = name;
		this->description = description;
	}
 
	void add(std::shared_ptr<MenuComponent> menuComponent) override {
		menuComponents.push_back(menuComponent);
	}
 
	void remove(std::shared_ptr<MenuComponent> menuComponent) override {
		menuComponents.erase(std::remove(menuComponents.begin(), menuComponents.end(), menuComponent), menuComponents.end());
	}
 
	std::shared_ptr<MenuComponent> getChild(int i) {
		return menuComponents.at(i);
	}
 
	std::string getName() {
		return name;
	}
 
	std::string getDescription() {
		return description;
	}
 
	std::shared_ptr<Iterator> createIterator() override {
		return std::make_shared<CompositeIterator>(
				std::make_shared<StlIteratorAdapter<typename std::vector<std::shared_ptr<MenuComponent>>::iterator>>(menuComponents.begin(), menuComponents.end()));
	}

	void print() {
		std::cout << "\n" << getName()
					<< ", " << getDescription() << "\n"
					<< "---------------------"
					<< "\n";
  
		for (auto menuComponent: menuComponents) {
			menuComponent->print();
		}
	}
};

#endif
