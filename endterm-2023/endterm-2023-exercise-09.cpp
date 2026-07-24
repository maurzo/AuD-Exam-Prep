#include "endterm-2023.hpp"

#include <stdexcept>

namespace aud::endterm_2023::exercise_09 {

/*
 * Aufgabe 9, Seite 17
 *
 * s besteht nur aus '0', '1' und '?'. Erzeuge alle Strings, die entstehen,
 * wenn jedes '?' unabhängig durch '0' oder '1' ersetzt wird.
 * Die Reihenfolge der Ergebnisse ist beliebig.
 *
 * Beispiel: "0?1?" -> {"0010", "0011", "0110", "0111"}
 *
 * Auf Papier sollten die Strings ausgegeben werden. Für die Tests werden sie
 * stattdessen zurückgegeben.
 */

void listPatternsRec(std::string &s, int i) {
  if (i >= s.length()) {
    std::printf("%s", s);
    return;
  }

  if (s[i] == '?') {
    s[i] = '0';
    listPatternsRec(s, i + 1);

    s[i] = '1';
    listPatternsRec(s, i + 1);

    // Ursprünglichen Zustand wiederherstellen
    s[i] = '?';
  } else {
    listPatternsRec(s, i + 1);
  }
}
std::vector<std::string> listPatterns(std::string s) { listPatternsRec(s, 0); }

} // namespace aud::endterm_2023::exercise_09
