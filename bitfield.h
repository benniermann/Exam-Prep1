/*
 * bitfield.h  –  Aufgabe 5: Bit-Operationen  (8 Punkte)
 * ======================================================
 *
 * Implementiere Bit-Manipulationsfunktionen für uint32_t-Werte.
 *
 * REGELN:
 *   - Nur bitweise Operatoren verwenden: & | ^ ~ << >>
 *   - Keine if/else, keine Schleifen (außer bei count_ones)
 *   - Keine arithmetischen Operatoren außer bei pack/unpack
 */

#ifndef BITFIELD_H
#define BITFIELD_H

#include <stdint.h>


/* ------------------------------------------------------------------ */
/*  5a) Einzelne Bits manipulieren  (4 Punkte)                        */
/* ------------------------------------------------------------------ */

/*
 * Setze Bit an Position 'pos' auf 1.
 * pos = 0 ist das LSB (niedrigstes Bit), pos = 31 das MSB.
 *
 * Beispiel: set_bit(0b0000, 2) → 0b0100  (= 4)
 */
uint32_t set_bit(uint32_t val, int pos);

/*
 * Lösche Bit an Position 'pos' (setze auf 0).
 *
 * Beispiel: clear_bit(0b1111, 1) → 0b1101  (= 13)
 */
uint32_t clear_bit(uint32_t val, int pos);

/*
 * Schalte Bit an Position 'pos' um (0→1, 1→0).
 *
 * Beispiel: toggle_bit(0b1010, 0) → 0b1011  (= 11)
 *           toggle_bit(0b1010, 1) → 0b1000  (= 8)
 */
uint32_t toggle_bit(uint32_t val, int pos);

/*
 * Lies den Wert des Bits an Position 'pos'.
 * Gibt 0 oder 1 zurück.
 *
 * Beispiel: get_bit(0b1010, 1) → 1
 *           get_bit(0b1010, 0) → 0
 */
int get_bit(uint32_t val, int pos);


/* ------------------------------------------------------------------ */
/*  5b) Hamming-Gewicht  (2 Punkte)                                   */
/* ------------------------------------------------------------------ */

/*
 * Zählt die Anzahl gesetzter Bits (Hamming-Gewicht / Popcount).
 *
 * Beispiele:
 *   count_ones(0)          → 0
 *   count_ones(0xFFFFFFFF) → 32
 *   count_ones(0b10110100) → 4
 *   count_ones(7)          → 3   (0b111)
 *
 * Erlaubt: eine Schleife (iteriere über alle Bit-Positionen).
 */
int count_ones(uint32_t val);


/* ------------------------------------------------------------------ */
/*  5c) RGB packen und entpacken  (2 Punkte)                          */
/* ------------------------------------------------------------------ */

/*
 * Packt drei Farbkanäle in ein uint32_t nach dem Format 0x00RRGGBB.
 *
 * Bit-Layout:
 *   Bits 23-16: Rot   (r)
 *   Bits 15-8:  Grün  (g)
 *   Bits  7-0:  Blau  (b)
 *   Bits 31-24: immer 0
 *
 * Beispiel: pack_rgb(0xFF, 0x80, 0x00) → 0x00FF8000
 */
uint32_t pack_rgb(uint8_t r, uint8_t g, uint8_t b);

/*
 * Entpackt einen 0x00RRGGBB-Wert in die drei Farbkanäle.
 * Schreibt die Werte in die übergebenen Zeiger.
 * Wenn r, g oder b == NULL: den entsprechenden Kanal überspringen.
 *
 * Beispiel:
 *   uint8_t r, g, b;
 *   unpack_rgb(0x00FF8000, &r, &g, &b);
 *   → r = 0xFF, g = 0x80, b = 0x00
 */
void unpack_rgb(uint32_t packed, uint8_t *r, uint8_t *g, uint8_t *b);

#endif /* BITFIELD_H */
