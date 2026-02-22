#include <string>
#include <vector>
#include <unordered_map>  
#include <iostream>  
using namespace std;
class Item {
    string name;
    double price;

public: 
    Item(string name, double price) :name(name), price(price) {};

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }
};

class VendingMachine {
    vector<Item> items;
    unordered_map<int, int>stock;
    int currentMoney;
public:
    void addItem(int id, Item item, int quantity) {
        items.push_back(item);
        stock[id] = quantity;
    }

    void displayItems() {
        for (int i = 0; i < items.size(); i++) {
            cout << "ID: " << i << " Name: " << items[i].getName() << " Price: " << items[i].getPrice() << " Stock: " << stock[i] << endl;
        }
    }

    void insertMoney(int amount) {
        currentMoney += amount;
    }

    void purchaseItem(int id) {
        if(stock[id]>0 && currentMoney >= items[id].getPrice()) {
            stock[id]--;
            currentMoney -= items[id].getPrice();
            cout << "Purchased: " << items[id].getName() << endl;    
        } else {
            cout << "Cannot purchase item. Either out of stock or insufficient funds." << endl;
        }
    }
};

int main(){
    VendingMachine vm;
    vm.addItem(0, Item("Soda", 1.50), 10);
    vm.addItem(1, Item("Chips", 1.00), 5);
    vm.addItem(2, Item("Candy", 0.75), 20);

    vm.displayItems();

    vm.insertMoney(5);
    vm.purchaseItem(0);
    vm.purchaseItem(1);
    vm.purchaseItem(2);

    return 0;
}