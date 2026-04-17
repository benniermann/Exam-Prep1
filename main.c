/*
 * main.c  –  Testfälle Übungsklausur Informatik I
 * ================================================
 *
 * Aktiviere/Deaktiviere einzelne Aufgaben hier:
 */
#define TEST_AUFGABE1  0    /* Lagerverwaltung     (inventory.h)  */
#define TEST_AUFGABE2  1    /* Verkettete Liste    (linkedlist.h) */
#define TEST_AUFGABE3  0    /* Strings & Kodierung (encode.h)     */
#define TEST_AUFGABE4  0    /* Rekursion           (recursion.h)  */
#define TEST_AUFGABE5  0    /* Bit-Operationen     (bitfield.h)   */

/* -------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#if TEST_AUFGABE1
#include "inventory.h"
#endif
#if TEST_AUFGABE2
#include "linkedlist.h"
#endif
#if TEST_AUFGABE3
#include "encode.h"
#endif
#if TEST_AUFGABE4
#include "recursion.h"
#endif
#if TEST_AUFGABE5
#include "bitfield.h"
#endif

/* -------------------------------------------------------------- */
/*  Hilfsmakros für die Tests                                     */
/* -------------------------------------------------------------- */

static int tests_run    = 0;
static int tests_passed = 0;

#define CHECK(condition, msg)                                        \
    do {                                                             \
        tests_run++;                                                 \
        if (condition) {                                             \
            tests_passed++;                                          \
            printf("  [OK]   %s\n", msg);                           \
        } else {                                                     \
            printf("  [FAIL] %s\n", msg);                           \
        }                                                            \
    } while (0)

#define CHECK_INT(got, expected, msg)                                \
    do {                                                             \
        tests_run++;                                                 \
        if ((got) == (expected)) {                                   \
            tests_passed++;                                          \
            printf("  [OK]   %s  (= %d)\n", msg, (int)(got));       \
        } else {                                                     \
            printf("  [FAIL] %s  (erwartet %d, bekommen %d)\n",     \
                   msg, (int)(expected), (int)(got));                \
        }                                                            \
    } while (0)

#define CHECK_DBL(got, expected, tol, msg)                           \
    do {                                                             \
        tests_run++;                                                 \
        double _diff = (got) - (expected);                           \
        if (_diff < 0) _diff = -_diff;                               \
        if (_diff <= (tol)) {                                        \
            tests_passed++;                                          \
            printf("  [OK]   %s  (= %.4f)\n", msg, (double)(got));  \
        } else {                                                     \
            printf("  [FAIL] %s  (erwartet %.4f, bekommen %.4f)\n", \
                   msg, (double)(expected), (double)(got));          \
        }                                                            \
    } while (0)

#define CHECK_STR(got, expected, msg)                                \
    do {                                                             \
        tests_run++;                                                 \
        if ((got) != NULL && strcmp((got), (expected)) == 0) {      \
            tests_passed++;                                          \
            printf("  [OK]   %s  (= \"%s\")\n", msg, (got));        \
        } else {                                                     \
            printf("  [FAIL] %s  (erwartet \"%s\", bekommen \"%s\")\n",\
                   msg, (expected), (got) ? (got) : "(null)");       \
        }                                                            \
    } while (0)

#define SECTION(name) \
    printf("\n--- %s ---\n", name)

