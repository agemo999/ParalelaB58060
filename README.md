# ParalelaB58060

CollatzOpenMp
make y luego correr el archivo generado normalmente

CollatzMpi
Para correr el mpi basta con usar el make
luego para correrlo
mpiexec -n numeroprocesos direccion_completa_ejecutable

CollatzOpenacc
con correr el make corre el archivo acelerando, tener un procesador nvidia y tener pgi

Sockets
make genera todo, correr server en una terminal y se queda esperando, luego con el cliente cuando lo corran 
va a pedir el ip, el puerto es generico en el server, luego pide el mensaje y lo envia al server y trata
de recuperarlo.
