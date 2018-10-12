  #include <stdio.h>
  #include <errno.h>

  int main( int argc, char *argv[] )
  {

    FILE *fp;

    if (argc < 2) return 1;

    fp = fopen(argv[1], "w");

    if (fp == NULL) {

      switch(errno) {

        case EACCES:
          printf("Can't access file.\n");
          break;

        case EISDIR:
          printf("Can't operate on directory.\n");
          break;

        default:
          printf("another error occurred.\n");
          break;

      }

      return 1;

    }

    fclose(fp);

    return 0;
  }
