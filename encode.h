/*
 * encode.h  –  Aufgabe 3: Strings & Kodierung  (22 Punkte)
 * =========================================================
 *
 * Implementiere Zeichenketten-Operationen und einfache Kodierverfahren.
 *
 * WICHTIG:
 *   - Funktionen die einen String zurückgeben, geben einen neu
 *     allokierten malloc-Buffer zurück.
 *   - Der AUFRUFER ist für free() verantwortlich.
 *   - Alle zurückgegebenen Strings müssen '\0'-terminiert sein.
 *   - Bei Fehler (NULL-Eingabe, Speicherfehler): NULL zurückgeben.
 */

#ifndef ENCODE_H
#define ENCODE_H

#include <stddef.h>   /* size_t  */
#include <stdint.h>   /* uint8_t */


/* ------------------------------------------------------------------ */
/*  3a) Caesar-Verschlüsselung  (5 Punkte)                            */
/* ------------------------------------------------------------------ */

/*
 * Verschlüsselt 'text' mit Caesar-Chiffre (Verschiebung um 'shift').
 *
 * Regeln:
 *   - 'shift' liegt im Bereich [0, 25]
 *   - Nur ASCII-Buchstaben (a-z, A-Z) werden verschoben
 *   - Großbuchstaben bleiben Großbuchstaben, Kleinbuchstaben bleiben Klein
 *   - Alle anderen Zeichen (Ziffern, Satzzeichen, Leerzeichen) bleiben unverändert
 *   - Der Alphabet-Wrap wird korrekt behandelt: 'Z' + 1 → 'A'
 *
 * Beispiel: caesar_encode("Hallo Welt!", 3) → "Kdoor Zhow!"
 *
 * Rückgabe: neuer malloc-String, oder NULL bei Fehler.
 */
char *caesar_encode(const char *text, int shift);

/*
 * Entschlüsselt einen mit Caesar verschlüsselten Text.
 * Entspricht caesar_encode(text, 26 - shift).
 *
 * Beispiel: caesar_decode("Kdoor Zhow!", 3) → "Hallo Welt!"
 *
 * Rückgabe: neuer malloc-String, oder NULL bei Fehler.
 */
char *caesar_decode(const char *text, int shift);


/* ------------------------------------------------------------------ */
/*  3b) XOR-Kodierung  (4 Punkte)                                     */
/* ------------------------------------------------------------------ */

/*
 * Verknüpft jedes Byte von 'text' mit 'key' via XOR.
 *
 * Eigenschaften:
 *   - xor_encode(xor_encode(text, key), key) == text  (selbst-invers)
 *   - Alle Bytes des Strings werden kodiert (auch Nicht-Buchstaben)
 *   - Das abschließende '\0' wird NICHT kodiert
 *
 * Beispiel: xor_encode("ABC", 0x01) → Bytes: 0x40 0x43 0x42
 *           (d.h. "@CB" – die Zeichen sind im Allgemeinen nicht druckbar)
 *
 * Rückgabe: neuer malloc-String (gleiche Länge wie Eingabe), oder NULL.
 */
char *xor_encode(const char *text, uint8_t key);


/* ------------------------------------------------------------------ */
/*  3c) Rotations-Check  (5 Punkte)                                   */
/* ------------------------------------------------------------------ */

/*
 * Prüft ob String 'b' eine zyklische Rotation von String 'a' ist.
 *
 * Definition:
 *   b ist eine Rotation von a, wenn es ein k gibt, sodass
 *   b == a[k..n-1] + a[0..k-1]  (zyklisch verschieben um k Stellen)
 *
 * Beispiele:
 *   is_rotation("abcde", "cdeab") → 1   (k=2)
 *   is_rotation("abcde", "abcde") → 1   (k=0)
 *   is_rotation("abcde", "abecd") → 0
 *   is_rotation("abc",   "abcd")  → 0   (unterschiedliche Längen)
 *   is_rotation("",      "")      → 1
 *
 * Gibt 1 zurück wenn b eine Rotation von a ist, sonst 0.
 * Gibt 0 zurück wenn a == NULL oder b == NULL.
 *
 * Tipp: b ist eine Rotation von a genau dann wenn b ein Teilstring
 *       von (a+a) ist (und gleiche Länge haben).
 */
int is_rotation(const char *a, const char *b);


/* ------------------------------------------------------------------ */
/*  3d) Run-Length-Encoding (RLE)  (8 Punkte)                         */
/* ------------------------------------------------------------------ */

/*
 * Kodiert einen String mit Run-Length-Encoding.
 *
 * Algorithmus: Aufeinanderfolgende gleiche Zeichen werden durch
 * Anzahl + Zeichen ersetzt.
 *
 * Beispiele:
 *   rle_encode("aaabbc")    → "3a2b1c"
 *   rle_encode("abcd")      → "1a1b1c1d"
 *   rle_encode("aaaa")      → "4a"
 *   rle_encode("aabbccdd")  → "2a2b2c2d"
 *   rle_encode("")          → ""  (leerer String → leerer String)
 *
 * Rückgabe: neuer malloc-String, oder NULL bei Fehler.
 *
 * Hinweis: Der kodierte String kann länger als der ursprüngliche sein
 *          (z.B. "abcd" → "1a1b1c1d"). Berechne die benötigte
 *          Puffergröße korrekt oder nutze einen ausreichend großen Buffer.
 */
char *rle_encode(const char *text);

/*
 * Dekodiert einen RLE-kodierten String.
 *
 * Beispiele:
 *   rle_decode("3a2b1c")  → "aaabbc"
 *   rle_decode("10x2y")   → "xxxxxxxxxx yy"   (Zahl kann mehrstellig sein!)
 *   rle_decode("")         → ""
 *
 * Fehlerbehandlung:
 *   - Ungültiges Format (z.B. kein Buchstabe nach der Zahl,
 *     oder Zahl ist 0): NULL zurückgeben
 *
 * Rückgabe: neuer malloc-String, oder NULL bei Fehler.
 */
char *rle_decode(const char *encoded);

#endif /* ENCODE_H */
