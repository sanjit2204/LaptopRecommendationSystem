#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Laptop {
    string manufacturer, model;
    int ram;
    double price;
    double rating;
    double cpu_single_core;
    double cpu_multi_core;
    double gpu_score;
};

void addLaptop(const string &filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Laptop laptop;
    cout << "Enter Manufacturer: ";
    cin.ignore();
    getline(cin, laptop.manufacturer);
    cout << "Enter Model: ";
    getline(cin, laptop.model);
    cout << "Enter RAM (GB): ";
    cin >> laptop.ram;
    cout << "Enter Price (INR): ";
    cin >> laptop.price;
    cout << "Enter Rating (out of 5): ";
    cin >> laptop.rating;
    cout << "Enter CPU Single-Core Benchmark: ";
    cin >> laptop.cpu_single_core;
    cout << "Enter CPU Multi-Core Benchmark: ";
    cin >> laptop.cpu_multi_core;
    cout << "Enter GPU Score: ";
    cin >> laptop.gpu_score;

    file << laptop.manufacturer << "," << laptop.model << "," << laptop.ram << "," << laptop.price 
         << "," << laptop.rating << "," << laptop.cpu_single_core << "," << laptop.cpu_multi_core << "," << laptop.gpu_score << endl;
    file.close();
    cout << "Laptop added successfully!\n";
}

// Function to read laptops from the file
vector<Laptop> readLaptops(const string &filename) {
    vector<Laptop> laptops;
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return laptops;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Laptop laptop;
        string ramStr, priceStr, ratingStr, cpuSingleStr, cpuMultiStr, gpuStr;

        if (getline(ss, laptop.manufacturer, ',') && getline(ss, laptop.model, ',') &&
            getline(ss, ramStr, ',') && getline(ss, priceStr, ',') && getline(ss, ratingStr, ',') &&
            getline(ss, cpuSingleStr, ',') && getline(ss, cpuMultiStr, ',') && getline(ss, gpuStr, ',')) {
            
            laptop.ram = stoi(ramStr);
            laptop.price = stod(priceStr);
            laptop.rating = stod(ratingStr);
            laptop.cpu_single_core = stod(cpuSingleStr);
            laptop.cpu_multi_core = stod(cpuMultiStr);
            laptop.gpu_score = stod(gpuStr);
            laptops.push_back(laptop);
        }
    }
    file.close();
    return laptops;
}

void recommendLaptops(vector<Laptop> &laptops, int minRAM, double maxPrice) {
    vector<Laptop> filteredLaptops;

    for (const auto &laptop : laptops) {
        if (laptop.ram >= minRAM && laptop.price <= maxPrice) {
            filteredLaptops.push_back(laptop);
        }
    }
    
    if (filteredLaptops.empty()) {
        cout << "No laptops match your criteria.\n";
        return;
    }

    sort(filteredLaptops.begin(), filteredLaptops.end(), [](const Laptop &a, const Laptop &b) {
        double scoreA = a.rating * 10 + a.cpu_single_core * 0.5 + a.cpu_multi_core * 0.3 + a.gpu_score * 0.2;
        double scoreB = b.rating * 10 + b.cpu_single_core * 0.5 + b.cpu_multi_core * 0.3 + b.gpu_score * 0.2;
        return scoreA > scoreB;
    });

    cout << "\nTop 5 Recommended Laptops:\n";
    for (size_t i = 0; i < min(filteredLaptops.size(), static_cast<size_t>(5)); ++i) {
        cout << i + 1 << ". " << filteredLaptops[i].manufacturer << " " << filteredLaptops[i].model
             << " | " << filteredLaptops[i].ram << "GB RAM | Rating: " << filteredLaptops[i].rating
             << " | Price: INR " << filteredLaptops[i].price
             << " | CPU Single-Core: " << filteredLaptops[i].cpu_single_core
             << " | CPU Multi-Core: " << filteredLaptops[i].cpu_multi_core
             << " | GPU Score: " << filteredLaptops[i].gpu_score << endl;
    }
}

int main() {
    string filename = "C:/Users/Sanjit/Downloads/AP/AP1/laptops.txt"; // User needs to change this path
    int choice;

    while (true) {
        cout << "\nLaptop Recommendation System\n";
        cout << "1. Add Laptop\n";
        cout << "2. Search Laptops\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            addLaptop(filename);
        } else if (choice == 2) {
            vector<Laptop> laptops = readLaptops(filename);
            if (laptops.empty()) {
                cout << "No laptops found in the file.\n";
            } else {
                int minRAM;
                double maxPrice;
                cout << "Enter minimum RAM (GB): ";
                cin >> minRAM;
                cout << "Enter maximum price (INR): ";
                cin >> maxPrice;
                recommendLaptops(laptops, minRAM, maxPrice);
            }
        } else if (choice == 3) {
            cout << "Exiting program...\n";
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}