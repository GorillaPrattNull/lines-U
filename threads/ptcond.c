     #include <pthread.h>
     #include <stdio.h>
     #include <assert.h>
     pthread_mutex_t cond_mutex = PTHREAD_MUTEX_INITIALIZER;
     pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

     int workCount = 0;

     #define MAX_CONSUMERS 10

      void *consumerThread( void *arg )
       {
       int ret;
       pthread_detach( pthread_self() );
       printf( "Consumer %x: Started\n", pthread_self() );

       while( 1 ) {

         assert( pthread_mutex_lock( &cond_mutex ) == 0);
         assert( pthread_cond_wait( &condition, &cond_mutex )== 0);

              if (workCount) {
                workCount;
                printf( "Consumer %x: Performed work (%d)\n", pthread_self(), workCount);
              }
         assert( pthread_mutex_unlock(&cond_mutex ) == 0);
       }
         printf( "Consumer %x: Finished\n", pthread_self() );
         pthread_exit( NULL );
       }

     void *producerThread( void *arg )
     {
       int i, j, ret;
       double result=0.0;

       printf("Producer started\n");

       for ( i = 0 ; i < 30 ; i++ ) {

         ret = pthread_mutex_lock( &cond_mutex );
         if (ret == 0) {
           printf( "Producer: Creating work (%d)\n", workCount );
           workCount++;
           pthread_cond_broadcast( &condition );
           pthread_mutex_unlock( &cond_mutex );
         } else {
           assert(0);
         }

         for ( j = 0 ; j < 60000 ; j++ ) {
           result = result + (double)random();
         }

        }

        printf("Producer finished\n");

        pthread_exit( NULL );
      }


      int main()
      {
        int i;
        pthread_t consumers[MAX_CONSUMERS];
        pthread_t producer;

        /* Spawn the consumer thread */
        for ( i = 0 ; i < MAX_CONSUMERS ; i++ ) {
          pthread_create( &consumers[i], NULL, consumerThread, NULL );
        }

        /* Spawn the single producer thread */
        pthread_create( &producer, NULL, producerThread, NULL );

        /* Wait for the producer thread */
        pthread_join( producer, NULL );

        while ((workCount > 0));

        /* Cancel and join the consumer threads */
        for ( i = 0 ; i < MAX_CONSUMERS ; i++ ) {
          pthread_cancel( consumers[i] );
        }

        pthread_mutex_destroy( &cond_mutex );
        pthread_cond_destroy( &condition );

        return 0;
      }