/* ============================================================== */
/*  AUFGABE 1 – Lagerverwaltung                                   */
/* ============================================================== */
#if TEST_AUFGABE1
static void test_aufgabe1(void)
{
    printf("\n=== AUFGABE 1: Lagerverwaltung ===\n");

    /* 1b: Erzeugen */
    SECTION("1b: warehouse_create / warehouse_destroy");
    {
        Warehouse *w = warehouse_create();
        CHECK(w != NULL, "warehouse_create gibt nicht-NULL zurueck");
        if (w) {
            CHECK_INT(w->count,    0, "Neues Lager: count == 0");
            CHECK_INT(w->capacity, 4, "Neues Lager: capacity == 4");
            CHECK_INT(w->next_id,  1, "Neues Lager: next_id == 1");
            CHECK(w->products != NULL, "Neues Lager: products-Array alloziert");
        }
        warehouse_destroy(w);
        warehouse_destroy(NULL);   /* Darf nicht abstuerzen */
        CHECK(1, "warehouse_destroy(NULL) kein Absturz");
    }

    /* 1c: Hinzufügen */
    SECTION("1c: warehouse_add_product");
    {
        Warehouse *w = warehouse_create();
        assert(w);

        int r = warehouse_add_product(w, "Apfel", 0.99, 100);
        CHECK_INT(r, 0, "Produkt hinzufuegen: Rueckgabe 0");
        CHECK_INT(w->count, 1, "count == 1 nach erstem Produkt");

        warehouse_add_product(w, "Banane",     0.49,  50);
        warehouse_add_product(w, "Kirsche",    3.50,  30);
        warehouse_add_product(w, "Dattel",     7.20,  10);

        CHECK_INT(w->count,    4, "count == 4 nach vier Produkten");
        CHECK_INT(w->capacity, 4, "capacity noch 4 (nicht gewachsen)");

        /* 5. Produkt erzwingt Verdopplung auf 8 */
        warehouse_add_product(w, "Erdbeere", 2.10, 200);
        CHECK_INT(w->count,     5, "count == 5 nach fuenftem Produkt");
        CHECK_INT(w->capacity,  8, "capacity == 8 nach Verdopplung");

        /* IDs stimmen */
        CHECK_INT(w->products[0].id, 1, "Produkt 0 hat ID 1");
        CHECK_INT(w->products[4].id, 5, "Produkt 4 hat ID 5");

        /* Fehlerfall: negativer Preis */
        r = warehouse_add_product(w, "Fehler", -1.0, 5);
        CHECK_INT(r, -1, "Negativer Preis: Rueckgabe -1");
        CHECK_INT(w->count, 5, "count unveraendert bei Fehler");

        /* Fehlerfall: NULL-Name */
        r = warehouse_add_product(w, NULL, 1.0, 5);
        CHECK_INT(r, -1, "NULL-Name: Rueckgabe -1");

        warehouse_destroy(w);
    }

    /* 1d: Entfernen */
    SECTION("1d: warehouse_remove_by_id");
    {
        Warehouse *w = warehouse_create();
        assert(w);
        warehouse_add_product(w, "A", 1.0, 1);   /* ID 1 */
        warehouse_add_product(w, "B", 2.0, 2);   /* ID 2 */
        warehouse_add_product(w, "C", 3.0, 3);   /* ID 3 */

        /* Entferne ID 2 (mittleres Element) */
        int r = warehouse_remove_by_id(w, 2);
        CHECK_INT(r, 0, "Entfernen ID 2: Rueckgabe 0");
        CHECK_INT(w->count, 2, "count == 2 nach Entfernen");

        /* Lücke wird durch letztes Element geschlossen */
        int found_id2 = 0;
        for (int i = 0; i < w->count; i++)
            if (w->products[i].id == 2) found_id2 = 1;
        CHECK(!found_id2, "ID 2 nicht mehr im Lager");

        /* Entferne nicht existierende ID */
        r = warehouse_remove_by_id(w, 99);
        CHECK_INT(r, -1, "Nicht-existente ID: Rueckgabe -1");
        CHECK_INT(w->count, 2, "count unveraendert bei Fehler");

        /* Entferne alle restlichen Elemente */
        warehouse_remove_by_id(w, 1);
        warehouse_remove_by_id(w, 3);
        CHECK_INT(w->count, 0, "Lager leer nach allem Entfernen");

        warehouse_destroy(w);
    }

    /* 1e: Suche nach Name */
    SECTION("1e: warehouse_find_by_name");
    {
        Warehouse *w = warehouse_create();
        assert(w);
        warehouse_add_product(w, "Apfel",       0.99,  10);
        warehouse_add_product(w, "Baumapfel",   1.50,  5);
        warehouse_add_product(w, "Birne",       1.10,  20);
        warehouse_add_product(w, "Weintraube",  2.80,  15);

        Product *p = warehouse_find_by_name(w, "apf");
        CHECK(p != NULL, "Suche 'apf': Ergebnis nicht NULL");
        if (p) {
            /* Muss entweder "Apfel" oder "Baumapfel" sein */
            int ok = (strstr(p->name, "pfel") != NULL);
            CHECK(ok, "Suche 'apf': Gefundenes Produkt enthaelt 'pfel'");
        }

        p = warehouse_find_by_name(w, "Birne");
        CHECK(p != NULL, "Suche 'Birne': gefunden");
        if (p) CHECK(strcmp(p->name, "Birne") == 0, "Suche 'Birne': korrekter Name");

        p = warehouse_find_by_name(w, "Mango");
        CHECK(p == NULL, "Suche 'Mango': nicht gefunden (NULL)");

        p = warehouse_find_by_name(w, NULL);
        CHECK(p == NULL, "Suche NULL-Query: NULL zurueck");

        warehouse_destroy(w);
    }

    /* 1f: Gesamtwert */
    SECTION("1f: warehouse_total_value");
    {
        Warehouse *w = warehouse_create();
        assert(w);

        CHECK_DBL(warehouse_total_value(w), 0.0, 1e-9,
                  "Leeres Lager: Gesamtwert 0.0");

        warehouse_add_product(w, "X", 2.00, 3);   /* 6.00 */
        warehouse_add_product(w, "Y", 1.50, 4);   /* 6.00 */
        warehouse_add_product(w, "Z", 0.25, 8);   /* 2.00 */
        /* Gesamt = 14.00 */
        CHECK_DBL(warehouse_total_value(w), 14.0, 1e-6,
                  "Gesamtwert 14.00");

        CHECK_DBL(warehouse_total_value(NULL), 0.0, 1e-9,
                  "NULL-Lager: Gesamtwert 0.0");

        warehouse_destroy(w);
    }

    /* 1g: Sortierung */
    SECTION("1g: warehouse_sort_by_price");
    {
        Warehouse *w = warehouse_create();
        assert(w);
        warehouse_add_product(w, "Teuer",  9.99, 1);
        warehouse_add_product(w, "Mittel", 4.50, 2);
        warehouse_add_product(w, "Billig", 0.10, 3);
        warehouse_add_product(w, "Gleich", 4.50, 4);   /* gleicher Preis wie Mittel */

        warehouse_sort_by_price(w);

        CHECK_DBL(w->products[0].price, 0.10, 1e-9, "Sort[0] = 0.10");
        CHECK_DBL(w->products[3].price, 9.99, 1e-9, "Sort[3] = 9.99");

        /* Bei Gleichpreis: niedrigere ID zuerst */
        if (w->products[1].price == w->products[2].price) {
            CHECK(w->products[1].id < w->products[2].id,
                  "Gleicher Preis: kleinere ID zuerst");
        }

        CHECK_INT(w->count, 4, "count nach Sort unveraendert");

        warehouse_sort_by_price(NULL);  /* Kein Absturz */
        CHECK(1, "warehouse_sort_by_price(NULL) kein Absturz");

        warehouse_destroy(w);
    }
}
#endif /* TEST_AUFGABE1 */


