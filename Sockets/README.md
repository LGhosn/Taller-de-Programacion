# Sockets - **algun nombre de tu preferencia**

Padrón: 106998

Nombre: Lautaro Gabriel Ghosn 

*A partir de acá pones una descripción de tu solución, de
como resolviste esta parte del TP.*

El tp lo traté de resolver de la forma más estructurada posible como ustedes recomendaron, al principio me armé una especie de guía con pasos de lo que tenía que hacer y cómo pensaba implementarlo.
Empecé haciendo el mapa ya que para mí era lo más fácil que podía encarar, al principio empecé con la idea de tener una clase Mapa que tenga como atributos el ancho, alto y un vector de tuplas que contenga únicamente los lugares que estaban ocupados en el mapa, cómo soy nuevo en C++ no tenía mucho idea cómo se manejan las tuplas acá entonces cuando lo estaba implementando se me hizo complicado y terminé desistiendo de esa idea.
Entonces fui por una idea más básica, hacer el mapa cómo una matriz de ancho x alto y listo, esa idea tuvo éxito y es la que quedó al final de la implementación. Una vez terminada esta implementación, me hice unos tests aparte para ver si el mapa funcionaba como quería, cómo pasaron las pruebas que hice era momento de seguir a otro paso.
Así es como seguí con la parte del parseo del archivo entrante, la cuál fue sumamente rápida usando el operador << para extraer todo.
Ahora tenía que seguir con el protocolo y el socket. Acá quiero hacer un paréntesis importante porque le estuve dando vueltas para hacer mí propio tda socket pero terminé utilizando el tda Socket de Martín, el cuál no sabía si poner un copyright en el archivo para marcar que es de él y no mío. 
Entonces con esta decisión tomada me puse a hacer el protocolos y acá perdí el hilo de la estructura mental para programar que me había hecho, y empecé a programar sin pensar más o menos, todo esto porque no me cerraba la idea de lo que tenía que hacer, no entendía cómo funcionaba el envío y recepción de mensajes a través de los sockets.
Claramente esto fue porque yo no implementé los sockets, lo cual me ahorró mucho tiempo pero me quitó a la hora de seguir con el resto del tp. Por lo que decidí releerme más a fondo los handouts y googlear más.
Una vez que logré entender la idea de lo que quería plasmar me puse a implementar el protocolo, ahí surgió un problema más de no conocer el lenguaje y no saber cómo por ejemplo agrupar un par de uint16_t y uint8_t para mandarlos por el protocolo y del otro lado parsearlos, así que lo implementé de la manera más sencilla, un mensaje de envíar equivalía a uno de recibir así tenía todo parseado de una y lo recibía del otro lado más fácil.
De esta forma fue mí proceso para resolver el tp, empecé bastante organizado hasta que por ahorrar tiempo (usar el tda Martín) terminé cometiendo más errores hasta que le agarré bien la mano a lo que quería hacer.

---------------------------------------------------------------------
Reentrega:

Para la reentrega tuve en cuenta mayormente el comentario de modelar la clase `Server` y `Cliente` lo que me llevó a separar la clase `Protocolo` a las respectivas `ServerProtocolo` y `ClientProtocolo`, porque por más que sea un único protocolo, se comporta de diferente forma si es el server o si es el cliente por lo que me pareció
más claro hacerlo de esta forma.
Además realicé mejoras así ya no hay números mágicos y es todo mucho más consistente.
Así quedaría un gráfico de cómo está hecho el tp y como se hablan entre sí las clases:
![](http://www.plantuml.com/plantuml/png/POvD2WCX38NtdY8zm5oX3CowK9WJY1Eer2H5Ow6txyYuy6SZvBtuVLcJsgYPWhdf2mb1vMTSi2d1Zl6BiGxFA2fEWdJfmtwiGSu4XoVav8KnrMuB7bbn_D_7cn09x-BUgCPSR5YM--XhgajQ7ZY7rblHPMdsjIQO1NC_0iQWB7Nd3yIfNv6FJE4F)

Upadte:
Realice mas refactor asi las clases son mas legibles y sean mas pequeñas, y a su vez agregué excepciones para hacer una mejor implementación.
