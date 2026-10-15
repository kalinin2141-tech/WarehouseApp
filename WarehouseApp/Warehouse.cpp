#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Product.h"
using namespace std;
int getSafeInt(string prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(10000, '\n');
            return val;
        }
        cout << "Ошибка! Нужно ввести целое число.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}
double getSafeDouble(string prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) {
            cin.ignore(10000, '\n');
            return val;
        }
        cout << "Ошибка! Нужно ввести число.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}
string getString(string prompt) {
    string val;
    cout << prompt;
    getline(cin, val);
    return val;
}
void loadFromFile(vector<Product>& products) {
    ifstream fin("data/products.txt");
    if (!fin.is_open()) {
        cout << "Файл не найден, начинаем с пустого склада.\n";
        return;
    }
    
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        Product p;
        
        getline(ss, token, ','); p.id = stoi(token);
        getline(ss, p.name, ',');
        getline(ss, p.category, ',');
        getline(ss, token, ','); p.price = stod(token);
        getline(ss, token, ','); p.quantity = stoi(token);
        
        products.push_back(p);
    }
    fin.close();
}
void saveToFile(vector<Product>& products) {
    ofstream fout("data/products.txt");
    for (int i = 0; i < products.size(); i++) {
        fout << products[i].id << "," 
             << products[i].name << "," 
             << products[i].category << "," 
             << products[i].price << "," 
             << products[i].quantity << "\n";
    }
    fout.close();
    cout << "Данные успешно сохранены!\n";
}
void printProducts(vector<Product>& products) {
    if (products.empty()) {
        cout << "Склад пуст.\n";
        return;
    }
    cout << "ID\t| Название\t| Категория\t| Цена\t| Кол-во\n";
    cout << "---------------------------------------------------------\n";
    for (int i = 0; i < products.size(); i++) {
        cout << products[i].id << "\t| " 
             << products[i].name << "\t\t| " 
             << products[i].category << "\t\t| " 
             << products[i].price << "\t| " 
             << products[i].quantity << "\n";
    }
}
void addProduct(vector<Product>& products) {
    Product p;
    p.id = getSafeInt("Введите уникальный ID: ");
    for (int i = 0; i < products.size(); i++) {
        if (products[i].id == p.id) {
            cout << "Товар с таким ID уже существует!\n";
            return;
        }
    }
    p.name = getString("Введите название: ");
    p.category = getString("Введите категорию: ");
    p.price = getSafeDouble("Введите цену (>= 0): ");
    while (p.price < 0) {
        cout << "Цена не может быть отрицательной!\n";
        p.price = getSafeDouble("Введите цену (>= 0): ");
    }
    p.quantity = getSafeInt("Введите количество (>= 0): ");
    while (p.quantity < 0) {
        cout << "Количество не может быть отрицательным!\n";
        p.quantity = getSafeInt("Введите количество (>= 0): ");
    }
    products.push_back(p);
    cout << "Товар добавлен!\n";
}
void deleteProduct(vector<Product>& products) {
    int id = getSafeInt("Введите ID товара для удаления: ");
    for (int i = 0; i < products.size(); i++) {
        if (products[i].id == id) {
            products.erase(products.begin() + i);
            cout << "Товар удален!\n";
            return;
        }
    }
    cout << "Товар с таким ID не найден.\n";
}
void searchByName(vector<Product>& products) {
    string name = getString("Введите часть названия для поиска: ");
    bool found = false;
    for (int i = 0; i < products.size(); i++) {
        if (products[i].name.find(name) != string::npos || 
            products[i].name.find(name) != string::npos) { 
            cout << "Найдено: " << products[i].name << " (ID: " << products[i].id << ")\n";
            found = true;
        }
    }
    if (!found) cout << "Ничего не найдено.\n";
}
void totalCost(vector<Product>& products) {
    double total = 0;
    for (int i = 0; i < products.size(); i++) {
        total += products[i].price * products[i].quantity;
    }
    cout << "Общая стоимость склада: " << total << " руб.\n";
}
void top3Expensive(vector<Product>& products) {
    if (products.size() < 3) {
        cout << "Товаров меньше 3, выводим все:\n";
        printProducts(products);
        return;
    }
    vector<Product> temp = products;
    sort(temp.begin(), temp.end(), [](Product a, Product b) {
        return a.price > b.price;
    });
    cout << "Топ-3 самых дорогих товара:\n";
    for (int i = 0; i < 3; i++) {
        cout << temp[i].name << " - " << temp[i].price << " руб.\n";
    }
}