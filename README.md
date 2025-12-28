# Analisis Kompleksitas Algoritma: E-Menu Search 🍔

Proyek Tugas Besar Mata Kuliah Analisis Kompleksitas Algoritma (Semester Ganjil 2025/2026).
Aplikasi ini membandingkan efisiensi pencarian menu menggunakan algoritma **Linear Search** dengan pendekatan **Iteratif** dan **Rekursif**.

## 🚀 Fitur Utama
- **Pencarian Menu:** Mencari item berdasarkan nama di database.
- **Dual Mode:** Pilihan algoritma Iteratif (Looping) vs Rekursif.
- **Analisis Waktu:** Pengukuran waktu eksekusi presisi tinggi (Nanoseconds).
- **GUI Web:** Antarmuka modern berbasis web menggunakan Crow C++ Framework.

## 📂 Struktur File
- `e-menu_search.cpp`: Source code utama (Backend C++).
- `menu_database.txt`: Database dummy untuk pengujian.
- `buat_menu_real.py`: Script Python generator data otomatis (untuk membuat 1000/5000 data).
- `crow_all.h`: Library Crow framework (Single header).

## 🛠️ Cara Menjalankan (Localhost)
1. Pastikan compiler C++ mendukung C++11 (misal: MinGW/G++).
2. Compile file utama:
   ```bash
   g++ e-menu_search.cpp -o e-menu_search -lpthread -lws2_32
