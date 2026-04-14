/*
 * recursion.h  –  Aufgabe 4: Rekursion  (15 Punkte)
 * ===================================================
 *
 * Implementiere alle Funktionen REKURSIV.
 * Iterative Lösungen werden mit 0 Punkten bewertet.
 * Hilfsfunktionen dürfen definiert werden.
 *
 * Erlaubt: Lokale Variablen, if/else, Return-Anweisungen,
 *          arithmetische Operatoren, Rekursionsaufruf.
 * Verboten: Schleifen (for, while, do-while) in den geforderten
 *           Funktionen.
 */

#ifndef RECURSION_H
#define RECURSION_H


/* ------------------------------------------------------------------ */
/*  4a) Schnelle Potenz  (3 Punkte)                                   */
/* ------------------------------------------------------------------ */

/*
 * Berechnet x^n rekursiv mit dem "Exponentiation by Squaring"-Verfahren.
 *
 * Idee (Divide & Conquer):
 *   x^0       = 1
 *   x^n       = (x^(n/2))^2          wenn n gerade
 *   x^n       = x * (x^(n/2))^2      wenn n ungerade
 *
 * Diese Methode läuft in O(log n) statt O(n).
 *
 * Annahmen: n >= 0, kein Integer-Overflow in den Tests.
 *
 * Beispiele:
 *   fast_power(2, 10) → 1024
 *   fast_power(3,  0) → 1
 *   fast_power(5,  1) → 5
 *   fast_power(2, 16) → 65536
 */
long long fast_power(long long x, int n);


/* ------------------------------------------------------------------ */
/*  4b) Größter gemeinsamer Teiler  (3 Punkte)                        */
/* ------------------------------------------------------------------ */

/*
 * Berechnet den ggT von a und b mit dem Euklidischen Algorithmus.
 *
 * Rekurrenz:
 *   gcd(a, 0) = a
 *   gcd(a, b) = gcd(b, a % b)
 *
 * Annahmen: a > 0, b >= 0.
 *
 * Beispiele:
 *   gcd(48, 18) → 6
 *   gcd(100, 75) → 25
 *   gcd(7, 0)  → 7
 *   gcd(13, 13) → 13
 */
int gcd(int a, int b);


/* ------------------------------------------------------------------ */
/*  4c) Türme von Hanoi  (4 Punkte)                                   */
/* ------------------------------------------------------------------ */

/*
 * Löst das Türme-von-Hanoi-Problem für n Scheiben.
 *
 * Gibt jeden Zug auf stdout aus:
 *   "Bewege Scheibe <k> von <from> nach <to>\n"
 *
 * Parameter:
 *   n    – Anzahl Scheiben (>= 0)
 *   from – Quellstab (z.B. 'A')
 *   to   – Zielstab   (z.B. 'C')
 *   aux  – Hilfsstab  (z.B. 'B')
 *
 * Rückgabewert: Anzahl der durchgeführten Züge.
 * Formel: 2^n - 1 Züge (Scheibenindex in der Ausgabe: 1 = kleinste)
 *
 * Beispiel für n=2, from='A', to='C', aux='B':
 *   "Bewege Scheibe 1 von A nach B"
 *   "Bewege Scheibe 2 von A nach C"
 *   "Bewege Scheibe 1 von B nach C"
 *   Rückgabe: 3
 *
 * Hinweis: Die Nummerierung der Scheiben in der Ausgabe ist freigestellt
 *          (z.B. Tiefe des Rekursionsbaums oder fortlaufend),
 *          solange die Reihenfolge der Züge korrekt ist.
 *          Wichtig ist der korrekte Rückgabewert.
 */
int hanoi(int n, char from, char to, char aux);


/* ------------------------------------------------------------------ */
/*  4d) Pfade im Gitter  (5 Punkte)                                   */
/* ------------------------------------------------------------------ */

/*
 * Zählt alle möglichen Pfade von der oberen linken Ecke (0,0)
 * zur unteren rechten Ecke (rows-1, cols-1) in einem Gitter.
 *
 * Erlaubte Bewegungen: nur nach rechts (+1 Spalte) oder
 *                      nach unten (+1 Zeile).
 *
 * Naive Rekurrenz:
 *   paths(1, c) = 1  für alle c  (nur eine Zeile: immer geradeaus)
 *   paths(r, 1) = 1  für alle r  (nur eine Spalte: immer geradeaus)
 *   paths(r, c) = paths(r-1, c) + paths(r, c-1)
 *
 * Beispiele:
 *   count_paths(1, 1) → 1
 *   count_paths(2, 2) → 2
 *   count_paths(3, 3) → 6
 *   count_paths(4, 4) → 20
 *
 * BONUS (+2P): Implementiere die Variante count_paths_memo mit
 *             Memoization-Array um exponentielle Laufzeit zu vermeiden.
 *             Signatur: int count_paths_memo(int r, int c, int memo[][20])
 *             Wenn memo == NULL: normale Rekursion ohne Memoization.
 */
int count_paths(int rows, int cols);

/* BONUS: Memoization-Variante (memo ist ein 20x20-Array, mit -1 vorbelegt) */
int count_paths_memo(int rows, int cols, int memo[][20]);

#endif /* RECURSION_H */
