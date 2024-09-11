# danske tal opg 

## Kompilering

For at kompilere dette projekt på en ARM-baseret Mac M2, kan du bruge følgende kommando i terminalen:

```bash
mkdir -p build
gcc \
src/danish_number.c \
src/demo.c \
-o build/danish_number_2_letter
```
### Structs og deres brug

Dette projekt indeholder en funktion til at konvertere tal til deres danske tekstrepræsentation. For at gøre konverteringen fleksibel og tilpasses forskellige formateringsbehov, benyttes ad/af en række strukturer (`structs`) og enums til at konfigurere, hvordan tallene skal vises.

#### `NumberFormat` Struct

```c
typedef struct {
    Occurrence og;               // Angiver hvor 'og' skal bruges
    int skip_one_thousand;       // Angiver om 'et tusind' skal forkortes til 'tusind'
    Style style;                 // Angiver stilen (Normal, Formal, Uformel)
    int capitalize_first;        // Om første bogstav skal være stort
    int use_numeric_for_large;   // Om store tal skal skrives numerisk
    long long numeric_threshold; // Grænsen hvor numerisk repræsentation skal bruges
} NumberFormat;

```
