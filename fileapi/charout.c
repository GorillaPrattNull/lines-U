#include <stdio.h>

int main()
{
int i;
FILE *fout;
const char string[]={"This\r\nis a test\r\nfile."};

fout = fopen("inpfile.txt", "w");

if (fout == (FILE *)NULL) exit(-1);

i = 0;
while (string[i] != NULL) {

fputc((int)string[i], fout);
i++;

}

fclose(fout);

return 0;
}
