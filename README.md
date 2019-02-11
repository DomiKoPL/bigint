Opis projektu:
    ./app aby właczyć aplikację

    bigint.h - zawiera spis funcki, które moża wykonac na strukturze BigInt

    bigint.c  - zawiera funcje porównywania, wypisywania, konwersji

    biginto.c - zawiera podstawowe operacje arytmetyczne takie jak dodawanie,odejmowanie, mnozenie, dzielenie, modulo

    bigintc.c - zawiera funkcje odpowiadajace za tworzenie nowej struktury BigInt, funkcje przypisania stringa itp.

    fft.c i fff.h - zawierają implementację algorytmu FFT wykorzystywanego do szybkiego mnożenia BigIntów

    parser.c i parser.h - zawierają implementację parsera wyrażeń arytmetycznych służaczego do obliczania wartości wyrażeń.


    BigInt - liczbe reprezentuje jako wielomian :
    X = a0 + a1 * p + a2 * p^2 + .. + an * p^n
    gdzie p = 10^9.

    Parser tworzy takowe drzewo operacji arytmetycznych.
    np. : 1 + 3
        +
      /   \
    1       3

    1 - 3 * 7 
         -
       /   \
      1      *
           /   \
          3     7

    i teraz rekunrenyjnie od liści drzewa oblicza kolejne wartości wyrażeń.