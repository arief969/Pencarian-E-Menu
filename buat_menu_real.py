import random

base_food_indo = ["Nasi Goreng", "Nasi Uduk", "Mie Goreng", "Mie Rebus", "Kwetiau", "Soto", "Sop", "Sate", "Gado-gado", "Rawon", "Rendang", "Ayam Goreng", "Ayam Bakar", "Bebek Goreng", "Lele Goreng", "Ikan Bakar", "Seblak", "Bakso", "Mie Ayam"]
base_food_western = ["Beef Burger", "Chicken Burger", "Cheese Burger", "Spaghetti", "Pizza", "Steak", "Fish and Chips", "Sandwich", "Salad", "Rice Bowl"]
base_drink = ["Es Teh", "Teh Hangat", "Es Jeruk", "Kopi Hitam", "Kopi Susu", "Cappuccino", "Latte", "Milkshake", "Jus", "Soda", "Lemon Tea", "Thai Tea", "Boba Milk", "Coklat Panas"]
base_snack = ["Kentang Goreng", "Sosis Bakar", "Roti Bakar", "Pisang Bakar", "Otak-otak", "Siomay", "Batagor", "Cireng", "Dimsum", "Risoles", "Lumpia", "Waffle", "Pancake", "Donat"]

variants = ["Spesial", "Jumbo", "Pedas", "Lada Hitam", "Asam Manis", "Mentega", "Rica-rica", "Balado", "Kecap", "Geprek", "Penyet", "Keju", "Mozarella", "Komplit", "Original", "Telur", "Ati Ampela", "Kornet", "Sapi", "Ayam", "Seafood"]

all_drinks_set = set(base_drink)
all_snacks_set = set(base_snack)

def get_price(menu_name, base_type):
    price = 10000
    menu_lower = menu_name.lower()

    if base_type == "drink":
        price = 5000
    elif base_type == "snack":
        price = 8000
    else:
        if "sapi" in menu_lower or "steak" in menu_lower or "beef" in menu_lower: price += 25000
        elif "kambing" in menu_lower or "bebek" in menu_lower: price += 20000
        elif "udang" in menu_lower or "cumi" in menu_lower or "seafood" in menu_lower: price += 18000
        elif "ayam" in menu_lower or "chicken" in menu_lower or "ikan" in menu_lower: price += 12000
        elif "burger" in menu_lower or "pizza" in menu_lower or "spaghetti" in menu_lower: price += 15000

    if "jumbo" in menu_lower or "large" in menu_lower: price += 5000
    if "spesial" in menu_lower or "komplit" in menu_lower: price += 4000
    if "mozarella" in menu_lower or "keju" in menu_lower: price += 3000

    price += random.randint(1, 50) * 100
    return price

def create_menu_with_price(target_count, filename):
    print(f"Sedang meracik {target_count} menu untuk {filename}...")
    menu_data = set()
    all_bases = base_food_indo + base_food_western + base_drink + base_snack
    
    attempts = 0
    max_attempts = target_count * 5 

    while len(menu_data) < target_count and attempts < max_attempts:
        attempts += 1
        base = random.choice(all_bases)
        name = base
        base_type = "food"

        if base in all_drinks_set:
            base_type = "drink"
            if random.random() > 0.6:
                name += f" {random.choice(['Jelly', 'Cincau', 'Gula Aren', 'Large'])}"
        elif base in all_snacks_set:
            base_type = "snack"
            if random.random() > 0.5:
                 name += f" {random.choice(variants)}"
        else:
            if random.random() > 0.4:
                name += f" {random.choice(variants)}"

        harga = get_price(name, base_type)
        entry = f"{name}, {harga}"
        menu_data.add(entry)

    sorted_list = sorted(list(menu_data))

    with open(filename, "w", encoding='utf-8') as f:
        f.write("\n".join(sorted_list))
    
    print(f"-> Selesai! File '{filename}' sudah jadi.")

create_menu_with_price(100, "menu_100.txt")
create_menu_with_price(1000, "menu_1000.txt")
create_menu_with_price(5000, "menu_5000.txt")
create_menu_with_price(10000, "menu_10000.txt")
