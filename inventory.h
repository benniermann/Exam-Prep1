/*
 * inventory.h  –  Aufgabe 1: Lagerverwaltung  (30 Punkte)
 * =========================================================
 *
 * Implementiere ein dynamisch wachsendes Lagersystem.
 *
 * WICHTIG: Definiere Product und Warehouse genau wie vorgegeben.
 *          Ändere NICHT die Struct-Felder oder Typen.
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <stddef.h>  /* size_t */

/* ------------------------------------------------------------------ */
/*  1a) Struct-Definitionen  (4 Punkte)                               */
/* ------------------------------------------------------------------ */

/*
 * Produkt im Lager.
 *
 * Felder:
 *   id       – eindeutige ID, automatisch vergeben (beginnend bei 1)
 *   name     – Produktname, max. 63 Zeichen + '\0'
 *   price    – Preis in Euro (>= 0.0)
 *   quantity – Lagerbestand (>= 0)
 */
typedef struct {
    int    id;
    char   name[64];
    double price;
    int    quantity;
} Product;

/*
 * Dynamisch wachsendes Lager.
 *
 * Felder:
 *   products  – Zeiger auf dynamisch alloziertes Product-Array
 *   count     – Anzahl aktuell gespeicherter Produkte
 *   capacity  – Kapazität des allokierten Arrays
 *   next_id   – nächste zu vergebende ID (startet bei 1)
 */
typedef struct {
    Product *products;
    int      count;
    int      capacity;
    int      next_id;
} Warehouse;


/* ------------------------------------------------------------------ */
/*  1b) Erzeugen und Zerstören  (4 Punkte)                            */
/* ------------------------------------------------------------------ */

/*
 * Erstellt ein neues Lager auf dem Heap.
 *
 * - Initialkapazität = 4
 * - Alle Felder korrekt initialisieren
 * - Gibt NULL zurück wenn malloc scheitert
 */
Warehouse *warehouse_create(void);

/*
 * Gibt alle Ressourcen des Lagers frei (inkl. products-Array).
 * Wenn w == NULL: sofort zurückkehren, kein Absturz.
 */
void warehouse_destroy(Warehouse *w);


/* ------------------------------------------------------------------ */
/*  1c) Produkt hinzufügen  (6 Punkte)                                */
/* ------------------------------------------------------------------ */

/*
 * Fügt ein neues Produkt in das Lager ein.
 *
 * - ID wird automatisch vergeben (w->next_id, dann inkrementieren)
 * - Wenn count == capacity: Array mit realloc verdoppeln
 * - name wird mit strncpy kopiert (max 63 Zeichen)
 * - Gibt 0 bei Erfolg zurück
 * - Gibt -1 zurück wenn: w == NULL, name == NULL, price < 0, quantity < 0,
 *   oder realloc scheitert
 */
int warehouse_add_product(Warehouse *w, const char *name,
                          double price, int quantity);


/* ------------------------------------------------------------------ */
/*  1d) Produkt entfernen  (5 Punkte)                                 */
/* ------------------------------------------------------------------ */

/*
 * Entfernt das Produkt mit der gegebenen ID aus dem Lager.
 *
 * - Schließt die entstehende Lücke: das LETZTE Element rückt an
 *   die Stelle des entfernten (Reihenfolge ändert sich ggf.)
 * - count wird um 1 verringert
 * - Gibt 0 bei Erfolg zurück
 * - Gibt -1 zurück wenn: w == NULL oder ID nicht gefunden
 *
 * Hinweis: Die ID des letzten Elements ändert sich NICHT.
 */
int warehouse_remove_by_id(Warehouse *w, int id);


/* ------------------------------------------------------------------ */
/*  1e) Suche nach Name  (4 Punkte)                                   */
/* ------------------------------------------------------------------ */

/*
 * Sucht das erste Produkt dessen Name den Suchstring 'query'
 * als Teilstring enthält (Groß-/Kleinschreibung EGAL).
 *
 * Beispiel: query="apf" findet "Apfel" und "Baumapfel"
 *
 * - Gibt Zeiger auf das gefundene Product zurück (kein malloc!)
 * - Gibt NULL zurück wenn: w == NULL, query == NULL, nichts gefunden
 *
 * Tipp: strcasestr() oder eigene case-insensitive Suche
 *       (strcasestr ist POSIX, ggf. eigene Implementierung nötig)
 */
Product *warehouse_find_by_name(Warehouse *w, const char *query);


/* ------------------------------------------------------------------ */
/*  1f) Gesamtlagerwert  (3 Punkte)                                   */
/* ------------------------------------------------------------------ */

/*
 * Berechnet den Gesamtwert aller Produkte im Lager.
 *
 * Gesamtwert = Summe aller (product.price * product.quantity)
 *
 * - Gibt 0.0 zurück wenn w == NULL oder count == 0
 */
double warehouse_total_value(const Warehouse *w);


/* ------------------------------------------------------------------ */
/*  1g) Sortieren nach Preis  (4 Punkte)                              */
/* ------------------------------------------------------------------ */

/*
 * Sortiert das products[]-Array aufsteigend nach Preis
 * mit dem Insertion-Sort-Algorithmus.
 *
 * Bei gleichem Preis: Reihenfolge nach ID (aufsteigend).
 *
 * - Wenn w == NULL oder count <= 1: sofort zurückkehren
 */
void warehouse_sort_by_price(Warehouse *w);


/* ------------------------------------------------------------------ */
/*  Hilfsfunktion (zur Verfügung gestellt, nicht implementieren)      */
/* ------------------------------------------------------------------ */

/*
 * Gibt alle Produkte im Lager auf stdout aus.
 * Format: [ID] Name | Preis: X.XX EUR | Menge: Y
 */
void warehouse_print(const Warehouse *w);

#endif /* INVENTORY_H */
