# Programmieraufgaben aus den AuD-Klausuren 2023-2025

Dieses Projekt enthält alle offenen Programmier- und Algorithmenentwurfsaufgaben aus den sechs
bereitgestellten Klausuren. Reine Multiple-Choice-, Laufzeit-, Zeichen- und Theorieaufgaben sind nicht
enthalten.

Jede Klausur ist ein eigenes CMake-Modul. Jede Datei folgt dem Schema
`<term>-<year>-<exercise>.cpp`. In den Funktionen ist nur der mit `TODO` markierte Rumpf zu ersetzen.
Signaturen, Datenstrukturen und 44 ausführbare Tests sind bereits vorhanden.

## Bauen und testen

Einmalig konfigurieren:

```sh
cmake --preset default
```

Dabei wird auch die von clangd/Neovim benötigte Kompilierungsdatenbank erzeugt.

Alle Klausuren bauen und testen:

```sh
cmake --build --preset default && ./build/Testsuite
```

Nur eine Klausur testen:

```sh
./build/Testsuite endterm-2023
./build/Testsuite retake-2025
```

Verfügbare Klausurnamen zeigt `./build/Testsuite --list`. Solange noch `TODO`-Rümpfe vorhanden sind,
kompiliert das Projekt, aber die betroffenen Tests melden erwartungsgemäß Fehler.

## Enthaltene Aufgaben

| Klausur | Datei | Funktionen/Operationen |
|---|---|---|
| Endterm 2023 | Exercise 09 | `listPatterns` |
| Endterm 2023 | Exercise 10 | `treeHeight`, `deepestLeavesSum`, `DoublyLinkedList::insertAt` |
| Endterm 2024 | Exercise 01 | `countDigits` |
| Endterm 2024 | Exercise 05 | `rootPaths`, `totalPaths` |
| Endterm 2024 | Exercise 06 | `traverse`, `minAbsDiff` |
| Endterm 2024 | Exercise 09 | `perimeter` |
| Endterm 2024 | Exercise 10 | `merge` |
| Endterm 2025 | Exercise 06 | `count`, `countSadNodes` |
| Endterm 2025 | Exercise 07 | `extract` |
| Endterm 2025 | Exercise 10 | `kClosestPair` |
| Retake 2023 | Exercise 09 | `validSequence` |
| Retake 2023 | Exercise 10 | `sumOfLeftLeaves`, `isSameTree`, `isSubtreeOf`, `DoublyLinkedList::deleteAt` |
| Retake 2024 | Exercise 01 | `generate` |
| Retake 2024 | Exercise 05 | `rightRotate` |
| Retake 2024 | Exercise 09 | `canVisitAllRooms` |
| Retake 2024 | Exercise 10 | `merge` |
| Retake 2025 | Exercise 06 | `countLeaves`, `count`/`countHappyNodes` |
| Retake 2025 | Exercise 07 | `merge`, `locate`, `swap` |
| Retake 2025 | Exercise 10 | `MedianStream::insert`, `MedianStream::getMedian` |

## Kleine Anpassungen gegenüber Papier

- Ausgaben wie `print(...)` werden als Rückgabewert modelliert, damit sie automatisch testbar sind.
- Die in Aufgabe 1 des Endterms 2024 als gegeben angenommene Funktion `pi(i)` wird als aufrufbarer
  Parameter übergeben.
- Die Klassen- und Struct-Namen liegen in getrennten Namespaces, damit alle sechs Klausuren gleichzeitig
  in einer Testsuite gelinkt werden können.
- Tests folgen dem Wortlaut der Aufgaben. Das ist relevant bei offensichtlichen Unstimmigkeiten in den
  Musterlösungen: Baumhöhe zählt Kanten, „traurig“ bedeutet strikt größere Tiefe, und Retake 2024
  `generate` behält nur Werte, die in der Eingabe exakt einmal vorkommen.

Die Tests enthalten normale Fälle, Randfälle und die Beispiele aus den Aufgabenblättern. Sie prüfen bei
verketteten Listen und Rotationen zusätzlich die Pointer-Struktur und, wo gefordert, dass Eingaben
unverändert bleiben.
