#include <iostream>
#include <vector>
#include <windows.h>
#include "Product.h"
extern void loadFromFile(std::vector<Product>&);
extern void saveToFile(std::vector<Product>&);
extern void printProducts(std::vector<Product>&);
extern void addProduct(std::vector<Product>&);
extern void deleteProduct(std::vector<Product>&);
extern void searchByName(std::vector<Product>&);
extern void totalCost(std::vector<Product>&);
extern void top3Expensive(std::vector<Product>&);
using namespace std;
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    system("chcp 65001 > nul"); 
    vector<Product> products;
    loadFromFile(products);
    int choice;
    do {
        cout << "\n=== СКЛАД ===\n";
        cout << "1. Показать все товары\n";
        cout << "2. Добавить товар\n";
        cout << "3. Удалить товар\n";
        cout << "4. Поиск по названию\n";
        cout << "5. Аналитика (Общая стоимость)\n";
        cout << "6. Аналитика (Топ-3 дорогих)\n";
        cout << "7. Сохранить и выйти\n";
        cout << "0. Выход без сохранения\n";
        cout << "Выберите действие: ";
        if (!(cin >> choice)) {
            cout << "Ошибка ввода!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n);
        switch (choice) {
            case 1: printProducts(products); break;
            case 2: addProduct(products); break;
            case 3: deleteProduct(products); break;
            case 4: searchByName(products); break;
            case 5: totalCost(products); break;
            case 6: top3Expensive(products); break;
            case 7: saveToFile(products); return 0;
            case 0: cout << "Выход...\n"; break;
            default: cout << "Нет такого пункта!\n";
        }
    } while (choice != 0);
    return 0;
}