//Ejercicio 10. Los enlaces se crean con la orden ln

//Parte 1. Crea un enlace simbólico a un fichero ordinario y otro a un directorio.
//Comprobar el resultado con ls -l y ls -i. Determinar el i-nodo de cada fichero.

ln -s nuevoEnlace.txt enlacSimbolico.txt
ln -s nuevoDir dirSimbol
ls -l
ls -i
3147346 enlacSimbolico.txt
3147347 dirSimbol

//Parte 2. Repetir el apartado anterior con enlaces rígidos. Determinar los i-nodos de los ficheros
//y las propiedades con stat(observar el atributo número de enlaces).

ln nuevoEnlace.txt enlaceRigido.txt
stat nuevoEnlace.txt
(Se ha creado un nuevo link al comprobar con stat).

//Parte 3. 
//¿Qué sucede cuando se borra uno de los enlaces rígidos?
Se decrementa el contador de enlaces del fichero original.
//¿Qué sucede cuando se borra un enlace simbólico?
Se elimina de la tabla de ficheros y directorios.
//¿Qué sucede cuando se borra el fichero original?
Si tenía enlace simbólico asociado ese fichero queda inutilizable. Disponía de un i-nodo distinto pero dependía del fichero original.
Si tenía enlace rígido, este pasa a ser el fichero principal. Tenía el mismo i-nodo que el fichero original por tanto ahora solo existe un enlace de ese mismo fichero pero con otro nombre.
