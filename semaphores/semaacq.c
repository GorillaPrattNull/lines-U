     #include <stdio.h>
     #include <sys/sem.h>
     #include <stdlib.h>
     #include "commonarray.h"

     int main()
     {
       int semid, i;
       struct sembuf sb[10];

        /* Get the semaphore with the id MY_SEM_ID */
        semid = semget(MY_SEMARRAY_ID, 10, 0);
     //   semid = semget(MY_SEM_ID, 10, 0);

        if (semid >= 0) {

          for (i = 0 ; i < 10 ; i++) {
            sb[i].sem_num = i;
            sb[i].sem_op = -1;
            sb[i].sem_flg = 0;
          }

          printf("semaacq: Attempting to acquire semaphore %d\n",
                  semid);

          /* Acquire the semaphores */
          if (semop(semid, &sb[0], 10) == -1) {

            printf("semaacq: semop failed.\n");
            exit(-1);

          }


        printf("semaacq: Semaphore acquired %d\n", semid);

      }

      return 0;
 }