/* ============================================================== */
/*  AUFGABE 2 – Einfach Verkettete Liste                          */
/* ============================================================== */
#if TEST_AUFGABE2
static void test_aufgabe2(void)
{
    printf("\n=== AUFGABE 2: Einfach Verkettete Liste ===\n");

    /* 2b: Erzeugen */
    SECTION("2b: slist_create / slist_destroy");
    {
        SList *l = slist_create();
        CHECK(l != NULL, "slist_create gibt nicht-NULL zurueck");
        if (l) {
            CHECK(l->head == NULL, "Neue Liste: head == NULL");
            CHECK(l->tail == NULL, "Neue Liste: tail == NULL");
            CHECK_INT(l->size, 0, "Neue Liste: size == 0");
        }
        slist_destroy(l);
        slist_destroy(NULL);
        CHECK(1, "slist_destroy(NULL) kein Absturz");
    }

    /* 2c: push_front / push_back */
    SECTION("2c: slist_push_front / slist_push_back");
    {
        SList *l = slist_create();
        assert(l);

        slist_push_back(l, 10);
        slist_push_back(l, 20);
        slist_push_back(l, 30);
        CHECK_INT(l->size, 3, "push_back 3x: size == 3");
        CHECK_INT(l->head->value, 10, "push_back: head == 10");
        CHECK_INT(l->tail->value, 30, "push_back: tail == 30");

        slist_push_front(l, 5);
        CHECK_INT(l->size, 4, "push_front: size == 4");
        CHECK_INT(l->head->value, 5, "push_front: neuer head == 5");
        CHECK_INT(l->tail->value, 30, "push_front: tail unveraendert");

        /* tail->next muss NULL sein */
        CHECK(l->tail->next == NULL, "tail->next == NULL");

        slist_destroy(l);
    }

    /* 2d: pop_front / remove_at */
    SECTION("2d: slist_pop_front / slist_remove_at");
    {
        SList *l = slist_create();
        assert(l);

        /* pop von leerer Liste */
        int err = 0;
        slist_pop_front(l, &err);
        CHECK_INT(err, -1, "pop_front von leerer Liste: err == -1");

        slist_push_back(l, 1);
        slist_push_back(l, 2);
        slist_push_back(l, 3);
        slist_push_back(l, 4);
        /* Liste: [1, 2, 3, 4] */

        err = 0;
        int val = slist_pop_front(l, &err);
        CHECK_INT(err, 0,  "pop_front Erfolg: err == 0");
        CHECK_INT(val, 1,  "pop_front: Rueckgabe 1");
        CHECK_INT(l->size, 3, "pop_front: size == 3");
        CHECK_INT(l->head->value, 2, "pop_front: neuer head == 2");

        /* Liste: [2, 3, 4] – entferne Index 1 (Wert 3) */
        int r = slist_remove_at(l, 1);
        CHECK_INT(r, 0, "remove_at(1) Erfolg: 0");
        CHECK_INT(l->size, 2, "remove_at: size == 2");
        /* Prüfe dass 2 → 4 */
        if (l->head && l->head->next)
            CHECK_INT(l->head->next->value, 4, "remove_at: 2 -> 4");

        /* Außerhalb: */
        r = slist_remove_at(l, 99);
        CHECK_INT(r, -1, "remove_at(99): -1 (out of range)");
        r = slist_remove_at(l, -1);
        CHECK_INT(r, -1, "remove_at(-1): -1 (negativ)");

        /* Letztes Element entfernen → tail korrekt aktualisieren */
        slist_push_back(l, 99);
        /* Liste: [2, 4, 99] – entferne letzten */
        r = slist_remove_at(l, 2);
        CHECK_INT(r, 0, "remove_at(letzter): 0");
        CHECK_INT(l->tail->value, 4, "tail nach remove_at(letzter) == 4");
        CHECK(l->tail->next == NULL, "tail->next == NULL nach remove_at");

        slist_destroy(l);
    }

    /* 2e: Insertion Sort */
    SECTION("2e: slist_insertion_sort");
    {
        SList *l = slist_create();
        assert(l);

        /* Leere Liste / einelementige Liste */
        slist_insertion_sort(l);
        CHECK_INT(l->size, 0, "Sort leere Liste: size unveraendert 0");

        slist_push_back(l, 42);
        slist_insertion_sort(l);
        CHECK_INT(l->size, 1, "Sort einelementig: size 1");
        CHECK_INT(l->head->value, 42, "Sort einelementig: Wert unveraendert");

        slist_push_back(l, 5);
        slist_push_back(l, 30);
        slist_push_back(l, 1);
        slist_push_back(l, 17);
        /* Liste vor Sort: [42, 5, 30, 1, 17] */
        slist_insertion_sort(l);
        /* Erwartet: [1, 5, 17, 30, 42] */
        CHECK_INT(l->size, 5, "Sort 5 Elemente: size unveraendert");
        CHECK_INT(l->head->value, 1,  "Sort: head == 1");
        CHECK_INT(l->tail->value, 42, "Sort: tail == 42");
        CHECK(l->tail->next == NULL,  "Sort: tail->next == NULL");

        /* Prüfe vollständige Reihenfolge */
        int expected[] = {1, 5, 17, 30, 42};
        SNode *cur = l->head;
        int ok = 1;
        for (int i = 0; i < 5 && cur; i++, cur = cur->next)
            if (cur->value != expected[i]) ok = 0;
        CHECK(ok, "Sort: [1, 5, 17, 30, 42] korrekte Reihenfolge");

        /* Duplikate */
        slist_push_front(l, 17);
        slist_push_front(l, 1);
        slist_insertion_sort(l);
        CHECK_INT(l->size, 7, "Sort mit Duplikaten: size 7");
        CHECK_INT(l->head->value, 1, "Sort Duplikate: head == 1");

        slist_destroy(l);
    }

    /* 2f: Reverse */
    SECTION("2f: slist_reverse");
    {
        SList *l = slist_create();
        assert(l);

        /* Einelementig */
        slist_push_back(l, 7);
        slist_reverse(l);
        CHECK_INT(l->head->value, 7, "Reverse einelementig: unveraendert");
        CHECK_INT(l->tail->value, 7, "Reverse einelementig: tail == 7");

        slist_push_back(l, 2);
        slist_push_back(l, 9);
        slist_push_back(l, 4);
        /* Liste: [7, 2, 9, 4] → nach Reverse: [4, 9, 2, 7] */
        slist_reverse(l);

        CHECK_INT(l->head->value, 4, "Reverse: neuer head == 4");
        CHECK_INT(l->tail->value, 7, "Reverse: neuer tail == 7");
        CHECK(l->tail->next == NULL, "Reverse: tail->next == NULL");
        CHECK_INT(l->size, 4, "Reverse: size unveraendert");

        /* Reihenfolge prüfen */
        int expected[] = {4, 9, 2, 7};
        SNode *cur = l->head;
        int ok = 1;
        for (int i = 0; i < 4 && cur; i++, cur = cur->next)
            if (cur->value != expected[i]) ok = 0;
        CHECK(ok, "Reverse: [4, 9, 2, 7] korrekte Reihenfolge");

        /* Doppeltes Reverse ergibt Original */
        slist_reverse(l);
        CHECK_INT(l->head->value, 7, "Doppeltes Reverse: head == 7 wieder");
        CHECK_INT(l->tail->value, 4, "Doppeltes Reverse: tail == 4 wieder");

        slist_destroy(l);
    }
}
#endif /* TEST_AUFGABE2 */


