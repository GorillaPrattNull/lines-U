     #include <pthread.h>
     #include <stdlib.h>
     #include <stdio.h>
     #include <string.h>
     #include <errno.h>

     pthread_once_t my_init_mutex = PTHREAD_ONCE_INIT;

     void initialize_app( void )
     {
          printf("Init\n" );
     }

	void *myThread( void *arg )
        {
          pthread_once( &my_init_mutex, initialize_app );
	  pthread_t pt; //Thread Identifier
          pt = pthread_self();
          printf("Thread Identifier:  %x\n", (int)pt );
      	  printf("Thread is running!\n");
      	  printf("Thread %d is detaching\n", (int)arg );
          pthread_detach( pt );
       	   /* Terminate the thread */
           pthread_exit( arg );
           //pthread_exit( NULL );
        }

     int main()
     {
       int ret;
       pthread_t mythread;

       ret = pthread_create( &mythread, NULL, myThread, NULL );
       
       //add sleep because this program runs to fast for the thread to execute.
       sleep(3);

       if (ret != 0) {
         printf( "Can't create pthread (%s)\n", strerror( errno ) );
         exit(-1);
       }
       return 0;
     }
