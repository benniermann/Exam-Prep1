/*
 * linkedlist.h  –  Aufgabe 2: Einfach Verkettete Liste  (25 Punkte)
 * ==================================================================
 *
 * Implementiere eine einfach verkettete Liste für int-Werte.
 *
 * WICHTIG:
 *   - Knotenwerte dürfen NICHT getauscht werden.
 *     Nur Pointer umhängen (außer push/pop-Operationen).
 *   - Alle Knoten werden mit malloc alloziert.
 *   - slist_destroy gibt ALLE Knoten frei.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H


/* ------------------------------------------------------------------ */
/*  2a) Struct-Definitionen  (4 Punkte)                               */
/* ------------------------------------------------------------------ */

/*
 * Knoten der verketteten Liste.
 *
 * Felder:
 *   value  – gespeicherter Integer-Wert
 *   next   – Zeiger auf nachfolgenden Knoten (NULL wenn letzter)
 *
 * Hinweis: Selbstreferenz erfordert 'struct SNode' in der Definition.
 */
typedef struct SNode {
    int          value;
    struct SNode *next;
} SNode;

/*
 * Verwaltungsstruktur der Liste.
 *
 * Felder:
 *   head  – Zeiger auf ersten Knoten (NULL wenn leer)
 *   tail  – Zeiger auf letzten Knoten (NULL wenn leer)
 *           (tail ermöglicht O(1) push_back)
 *   size  – Anzahl Knoten in der Liste
 */
typedef struct {
    SNode *head;
    SNode *tail;
    int    size;
} SList;


/* ------------------------------------------------------------------ */
/*  2b) Erzeugen und Zerstören  (3 Punkte)                            */
/* ------------------------------------------------------------------ */

/*
 * Erstellt eine neue, leere Liste auf dem Heap.
 * Gibt NULL zurück wenn malloc scheitert.
 */
SList *slist_create(void);

/*
 * Gibt alle Knoten und die Liste selbst frei.
 * Wenn list == NULL: sofort zurückkehren, kein Absturz.
 */
void slist_destroy(SList *list);


/* ------------------------------------------------------------------ */
/*  2c) Einfügen  (4 Punkte)                                          */
/* ------------------------------------------------------------------ */

/*
 * Fügt einen neuen Knoten mit 'value' am Anfang der Liste ein.
 * Gibt 0 bei Erfolg, -1 bei Fehler (NULL-Liste oder malloc-Fehler).
 */
int slist_push_front(SList *list, int value);

/*
 * Fügt einen neuen Knoten mit 'value' am Ende der Liste ein.
 * Gibt 0 bei Erfolg, -1 bei Fehler.
 * Nutze tail für O(1)-Laufzeit.
 */
int slist_push_back(SList *list, int value);


/* ------------------------------------------------------------------ */
/*  2d) Entfernen  (4 Punkte)                                         */
/* ------------------------------------------------------------------ */

/*
 * Entfernt den ersten Knoten und gibt seinen Wert zurück.
 *
 * Fehlerbehandlung über err-Zeiger:
 *   - *err = 0  bei Erfolg
 *   - *err = -1 wenn Liste leer oder NULL
 * Wenn err == NULL: kein Fehlercode schreiben.
 *
 * Gibt bei Fehler 0 zurück (ignoriere diesen Wert wenn *err == -1).
 */
int slist_pop_front(SList *list, int *err);

/*
 * Entfernt den Knoten an Position 'index' (0-basiert).
 *
 * Gibt 0 bei Erfolg zurück.
 * Gibt -1 zurück wenn: list == NULL, index < 0, index >= size.
 *
 * Beispiel: Liste [10, 20, 30], remove_at(1) → [10, 30]
 */
int slist_remove_at(SList *list, int index);


/* ------------------------------------------------------------------ */
/*  2e) In-Place Sortierung  (6 Punkte)                               */
/* ------------------------------------------------------------------ */

/*
 * Sortiert die Liste aufsteigend mit Insertion Sort.
 *
 * PFLICHT: Nur Pointer umhängen, NICHT die value-Felder tauschen!
 *          (In einer echten Anwendung könnten die Knoten komplexe
 *           Daten enthalten, die man nicht einfach kopieren darf.)
 *
 * Algorithmus:
 *   - Unterteile die Liste gedanklich in sortierten Präfix und
 *     unsortierten Rest
 *   - Entnehme jeweils den ersten Knoten des unsortierten Rests
 *   - Füge ihn an der richtigen Stelle im sortierten Präfix ein
 *
 * Wenn list == NULL oder size <= 1: sofort zurückkehren.
 */
void slist_insertion_sort(SList *list);


/* ------------------------------------------------------------------ */
/*  2f) Umkehren  (4 Punkte)                                          */
/* ------------------------------------------------------------------ */

/*
 * Kehrt die Reihenfolge der Knoten in-place um.
 *
 * Beispiel: [1, 2, 3, 4] → [4, 3, 2, 1]
 *
 * PFLICHT: Nur Pointer umhängen, NICHT die value-Felder tauschen!
 *          head und tail müssen anschließend korrekt gesetzt sein.
 *
 * Wenn list == NULL oder size <= 1: sofort zurückkehren.
 */
void slist_reverse(SList *list);


/* ------------------------------------------------------------------ */
/*  Hilfsfunktionen (zur Verfügung gestellt, nicht implementieren)    */
/* ------------------------------------------------------------------ */

/* Gibt die Liste auf stdout aus: [1] -> [2] -> [3] -> NULL */
void slist_print(const SList *list);

/*
 * Erstellt ein neues int-Array mit allen Werten der Liste (in Reihenfolge).
 * Der Aufrufer ist für free() verantwortlich.
 * Gibt NULL zurück wenn list == NULL oder size == 0.
 */
int *slist_to_array(const SList *list);

#endif /* LINKEDLIST_H */