/* ============================================================== */
/*  AUFGABE 3 – Strings & Kodierung                               */
/* ============================================================== */
#if TEST_AUFGABE3
static void test_aufgabe3(void)
{
    printf("\n=== AUFGABE 3: Strings & Kodierung ===\n");

    /* 3a: Caesar */
    SECTION("3a: caesar_encode / caesar_decode");
    {
        char *enc = caesar_encode("Hallo Welt!", 3);
        CHECK_STR(enc, "Kdoor Zhow!", "Caesar encode 'Hallo Welt!' shift=3");
        free(enc);

        enc = caesar_encode("xyz", 3);
        CHECK_STR(enc, "abc", "Caesar encode 'xyz' shift=3 (Wrap)");
        free(enc);

        enc = caesar_encode("XYZ", 3);
        CHECK_STR(enc, "ABC", "Caesar encode 'XYZ' shift=3 (Gross, Wrap)");
        free(enc);

        enc = caesar_encode("Hello, World! 123", 13);
        CHECK_STR(enc, "Uryyb, Jbeyq! 123", "Caesar ROT13 (Zahlen unveraendert)");
        free(enc);

        /* shift=0: unveraendert */
        enc = caesar_encode("Test", 0);
        CHECK_STR(enc, "Test", "Caesar shift=0: unveraendert");
        free(enc);

        /* Dekodieren = Umkehrung */
        enc = caesar_encode("Informatik", 7);
        char *dec = caesar_decode(enc, 7);
        CHECK_STR(dec, "Informatik", "caesar_decode(caesar_encode(x,k),k) == x");
        free(enc);
        free(dec);

        /* NULL-Eingabe */
        enc = caesar_encode(NULL, 3);
        CHECK(enc == NULL, "caesar_encode(NULL): NULL");
    }

    /* 3b: XOR */
    SECTION("3b: xor_encode");
    {
        char *enc = xor_encode("ABC", 0x00);
        CHECK_STR(enc, "ABC", "XOR mit key=0x00: unveraendert");
        free(enc);

        /* XOR ist selbst-invers */
        enc = xor_encode("Hallo", 0x42);
        char *dec = xor_encode(enc, 0x42);
        CHECK_STR(dec, "Hallo", "xor_encode(xor_encode(x,k),k) == x");
        free(enc);
        free(dec);

        /* Länge bleibt gleich */
        enc = xor_encode("Test123", 0xFF);
        CHECK(enc != NULL && strlen(enc) == 7, "XOR: Laenge bleibt 7");
        free(enc);

        enc = xor_encode(NULL, 0x01);
        CHECK(enc == NULL, "xor_encode(NULL): NULL");
    }

    /* 3c: Rotation */
    SECTION("3c: is_rotation");
    {
        CHECK_INT(is_rotation("abcde", "cdeab"), 1, "is_rotation 'abcde','cdeab' → 1");
        CHECK_INT(is_rotation("abcde", "abcde"), 1, "is_rotation gleicher String → 1");
        CHECK_INT(is_rotation("abcde", "eabcd"), 1, "is_rotation 'eabcd' → 1 (k=4)");
        CHECK_INT(is_rotation("abcde", "abecd"), 0, "is_rotation 'abecd' → 0");
        CHECK_INT(is_rotation("abc",   "abcd"),  0, "is_rotation unterschiedl. Laenge → 0");
        CHECK_INT(is_rotation("",      ""),       1, "is_rotation leere Strings → 1");
        CHECK_INT(is_rotation("a",     "a"),       1, "is_rotation einzel 'a','a' → 1");
        CHECK_INT(is_rotation("a",     "b"),       0, "is_rotation 'a','b' → 0");
        CHECK_INT(is_rotation(NULL,    "abc"),     0, "is_rotation NULL-a → 0");
        CHECK_INT(is_rotation("abc",   NULL),      0, "is_rotation NULL-b → 0");
    }

    /* 3d: RLE */
    SECTION("3d: rle_encode / rle_decode");
    {
        /* Kodieren */
        char *enc = rle_encode("aaabbc");
        CHECK_STR(enc, "3a2b1c", "rle_encode 'aaabbc' → '3a2b1c'");
        free(enc);

        enc = rle_encode("abcd");
        CHECK_STR(enc, "1a1b1c1d", "rle_encode 'abcd' → '1a1b1c1d'");
        free(enc);

        enc = rle_encode("aaaa");
        CHECK_STR(enc, "4a", "rle_encode 'aaaa' → '4a'");
        free(enc);

        enc = rle_encode("");
        CHECK(enc != NULL && strlen(enc) == 0, "rle_encode '' → ''");
        free(enc);

        enc = rle_encode(NULL);
        CHECK(enc == NULL, "rle_encode(NULL) → NULL");

        /* Dekodieren */
        char *dec = rle_decode("3a2b1c");
        CHECK_STR(dec, "aaabbc", "rle_decode '3a2b1c' → 'aaabbc'");
        free(dec);

        dec = rle_decode("1a1b1c1d");
        CHECK_STR(dec, "abcd", "rle_decode '1a1b1c1d' → 'abcd'");
        free(dec);

        /* Mehrstellige Zahl */
        dec = rle_decode("10x");
        CHECK(dec != NULL && strlen(dec) == 10, "rle_decode '10x': Laenge 10");
        if (dec) {
            int all_x = 1;
            for (size_t i = 0; i < 10; i++) if (dec[i] != 'x') all_x = 0;
            CHECK(all_x, "rle_decode '10x': alle Zeichen 'x'");
        }
        free(dec);

        dec = rle_decode("");
        CHECK(dec != NULL && strlen(dec) == 0, "rle_decode '' → ''");
        free(dec);

        /* Encode → Decode Roundtrip */
        const char *original = "aaabbbccccdddddeeeee";
        enc = rle_encode(original);
        dec = rle_decode(enc);
        CHECK(dec != NULL && strcmp(dec, original) == 0,
              "RLE Roundtrip: encode(decode(x)) == x");
        free(enc);
        free(dec);

        /* Ungültiges Format */
        dec = rle_decode("3");   /* Zahl ohne Buchstabe danach */
        CHECK(dec == NULL, "rle_decode '3' (kein Zeichen): NULL");

        dec = rle_decode("0a");  /* Anzahl 0: ungueltig */
        CHECK(dec == NULL, "rle_decode '0a' (Anzahl 0): NULL");
    }
}
#endif /* TEST_AUFGABE3 */


