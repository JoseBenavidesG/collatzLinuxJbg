# collatzLinuxJbg
Conjetura Collatz para Linux


* author Jose Benavides G. josebenavidesg@gmail.com
* version 1.0.0
* date 23 Jan 2020
* History:
* ........20200123...JBG:	Initial code 
*.......................	Este es el codigo inicial, para el
*.......................	manejo de conjetura Collatz.  
*
* Compilation:
* 	Usted use el script ./compileAndRun.sh, que compila y pone en ejecucion el servicio
*
* Use:
* 	Como ya lo compilo y quedo ejecutandose atendiendo en el puerto 8080
* 	ahora para probarlo desde una consola puede probarlo, usando la sgte linea de comando:
*
*   	    curl http://localhost:8080/18/
*
*   y si quiere hacerlo desde un browser (navegador), use los gste:
*         http://localhost:8080/18/
*
* 	esto le entregara un mensaje JSON son la secuencia Collatz, como se esta :
*
* 	[9, 28, 14, 7, 22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1]
*
* Note:
* 	si usted, quiere solo ejecutar el servidor, sin tener que compilarlo, cada vez que lo ejecuta, despues
* 	de comnpilar, ejecute el sgte comando:
* 	./serverCollatz 
*
*	y el servidor estara esperando por un numero natural.
*
*************************************************************/
