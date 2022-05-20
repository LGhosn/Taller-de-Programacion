# Onboarding - Contador de Palabras

Padrón: 106998

Nombre: Lautaro Gabriel Ghosn

*A partir de acá pones una descripción de tu solución, de
como resolviste esta parte del TP.*

Como los README.md de Github son
[markdown](https://guides.github.com/features/mastering-markdown/),
podes hace informes simples pero elegantes.

Por ejemplo podes estresar **una cosa** u *otra cosa*. Preferí usar
*italics* y dejar **bold** solo para pocas cosas.

Para código podes resaltar código inline como `unsigned long c = 0`
o bien como un bloque de código separado:

```cpp
unsigned long c = 0;
while (c < 10) {
   ++c;
}
```

Como muchas veces una imagen explica mas que 1000 palabras, **tenes que
incluir al menos 1 diagrama**. Puede ser de clase, secuencia,
*whatever*.

Te recomendamos que uses [PlantUML](https://plantuml.com) que te permite
generar diagramas a partir de texto.

Incluye un [editor
online](https://www.plantuml.com/plantuml/uml/SyfFKj2rKt3CoKnELR1Io4ZDoSa70000)
en donde no solo podes editar y ver tu diagrama sino también podes
obtener un *link al PNG* que luego podes agregar a tu README.md

![](https://www.plantuml.com/plantuml/png/SoWkIImgAStDuV9FoafDBb6mgT7LLN0iAagizCaiBk622Liff1QM9kOKQsXomIH1WX3Pw5Y5r9pKtDIy4fV4aaGK1SMPLQb0FGwfUIb0Im00)

*Recordá, queremos que expliques como solucionaste el trabajo, no
queremos un diagrama detallado por que sí. Para leer exactamente todos
los métodos de todas tus clases ya tenemos el código.* **Poné solo lo importante.**

Proceso de solución del tp:
Lo primero que hice fue usar los static checkers para encontrar los potenciales errores y estilos del archivo. Eso me llevo a ver que faltaban y sobraban espacios en ciertos lugares, también faltaba el copyright y algo más importante (a mi criterio) la variable state no estaba inicializada `char state;`. De este barrido también aprendí que cpplint sigue la guía de includes de google (https://google.github.io/styleguide/cppguide.html#Names_and_Order_of_Includes), por lo cual modifique esa parte para que quedara bien. 
Después con una mirada más profunda a ojo me molestaban los números "mágicos" por lo que hice un par de `#define` para que quede más legible el código, a su vez noté que nunca se estaba liberando la memoria en el main del archivo y del wordscounter por lo que puse los delete correspondientes y cerré el archivo al finalizar, otra cosa que modifiqué fue que en la documentación del método `process` decía que devolvía números pero no estaba implementada de esa manera por lo que la cambié para respetar la documentación.
Paralelamente, a medida que iba haciendo este barrido a ojo, me hice un diagrama para poder entender cómo era el algoritmo que seguía este programa. 
![](http://www.plantuml.com/plantuml/png/RP71xjCm3CRlUGfp-_-H1jkEqrHDGaFY0XCSE224lCJJ8bAdSfmAzZOy2oz6qsxP2fpQVlvi__nrbnH5SnlC2prJIt0CcJhnhEPp59TipAmai84t0HE1ZQpeeY0uWWu37WMJsIT5TYZlkCiAYmOUU-VLOT8XaoD89D2IyyXAW6BFleyG8QdpFD-z60OU95fAoLoVPSSdHQLbLOhhFVtGKQxg1lPjv-c2G0mKW5B1XoKGU2N1kx5KTUYFSCR114hIUaO94Px6cUldLwOkc45LjQphCMI4W92FtgBraKjK0MzfpTm_XrgVAVG4cO4pzV6AQD9eEKNv_crwtMxBHzCyGZGF1ZC5CapzI9rG8bOiHzdOUk9BB1YPAyVhyTYfQJLliXdPHGWuPLHkgBw2z_iN41TWYqDLIVuQFPdN_v2SF8EhCJ_jFxnzDdV--azNC_6chl-hBc-xYlBbvLUp8tQv3Ny0)