/* ============================================================== */
/*  AUFGABE 4 – Rekursion                                         */
/* ============================================================== */
#if TEST_AUFGABE4
static void test_aufgabe4(void)
{
    printf("\n=== AUFGABE 4: Rekursion ===\n");

    /* 4a: Schnelle Potenz */
    SECTION("4a: fast_power");
    {
        CHECK_INT(fast_power(2,  0),  1,    "2^0 = 1");
        CHECK_INT(fast_power(2,  1),  2,    "2^1 = 2");
        CHECK_INT(fast_power(2, 10),  1024, "2^10 = 1024");
        CHECK_INT(fast_power(3,  4),  81,   "3^4 = 81");
        CHECK_INT(fast_power(5,  3),  125,  "5^3 = 125");
        CHECK_INT(fast_power(1, 100), 1,    "1^100 = 1");
        CHECK_INT(fast_power(2, 16),  65536,"2^16 = 65536");
        CHECK_INT(fast_power(7,  2),  49,   "7^2 = 49");
    }

    /* 4b: GGT */
    SECTION("4b: gcd");
    {
        CHECK_INT(gcd(48, 18),  6,  "gcd(48,18) = 6");
        CHECK_INT(gcd(100, 75), 25, "gcd(100,75) = 25");
        CHECK_INT(gcd(7, 0),    7,  "gcd(7,0) = 7");
        CHECK_INT(gcd(13, 13),  13, "gcd(13,13) = 13");
        CHECK_INT(gcd(1, 1),    1,  "gcd(1,1) = 1");
        CHECK_INT(gcd(17, 5),   1,  "gcd(17,5) = 1 (teilerfremd)");
        CHECK_INT(gcd(36, 48),  12, "gcd(36,48) = 12");
    }

    /* 4c: Hanoi */
    SECTION("4c: hanoi (nur Zuganzahl)");
    {
        printf("  [Hanoi n=1]:\n");
        int moves = hanoi(1, 'A', 'C', 'B');
        CHECK_INT(moves, 1, "hanoi(1): 1 Zug");

        printf("  [Hanoi n=2]:\n");
        moves = hanoi(2, 'A', 'C', 'B');
        CHECK_INT(moves, 3, "hanoi(2): 3 Zuege");

        /* n=3: 7 Züge, Ausgabe nicht geprüft */
        printf("  [Hanoi n=3]:\n");
        moves = hanoi(3, 'A', 'C', 'B');
        CHECK_INT(moves, 7, "hanoi(3): 7 Zuege");

        /* Sonderfall n=0 */
        moves = hanoi(0, 'A', 'C', 'B');
        CHECK_INT(moves, 0, "hanoi(0): 0 Zuege");
    }

    /* 4d: Gitterpfade */
    SECTION("4d: count_paths");
    {
        CHECK_INT(count_paths(1, 1), 1,  "count_paths(1,1) = 1");
        CHECK_INT(count_paths(2, 2), 2,  "count_paths(2,2) = 2");
        CHECK_INT(count_paths(3, 3), 6,  "count_paths(3,3) = 6");
        CHECK_INT(count_paths(4, 4), 20, "count_paths(4,4) = 20");
        CHECK_INT(count_paths(2, 5), 5,  "count_paths(2,5) = 5");
        CHECK_INT(count_paths(5, 2), 5,  "count_paths(5,2) = 5");
        CHECK_INT(count_paths(1, 7), 1,  "count_paths(1,7) = 1 (nur eine Zeile)");
        CHECK_INT(count_paths(3, 4), 10, "count_paths(3,4) = 10");
    }

    /* BONUS: Memoization */
    SECTION("4d BONUS: count_paths_memo");
    {
        int memo[20][20];
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 20; j++)
                memo[i][j] = -1;
        CHECK_INT(count_paths_memo(4, 4, memo), 20,
                  "count_paths_memo(4,4) = 20");
        /* Memoization: zweiter Aufruf sollte selbes Ergebnis liefern */
        CHECK_INT(count_paths_memo(4, 4, memo), 20,
                  "count_paths_memo(4,4) gecacht = 20");
    }
}
#endif /* TEST_AUFGABE4 */


