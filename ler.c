#include <stdio.h>
#include <stdlib.h>


void leitura(FILE *arq, int n){
	printf("%d", arq);
	for(int i=0; i < n; i++){
		int result = fgetc(arq);
		printf("olaaaaa: %x ", result);
	}
	printf("oiiiii \n");
}

void main()
{
FILE *arq = NULL;
char Linha[100];
int result;
int i,w,l=0;


arq = fopen("mbr.bin","rb");
printf("%d", arq);
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
if(w >=416 ){
	printf("%x", result);
	break;
	Linha[l] = (char) result;
	l++;
	
}
w++;
i++;
}

}
leitura(arq,3);
printf("w: %d",w);
//printf("linha: %s",Linha);
fclose(arq);
}
