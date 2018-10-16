#include <stdio.h>
#include <stdlib.h>
void main()
{
FILE *arq = NULL;
char Linha[100];
int result;
int i,w,l=0;

arq = fopen("mbr.bin","rb");

if(arq == NULL)
{
printf("Problemas de leitura\n");
return;
}
i=1;
while(!feof(arq))
{
result = fgetc(arq);
//printf("%x", result);
if(result){
	//printf("%x",result);


if(i == 2){
	
	printf(" ");
	i=0;
}
if(w >=419 ){
	printf("%x", result);
	Linha[l] = result;
	l++;
}
w++;
i++;
}

}
printf("w: %d",w);
printf("linha: %x",Linha);
fclose(arq);
}