/* ============================================================== */
/*  AUFGABE 5 – Bit-Operationen                                   */
/* ============================================================== */
#if TEST_AUFGABE5
static void test_aufgabe5(void)
{
    printf("\n=== AUFGABE 5: Bit-Operationen ===\n");

    /* 5a: Bit-Manipulation */
    SECTION("5a: set_bit / clear_bit / toggle_bit / get_bit");
    {
        /* set_bit */
        CHECK_INT(set_bit(0x00, 0),  0x01, "set_bit(0,0) = 0x01");
        CHECK_INT(set_bit(0x00, 7),  0x80, "set_bit(0,7) = 0x80");
        CHECK_INT(set_bit(0xFF, 3),  0xFF, "set_bit(0xFF,3) unveraendert");
        CHECK_INT(set_bit(0x00, 31), 0x80000000u, "set_bit(0,31) MSB");

        /* clear_bit */
        CHECK_INT(clear_bit(0xFF, 0),  0xFE, "clear_bit(0xFF,0) = 0xFE");
        CHECK_INT(clear_bit(0xFF, 7),  0x7F, "clear_bit(0xFF,7) = 0x7F");
        CHECK_INT(clear_bit(0x00, 5),  0x00, "clear_bit(0,5) = 0 unveraendert");

        /* toggle_bit */
        CHECK_INT(toggle_bit(0x00, 3), 0x08, "toggle_bit(0,3): 0 → 1");
        CHECK_INT(toggle_bit(0xFF, 3), 0xF7, "toggle_bit(FF,3): 1 → 0");
        CHECK_INT(toggle_bit(toggle_bit(0x5A, 4), 4), 0x5A,
                  "toggle_bit doppelt = original");

        /* get_bit */
        CHECK_INT(get_bit(0b1010, 0), 0, "get_bit(1010,0) = 0");
        CHECK_INT(get_bit(0b1010, 1), 1, "get_bit(1010,1) = 1");
        CHECK_INT(get_bit(0b1010, 3), 1, "get_bit(1010,3) = 1");
        CHECK_INT(get_bit(0x00, 15),  0, "get_bit(0,15) = 0");
    }

    /* 5b: count_ones */
    SECTION("5b: count_ones");
    {
        CHECK_INT(count_ones(0),           0,  "count_ones(0) = 0");
        CHECK_INT(count_ones(1),           1,  "count_ones(1) = 1");
        CHECK_INT(count_ones(0xFF),        8,  "count_ones(0xFF) = 8");
        CHECK_INT(count_ones(0xFFFFFFFF),  32, "count_ones(0xFFFFFFFF) = 32");
        CHECK_INT(count_ones(0b10110100),  4,  "count_ones(0b10110100) = 4");
        CHECK_INT(count_ones(7),           3,  "count_ones(7) = 3");
        CHECK_INT(count_ones(0x80000000),  1,  "count_ones(MSB only) = 1");
    }

    /* 5c: pack/unpack RGB */
    SECTION("5c: pack_rgb / unpack_rgb");
    {
        uint32_t packed = pack_rgb(0xFF, 0x80, 0x00);
        CHECK_INT(packed, 0x00FF8000u, "pack_rgb(FF,80,00) = 0x00FF8000");

        packed = pack_rgb(0x00, 0x00, 0x00);
        CHECK_INT(packed, 0x00000000u, "pack_rgb(0,0,0) = 0");

        packed = pack_rgb(0xFF, 0xFF, 0xFF);
        CHECK_INT(packed, 0x00FFFFFFu, "pack_rgb(FF,FF,FF) = 0x00FFFFFF");

        /* Bits 31-24 müssen 0 sein */
        packed = pack_rgb(0xAB, 0xCD, 0xEF);
        CHECK_INT((packed >> 24), 0, "pack_rgb: Bits 31-24 sind 0");

        /* unpack_rgb */
        uint8_t r, g, b;
        unpack_rgb(0x00FF8000u, &r, &g, &b);
        CHECK_INT(r, 0xFF, "unpack_rgb R = 0xFF");
        CHECK_INT(g, 0x80, "unpack_rgb G = 0x80");
        CHECK_INT(b, 0x00, "unpack_rgb B = 0x00");

        /* Roundtrip */
        uint32_t p2 = pack_rgb(0x12, 0x34, 0x56);
        uint8_t r2, g2, b2;
        unpack_rgb(p2, &r2, &g2, &b2);
        CHECK_INT(r2, 0x12, "Roundtrip R = 0x12");
        CHECK_INT(g2, 0x34, "Roundtrip G = 0x34");
        CHECK_INT(b2, 0x56, "Roundtrip B = 0x56");

        /* NULL-Pointer in unpack_rgb darf nicht abstuerzen */
        unpack_rgb(0x00AABBCC, &r, NULL, &b);
        CHECK(1, "unpack_rgb mit NULL-g: kein Absturz");
        CHECK_INT(r, 0xAA, "unpack_rgb NULL-g: R trotzdem korrekt");
    }
}
#endif /* TEST_AUFGABE5 */


/* ============================================================== */
/*  main                                                          */
/* ============================================================== */
int main(void)
{
    printf("========================================\n");
    printf("  Uebungsklausur Informatik I – Tests\n");
    printf("========================================\n");

#if TEST_AUFGABE1
    test_aufgabe1();
#endif
#if TEST_AUFGABE2
    test_aufgabe2();
#endif
#if TEST_AUFGABE3
    test_aufgabe3();
#endif
#if TEST_AUFGABE4
    test_aufgabe4();
#endif
#if TEST_AUFGABE5
    test_aufgabe5();
#endif

    printf("\n========================================\n");
    printf("  Ergebnis: %d / %d Tests bestanden\n", tests_passed, tests_run);
    printf("========================================\n");

    return (tests_passed == tests_run) ? 0 : 1;
}
