#include "crow_all.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <map>

using namespace std;
using namespace std::chrono;

struct MenuItem {
    string name;
    int price;
    string description;
};

map<string, vector<MenuItem>> databases;

vector<MenuItem> loadFile(string filename) {
    vector<MenuItem> tempMenu;
    string basePath = "F:\\semester 3\\aka\\tubes e-menu\\"; 
    string fullPath = basePath + filename;
    
    ifstream file(fullPath);
    string line;
    
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) continue;
            size_t posisiKoma = line.find_last_of(',');
            if (posisiKoma != string::npos) {
                string nama = line.substr(0, posisiKoma);
                string hargaStr = line.substr(posisiKoma + 1);
                try {
                    int harga = stoi(hargaStr);
                    tempMenu.push_back({nama, harga, "Menu Lezat"});
                } catch (...) { continue; }
            }
        }
        file.close();
        cout << "[SUKSES] Loaded " << filename << " (" << tempMenu.size() << " data)" << endl;
    } else {
        cout << "[ERROR] Gagal membuka: " << fullPath << endl;
    }
    return tempMenu;
}
// Iteratif
int searchIterative(const vector<MenuItem>& menu, string target) {
    for (size_t i = 0; i < menu.size(); ++i) {
        if (menu[i].name.find(target) != string::npos) return i;
    }
    return -1;
}
// Rekursif
int searchRecursive(const vector<MenuItem>& menu, const string& target, int index) {
    if (index >= (int)menu.size()) return -1;
    if (menu[index].name.find(target) != string::npos) return index;
    return searchRecursive(menu, target, index + 1);
}

