//Ej1. Comprobar el funcionamiento de nice y renice cambiando el valor de nice de la shell a -10
//y después cambiando su política de planificación a SCHED_FIFO con prioridad 12.

//Cambiar nice de bash a -10
nice -n-10 nash
nice //comprobarlo

//Cambiar política de planificación a SCHED_FIFO con prioridad 12
chrt -f -p 2230 //cambiar
chrt -a -p 2230 //consultar

