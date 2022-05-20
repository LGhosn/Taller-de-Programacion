# Threads - **algun nombre de tu preferencia**

Padrón: **106998**

Nombre: **Lautaro Gabriel Ghosn**

*A partir de acá pones una descripción de tu solución, de
como resolviste esta parte del TP.*

El tp no está termiando, funciona con un único cliente pero me falta la parte de aplicar el monitor para que este encapsule las critical sections y así sea multithreading.
Comencé a resolver el tp como si fuera un único cliente, porque a mi manera de ver era la manera más fácil, porque si ya tenía toda la estructura de cómo se manejaban las operaciones una vez el server lo recibía, era únicamente aplicarle los threads y hacerlo funcionar. Pero tardé más de lo que esperaba para hacerlo funcionar con un único cliente por lo que se me atrasó todo el calendario mental que tenía hecho para la resolución. Así que por ahora estoy en este punto donde funciona con un único cliente, pero claramente no está terminado, aunque mucho no le falta para completar toda su funcionalidad. 
Todavía no voy a agregar el gráfico porque no está terminado el diseño.
Me gustaría aprovechar este espacio para preguntar si hacer como hice de tener el archivo `common_imports.h` es algo válido o no y también quiero preguntar dónde es que se tiene que forzar el `socket.shutdown()` y el `socket.close()` cuando el server recibe una `q` por stdin. Porque por discord dijeron que "matar las conexiones de los clientes puede hacer que la salida no matchee y no te pasen los tests." ... "El que sí hay que shutdownear es el socket aceptador, para que se desbloquee". Pero a mi me pasa que si "mato" al server que es el que va a aceptando las conexiones me tira un error por pantalla que no va a pasar los tests, pero si "mato" a los otros únicamente, no termina a los clientes ni a al server, calculo que es porque se queda esperando al join, entonces no sé si debería solo esperar o cúal cerrar bien.
Espero terminar el tp cuanto antes así poder reentregarlo, disculpe la demora.

---

**Update**: Ahora sí, el tp funciona y cumple con lo que pide, tiene cosas para mejorar como la aplicación de `typedef bool (ClienteProtocolo::*mensajes_t)(std::string argumento);``mensajes_t mensajes[] = {listar, crear, unir};` que quería hacer para evitarme unos if y que quede más prolijo, pero no logré hacer que funcione, así que si podría guiarme con eso lo agredecería y lo podría aplicar para las casas con otro formato, así quito la mayor cantidad de ifs posibles.
En grandes rasgos, el grafico de como es que los hilos se lanzan en el tp es así:
![](http://www.plantuml.com/plantuml/png/TP7HQlCm38Nl_HIwA_pG5mYbjFmlC1Yx6cE8HcFk73crdR3kwIUdgQEQx2gEz9sZO-iG4uOqTCx88H5yMkVVyKHzmjO7sEq-VFZQxythlpVORlVmJ66aO6wVNAaKfZ8eHCoArVQnQ5M43fdEZn6EMbLHfXAfO5drP_laB76YUVBPMrueYZ8xbsIsyfh4DMcqsoe13RmmWVDncXoXlVqev365vUNgwWMpUI5cKtAJfrWwzPfr0XtBiYcdgIxxlI-rWV-1C9lEXIiuv1yiOvOHEbS3JnXHKEZmwWFq6181nPu2SkihjXU2E0LiKPWa10OO665psPHDwonBhOvJhgYtj1wd8aeuu856Z73oJD_MSxtG1ev9JlUL4KSyKuJB80K2uj4YJwrP4Cr1wA5plm00)
