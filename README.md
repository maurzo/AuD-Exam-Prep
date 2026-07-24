## Bauen und testen

Einmalig konfigurieren:

```sh
cmake --preset default
```
Alle Sets bauen und testen:

```sh
cmake --build --preset default && ./build/Testsuite
```

Nur ein Set testen:

```sh
./build/Testsuite endterm-2023
./build/Testsuite retake-2025
```

Verfügbare Set-Namen zeigt `./build/Testsuite --list`. Solange noch `TODO`-Rümpfe vorhanden sind,
kompiliert das Projekt, aber die betroffenen Tests melden erwartungsgemäß Fehler.

## Enthaltene Aufgaben

| Set | Datei | Funktionen/Operationen |
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

## Technische Konventionen

- Ausgaben wie `print(...)` werden als Rückgabewert modelliert, damit sie automatisch testbar sind.
- Die für `countDigits` angenommene Funktion `pi(i)` wird als aufrufbarer Parameter übergeben.
- Die Klassen- und Struct-Namen liegen in getrennten Namespaces, damit alle sechs Sets gleichzeitig
  in einer Testsuite gelinkt werden können.
- Baumhöhe zählt Kanten, „traurig“ bedeutet strikt größere Tiefe, und `generate` behält nur Werte, die
  in der Eingabe exakt einmal vorkommen.

