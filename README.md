# MicroProcesador
Desarrollo de un MicroProcesador en la asignatura Arquitectura de Computadoras de la carrera Ingenieria de Sistemas (ULA)

# SystemC
# Pasos
  1) Para el uso del MicroProcesador es necesario instalar la libreria SystemC. el procedimiento a seguir lo puedes encontrar en el siguiente link: [SystemC](https://github.com/juliolugo96/computer_architecture#instalaci%C3%B3n-de-systemc)

  2) Para compilar con SystemC, cada vez que abren la terminal, tienen que ejecutar éste comando:
    $
    
    export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
    
  3) Para configurar un archivo para que al abrir la terminal se ejecute solo, se debe hacer lo siguiente:
      1)Utilizar un editor de texto que se pueda abrir de la Terminal (gedit, notepad, leafpad, xed, mousepad, subl, code...)
      escribes el siguiente comando:
           
    $ <editor>  ~/.bashrc
      
   4) luego les abrira un archivo en el cual deben copiar al final lo siguiente:
      para arquitecturas de 64 bits:
         
    $ export LD_LIBRARY_PATH=/usr/local/systemc-2.3.3/lib-linux64
     
   para architectura de 32bits:
          
     $ export LD_LIBRARY_PATH=/usr/local/systemc-2.3.3/lib-linux
      
   luego guardas el archivo y reinicias la terminal y listo, se ejecutara dicho comando cada vez que inicies la Terminal.
   
   # Diseño
   ![Diseño Microprocesador](https://github.com/miguelfg03/MicroProcesador/blob/master/MicroP.jpg)
      
   # Desarrolladores
    Dunia Marquina -25151464
    Marcos Gutierrez - 23727237
    Miguel Gil -23723985
