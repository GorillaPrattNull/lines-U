   #include <stdio.h>
   #include <sys/mman.h>

   char data[4096];

   int main()
   {
   int ret;


     ret = mlock(&data, 1024);

     printf("mlock ret = %d\n", ret);

     ret = munlock(&data, 1024);

     printf("munlock ret = %d\n", ret);

     return 0;
   }
