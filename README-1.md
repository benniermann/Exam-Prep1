# Informatik I – Übungsklausur C-Programmierung

## Themen & Punkte

| Aufgabe | Thema | Header | Punkte |
|---------|-------|--------|--------|
| 1 | Structs & Dynamischer Speicher | `inventory.h` | 30 |
| 2 | Einfach Verkettete Liste | `linkedlist.h` | 25 |
| 3 | Strings & Kodierung | `encode.h` | 22 |
| 4 | Rekursion | `recursion.h` | 15 |
| 5 | Bit-Operationen | `bitfield.h` | 8 |
| **Gesamt** | | | **100** |

---

## Anleitung

### Dateien anlegen

Lege für jede Aufgabe eine eigene `.c`-Datei an und implementiere dort
alle Funktionen aus dem jeweiligen Header:

```
inventory.c    →  Aufgabe 1
linkedlist.c   →  Aufgabe 2
encode.c       →  Aufgabe 3
recursion.c    →  Aufgabe 4
bitfield.c     →  Aufgabe 5
```

### Kompilieren

```bash
gcc -Wall -Wextra -std=c11 \
    main.c inventory.c linkedlist.c encode.c recursion.c bitfield.c \
    -o uebung && ./uebung
```

### Einzelne Aufgaben ein-/ausschalten

In `main.c` oben die Makros auf `0` setzen um Aufgaben zu überspringen:

```c
#define TEST_AUFGABE1  1   // Lagerverwaltung
#define TEST_AUFGABE2  1   // Verkettete Liste
#define TEST_AUFGABE3  1   // Kodierung
#define TEST_AUFGABE4  1   // Rekursion
#define TEST_AUFGABE5  1   // Bit-Operationen
```

---

## Aufgabenbeschreibungen

### Aufgabe 1 – Lagerverwaltung (30P)

**Thema:** Structs, dynamisches Array, Pointer, Speicherverwaltung

Ein Lager (`Warehouse`) verwaltet eine dynamisch wachsende Liste von
Produkten (`Product`). Jedes Produkt hat eine eindeutige, automatisch
vergebene ID, einen Namen, einen Preis und eine Menge.

**Teilaufgaben:**
- `1a` (4P): Struct-Definitionen `Product` und `Warehouse`
- `1b` (4P): Erzeugen und Zerstören des Lagers
- `1c` (6P): Produkt hinzufügen mit automatischer Kapazitätserweiterung
- `1d` (5P): Produkt anhand ID entfernen
- `1e` (4P): Suche nach Name (Teilstring)
- `1f` (3P): Gesamtlagerwert berechnen
- `1g` (4P): Nach Preis sortieren (Insertion Sort)

**Wichtige Hinweise:**
- Initialkapazität = 4, bei vollem Array verdoppeln (`realloc`)
- IDs werden intern hochgezählt, beginnend bei 1
- `warehouse_destroy` muss alle Ressourcen freigeben (kein Memory-Leak!)
- NULL-Pointer als Argument → sofort return, kein Absturz

---

### Aufgabe 2 – Einfach Verkettete Liste (25P)

**Thema:** Structs, Pointer auf Pointer, dynamischer Speicher, Algorithmen

Eine einfach verkettete Liste (`SList`) speichert Integer-Werte in
`SNode`-Knoten. Jeder Knoten wird dynamisch alloziert.

**Teilaufgaben:**
- `2a` (4P): Struct-Definitionen `SNode` und `SList`
- `2b` (3P): Erzeugen und Zerstören
- `2c` (4P): Vorne einfügen (`push_front`), hinten einfügen (`push_back`)
- `2d` (4P): Vorne entfernen (`pop_front`), an Position entfernen (`remove_at`)
- `2e` (6P): In-Place Sortierung (Insertion Sort, Knoten umhängen, nicht Werte tauschen)
- `2f` (4P): Umkehren (in-place, nur Pointer umhängen)

**Wichtige Hinweise:**
- Werte von Knoten dürfen NICHT getauscht werden – nur die Pointer
- `pop_front` auf leere Liste: Fehlercode -1, via `int* err`-Parameter
- `remove_at`: Index 0-basiert, gibt 0 bei Erfolg zurück, -1 wenn außerhalb

---

### Aufgabe 3 – Strings & Kodierung (22P)

**Thema:** Strings, Pointer-Arithmetik, malloc, Algorithmen

**Teilaufgaben:**
- `3a` (5P): Caesar-Verschlüsselung und -Entschlüsselung
  - Nur Buchstaben verschieben, Groß-/Kleinschreibung beibehalten
  - Rückgabe: neuer `malloc`-String (Aufrufer ruft `free` auf)
- `3b` (4P): XOR-Kodierung jedes Zeichens mit einem `key`-Byte
- `3c` (5P): Rotations-Check zweier Strings
  - `"abcde"` und `"cdeab"` sind Rotationen voneinander
  - Gleiche Länge ist Voraussetzung
- `3d` (8P): Run-Length-Encoding (RLE)
  - Kodieren: `"aaabbc"` → `"3a2b1c"`
  - Dekodieren: `"3a2b1c"` → `"aaabbc"`
  - Rückgabe: neuer `malloc`-String

**Wichtige Hinweise:**
- Alle zurückgegebenen Strings müssen mit `'\0'` abgeschlossen sein
- `NULL` bei Speicherfehler oder ungültiger Eingabe zurückgeben
- RLE-Dekodierung: Mehrstellige Zahlen müssen unterstützt werden (`"12a"` → 12× 'a')

---

### Aufgabe 4 – Rekursion (15P)

**Thema:** Rekursive Algorithmen, Stack-Frames, Problemzerlegung

Alle Funktionen müssen **rekursiv** implementiert werden.
Iterative Lösungen werden mit 0 Punkten bewertet.

**Teilaufgaben:**
- `4a` (3P): Schnelle Potenz x^n (teile-und-herrsche, O(log n))
- `4b` (3P): Größter gemeinsamer Teiler (Euklidischer Algorithmus)
- `4c` (4P): Türme von Hanoi – Züge ausgeben + Anzahl zurückgeben
- `4d` (5P): Anzahl unterschiedlicher Pfade in einem Gitter
  - Von `(0,0)` nach `(rows-1, cols-1)`, nur rechts oder runter
  - Mit Memoization (optionales Bonus-Array übergeben)

---

### Aufgabe 5 – Bit-Operationen (8P)

**Thema:** Bitweise Operatoren, Bitfelder, Masken

Verwende ausschließlich bitweise Operatoren (`&`, `|`, `^`, `~`, `<<`, `>>`).

**Teilaufgaben:**
- `5a` (4P): Bit setzen, löschen, umschalten, lesen (Position 0 = LSB)
- `5b` (2P): Anzahl gesetzter Bits zählen (Hamming-Gewicht)
- `5c` (2P): RGB-Wert packen/entpacken (Format `0x00RRGGBB`)

---

## Bewertungshinweise

- **Robustheit (wichtig!):** Jede Funktion muss mit NULL-Pointern umgehen können,
  ohne abzustürzen.
- **Speicher:** Jedes `malloc` braucht ein `free`. Kein Memory-Leak.
- **Keine globalen Variablen** außer explizit erlaubt.
- **Keine Compiler-Warnungen** mit `-Wall -Wextra`.
