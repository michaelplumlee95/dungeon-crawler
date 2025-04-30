# Text-Based Dungeon Crawler – CS 111 Final Project

A lightweight, terminal-only roguelike written in **C++17**.  
Follow the steps below to pull the repo onto **your own Empress account**, compile, and play.

---

## 1  Clone (or copy) the project

```bash
# log in to your Empress shell first
cd ~                      # or wherever you keep coursework
git clone git@github.com:michaelplumlee95/dungeon-crawler.git
cd dungeon-crawler
```

*(No Git?  `sudo apt install git` or copy the folder with `scp`.)*

---

## 2  Build

> **Prerequisites:**  
> * g++ 11 + (already installed on Empress)  
> * `make`

```bash
make        # uses the provided Makefile
#   └─ outputs game.out
```

If you’d rather compile manually:

```bash
g++ -std=c++17 -Wall -Wextra *.cpp -o game.out
```

---

## 3  Run

```bash
./bin/game.out
```

Controls appear in-game (`attack`, `use <item>`, `inventory`, etc.).

---

## 4  File layout

```
assets/           ASCII art
data/             items.csv, monsters.csv, …
*.cpp *.h         source code
Makefile
README.md
```

---

## 5  Troubleshooting

| Symptom | Fix |
|---------|-----|
| `g++: command not found` | `sudo apt install build-essential` |
| Unicode art looks garbled | Run `export LANG=en_US.UTF-8` before launching |
| Seg-fault when entering a shop | Make sure `data/item_data.csv` is present and readable |

---

## 6  Credits

- Michael Plumlee  
- Tylar Wolff  
- Madelyn Kempka  
- Ethan Jackson  

CS 111 – Spring 2025  
California State University–San Marcos
