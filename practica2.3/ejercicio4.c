//Ej4. El comando ps es de especial importancia para ver los procesos del sistema y su estado.
//-Mostrar todos los procesos del usuario actual en formato extendido.
ps -el

//-Mostrar los procesos del sistema, incluyendo el identificado del proceso, el identificado del grupo de procesos
//el identificador de sesión, el estado y la línea de comandos.

ps -e -o pid,pgrp,session,stat,cmd

//-Observar el identificador de proceso, grupo de procesos y sesión de procesos.
//¿Qué identificadores comparte la shell y los programas que se ejecutan en ella?

El 1.   1     1     1 Ss   /usr/lib/systemd/systemd --switched-root --system --deserialize 22
Algunos más:
  460   460   460 Ss   /usr/lib/systemd/systemd-journald
  482   482   482 Ss   /usr/sbin/lvmetad -f
  492   492   492 Ss   /usr/lib/systemd/systemd-udevd
  747   747   747 S<sl /sbin/auditd
  749   749   749 S<sl /sbin/audispd
 1030  1030  1030 Ss   /usr/sbin/sshd -D
 1031  1031  1031 Ssl  /usr/bin/python -Es /usr/sbin/tuned -l -P
 1034  1034  1034 Ssl  /usr/sbin/rsyslogd -n
 1037  1037  1037 Ss   /usr/sbin/cupsd -f
 1050  1050  1050 Ss   /usr/sbin/atd -f
 1051  1051  1051 Ss   /usr/sbin/crond -n
 1320  1320  1320 Ss   /usr/libexec/postfix/master -
 1947  1947  1947 Ss   dhclient
 1952  1952  1952 Ssl  /usr/lib64/firefox/firefox
 12535 12535 12535 Ss   bash
 2462  2462  2462 Ssl  /usr/libexec/upowerd
 2700  2700  2700 Ss   bash 
 18018 18018  2230 S+   man ps

Los procesos cuyo comando es bash. En este caso 12535 y 2700.

//¿Cuál es el identificador de grupo de procesos cuando se crea un nuevo proceso?

