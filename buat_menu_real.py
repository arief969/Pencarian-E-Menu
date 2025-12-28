import random

# --- DATABASE KATA KULINER ---
base_food_indo = ["Nasi Goreng", "Nasi Uduk", "Mie Goreng", "Mie Rebus", "Kwetiau", "Soto", "Sop", "Sate", "Gado-gado", "Rawon", "Rendang", "Ayam Goreng", "Ayam Bakar", "Bebek Goreng", "Lele Goreng", "Ikan Bakar", "Seblak", "Bakso", "Mie Ayam"]
base_food_western = ["Beef Burger", "Chicken Burger", "Cheese Burger", "Spaghetti", "Pizza", "Steak", "Fish and Chips", "Sandwich", "Salad", "Rice Bowl"]
base_drink = ["Es Teh", "Teh Hangat", "Es Jeruk", "Kopi Hitam", "Kopi Susu", "Cappuccino", "Latte", "Milkshake", "Jus", "Soda", "Lemon Tea", "Thai Tea", "Boba Milk", "Coklat Panas"]
base_snack = ["Kentang Goreng", "Sosis Bakar", "Roti Bakar", "Pisang Bakar", "Otak-otak", "Siomay", "Batagor", "Cireng", "Dimsum", "Risoles", "Lumpia", "Waffle", "Pancake", "Donat"]

variants = ["Spesial", "Jumbo", "Pedas", "Lada Hitam", "Asam Manis", "Mentega", "Rica-rica", "Balado", "Kecap", "Geprek", "Penyet", "Keju", "Mozarella", "Komplit", "Original", "Telur", "Ati Ampela", "Kornet", "Sapi", "Ayam", "Seafood"]

# Fungsi menentukan harga logis berdasarkan nama menu
def get_price(menu_name):
    price = 10000 # Harga dasar
    
    # Logika Harga Makanan vs Minuman
    menu_lower = menu_name.lower()
    
    # Deteksi bahan mahal
    if "sapi" in menu_lower or "steak" in menu_lower or "beef" in menu_lower: price += 25000
    elif "kambing" in menu_lower or "bebek" in menu_lower: price += 20000
    elif "udang" in menu_lower or "cumi" in menu_lower or "seafood" in menu_lower: price += 18000
    elif "ayam" in menu_lower or "chicken" in menu_lower or "ikan" in menu_lower: price += 12000
    elif "burger" in menu_lower or "pizza" in menu_lower or "spaghetti" in menu_lower: price += 15000
    
    # Deteksi Minuman/Snack (Base price lebih murah)
    if any(x in menu_name for x in base_drink): price = 5000
    if any(x in menu_name for x in base_snack): price = 8000

    # Tambahan varian
    if "jumbo" in menu_lower or "large" in menu_lower: price += 5000
    if "spesial" in menu_lower or "komplit" in menu_lower: price += 4000
    if "mozarella" in menu_lower or "keju" in menu_lower: price += 3000
    
    # Variasi acak sedikit supaya tidak flat (kelipatan 500)
    price += random.choice([0, 500, 1000, 1500, 2000, 2500])
    
    return price

def create_menu_with_price(target_count, filename):
    print(f"Sedang meracik {target_count} menu + harga untuk {filename}...")
    menu_data = set() # Pakai Set untuk cegah duplikat nama
    
    all_bases = base_food_indo + base_food_western + base_drink + base_snack
    
    while len(menu_data) < target_count:
        # 1. Buat Nama
        base = random.choice(all_bases)
        name = base
        
        # Tambah varian secara acak
        if random.random() > 0.4 and base not in base_drink: # 60% peluang tambah varian makanan
            name += f" {random.choice(variants)}"
        elif base in base_drink and random.random() > 0.6:
            name += f" {random.choice(['Jelly', 'Cincau', 'Gula Aren', 'Large'])}"

        # 2. Hitung Harga
        harga = get_price(name)
        
        # Simpan format: "Nama Menu, Harga" (String)
        # Kita masukkan ke set sebagai satu string utuh agar unik
        entry = f"{name}, {harga}"
        menu_data.add(entry)

    # Convert ke list dan urutkan abjad (opsional, biar rapi)
    sorted_list = sorted(list(menu_data))

    # Tulis ke file
    with open(filename, "w", encoding='utf-8') as f:
        f.write("\n".join(sorted_list))
    
    print(f"-> Selesai! File '{filename}' sudah jadi.")

# --- EKSEKUSI ---
create_menu_with_price(100, "menu_100.txt")
create_menu_with_price(1000, "menu_1000.txt")
create_menu_with_price(5000, "menu_5000.txt")