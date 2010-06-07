Este es un programita para testear soluciones al TP3 de Métodos Numéricos
(DC-FCEyN-UBA), 1er cuatrimestre 2010.

Permite agregar programas "arquero" y archivos de prueba. Cada archivo de
prueba es un tiro. El programita ejecuta cada programa arquero con cada archivo
de prueba, y luego reporta resultados. Las listas de archivos se guardan
entre sesión y sesión, al menos en windows, y se pueden borrar con la tecla DEL.

También se incluyen un archivo "arquero" para hacer pruebas, aunque es
demasiado simple como para aprobar el TP. :-)

Para compilar el "arqueros" debería alcanzar con el compilador. 
Para compilar el programa de testeo hace falta la biblioteca
wxWidgets 2.8.x. 

La librería se puede bajar de: http://www.wxwidgets.org/

En ubuntu se pueden instalar con: 
sudo apt-get install libwxgtk2.8-dev wx2.8-headers wx2.8-i18n
Luego, con el comando "make" se puede compilar la aplicación.