string getHtmlPage(string result = "", string timeInfo = "", string selectedSize = "100") {
    
    string sel100 = (selectedSize == "100") ? "selected" : "";
    string sel1000 = (selectedSize == "1000") ? "selected" : "";
    string sel5000 = (selectedSize == "5000") ? "selected" : "";
     string sel10000 = (selectedSize == "10000") ? "selected" : "";

    return R"(
    <!DOCTYPE html>
    <html lang="id">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Resto E-Menu Search</title>
        <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@300;400;600;700&display=swap" rel="stylesheet">
        <style>
            * { box-sizing: border-box; margin: 0; padding: 0; }
            
            body {
                font-family: 'Poppins', sans-serif;
                min-height: 100vh;
                display: flex;
                justify-content: center;
                align-items: center;
                color: #2d3436;
                background: linear-gradient(-45deg, #ee7752, #e73c7e, #23a6d5, #23d5ab);
                background-size: 400% 400%;
                animation: gradientBG 15s ease infinite;
            }

            @keyframes gradientBG {
                0% { background-position: 0% 50%; }
                50% { background-position: 100% 50%; }
                100% { background-position: 0% 50%; }
            }

            .container {
                background: rgba(255, 255, 255, 0.9);
                padding: 50px 40px;
                border-radius: 24px;
                box-shadow: 0 20px 60px rgba(0,0,0,0.2);
                backdrop-filter: blur(10px);
                width: 100%;
                max-width: 550px;
                text-align: center;
                border: 1px solid rgba(255, 255, 255, 0.4);
            }

            h1 { font-weight: 700; color: #2d3436; margin-bottom: 5px; font-size: 28px; }
            .icon-header { font-size: 40px; margin-bottom: 10px; display: block; }
            
            .badge {
                display: inline-block;
                background: #dfe6e9;
                color: #636e72;
                padding: 5px 12px;
                border-radius: 50px;
                font-size: 12px;
                font-weight: 600;
                margin-bottom: 30px;
            }

            select, input[type="text"] {
                width: 100%;
                padding: 18px 20px;
                border: 2px solid transparent;
                background: #f1f2f6;
                border-radius: 16px;
                font-size: 16px;
                font-family: 'Poppins', sans-serif;
                outline: none;
                transition: all 0.3s ease;
                margin-bottom: 15px;
                color: #2d3436;
            }
            select:focus, input[type="text"]:focus {
                border-color: #6c5ce7;
                background: #fff;
                box-shadow: 0 10px 20px rgba(108, 92, 231, 0.1);
            }

            label { font-size: 12px; font-weight: 600; color: #636e72; display: block; text-align: left; margin-bottom: 5px; margin-left: 5px;}

            .btn-group { display: flex; gap: 15px; margin-top: 10px; }
            button {
                flex: 1;
                padding: 15px;
                border: none;
                border-radius: 14px;
                color: white;
                font-weight: 600;
                font-family: 'Poppins', sans-serif;
                cursor: pointer;
                transition: all 0.3s ease;
                display: flex;
                align-items: center;
                justify-content: center;
                gap: 8px;
            }
            
            .btn-iter { background: linear-gradient(135deg, #0984e3, #74b9ff); box-shadow: 0 10px 20px rgba(9, 132, 227, 0.2); }
            .btn-rec { background: linear-gradient(135deg, #6c5ce7, #a29bfe); box-shadow: 0 10px 20px rgba(108, 92, 231, 0.2); }

            button:hover { transform: translateY(-3px); filter: brightness(1.1); }

            .result-card {
                margin-top: 35px;
                background: #fff;
                border-radius: 16px;
                padding: 25px;
                text-align: left;
                box-shadow: 0 10px 30px rgba(0,0,0,0.05);
                border-left: 6px solid #ccc;
                animation: fadeIn 0.5s ease-out;
            }
            @keyframes fadeIn { from { opacity: 0; transform: translateY(10px); } to { opacity: 1; transform: translateY(0); } }

            .menu-title { font-size: 20px; font-weight: 700; color: #2d3436; margin-bottom: 5px; }
            .menu-price { font-size: 24px; font-weight: 700; color: #00b894; }
            
            .not-found { background: #fff5f5; color: #d63031; border-left-color: #d63031; }

            .time-stat {
                margin-top: 20px;
                font-size: 13px;
                color: #636e72;
                font-weight: 500;
                background: rgba(255,255,255,0.5);
                padding: 5px 10px;
                border-radius: 8px;
                display: inline-block;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <span class="icon-header">🍔</span>
            <h1>Cari Menu Favorit</h1>
            <div class="badge">E-Menu Database Search System</div>
            
            <form action="/search" method="GET">
                
                <label>Pilih Ukuran Data:</label>
                <select name="size">
                    <option value="100" )" + sel100 + R"(>📂 100 Data Menu</option>
                    <option value="1000" )" + sel1000 + R"(>📂 1.000 Data Menu</option>
                    <option value="5000" )" + sel5000 + R"(>📂 5.000 Data Menu</option>
                     <option value="10000" )" + sel10000 + R"(>📂 10.000 Data Menu</option>
                </select>

                <label>Nama Makanan:</label>
                <input type="text" name="query" placeholder="Contoh: Steak, Nasi Goreng..." required autocomplete="off">
                
                <div class="btn-group">
                    <button type="submit" name="algo" value="iterative" class="btn-iter">
                        <span>⚡</span> Iteratif
                    </button>
                    <button type="submit" name="algo" value="recursive" class="btn-rec">
                        <span>🔄</span> Rekursif
                    </button>
                </div>
            </form>
            
            )" + result + R"(
            )" + timeInfo + R"(
        </div>
    </body>
    </html>
    )";
}

int main() {
    cout << "--- MEMUAT DATABASE ---" << endl;
    databases["100"] = loadFile("menu_100.txt");
    databases["1000"] = loadFile("menu_1000.txt");
    databases["5000"] = loadFile("menu_5000.txt");
    databases["10000"] = loadFile("menu_10000.txt");
    cout << "--- SISTEM SIAP ---" << endl;

    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return getHtmlPage();
    });

    CROW_ROUTE(app, "/search")([](const crow::request& req){
        string query = req.url_params.get("query");
        string algo = req.url_params.get("algo");
        string size = req.url_params.get("size"); 
        
        if (databases.find(size) == databases.end() || databases[size].empty()) {
            return getHtmlPage("<div class='result-card not-found'><p>Database " + size + " kosong/tidak ditemukan!</p></div>", "", size);
        }

        const vector<MenuItem>& currentDB = databases[size];

        string themeColor = (algo == "iterative") ? "#0984e3" : "#6c5ce7";
        string algoDisplay = (algo == "iterative") ? "Iteratif" : "Rekursif";

        auto start = high_resolution_clock::now();
        int foundIndex = -1;
        
        if (algo == "iterative") foundIndex = searchIterative(currentDB, query);
        else foundIndex = searchRecursive(currentDB, query, 0);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);

        string resultHtml;
        if (foundIndex != -1) {
            resultHtml = "<div class='result-card' style='border-left-color: " + themeColor + ";'>"
                         "<div style='color:" + themeColor + "; font-size:12px; font-weight:bold; text-transform:uppercase; letter-spacing:1px; margin-bottom:5px;'>Ditemukan via " + algoDisplay + "</div>"
                         "<div class='menu-title'>" + currentDB[foundIndex].name + "</div>"
                         "<div class='menu-price'>Rp " + to_string(currentDB[foundIndex].price) + "</div>"
                         "</div>";
        } else {
            resultHtml = "<div class='result-card not-found'>"
                         "<div style='color:" + themeColor + "; font-size:12px; font-weight:bold; text-transform:uppercase; letter-spacing:1px; margin-bottom:5px;'>Dicari via " + algoDisplay + "</div>"
                         "<div class='menu-title'>Oops!</div>"
                         "<p>Data Makanan <b>" + query + "</b> tidak ada di menu (" + size + " Data).</p>"
                         "</div>";
        }

        string timeHtml = "<div class='time-stat'>⏱️ Waktu Eksekusi: <b style='color:" + themeColor + "'>" + to_string(duration.count()) + " ns</b> (Database: " + size + ")</div>";
        
        return getHtmlPage(resultHtml, timeHtml, size);
    });

    app.port(18080).multithreaded().run();
}
