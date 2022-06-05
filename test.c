#include<stdio.h>

 

int main(int argc, char* argv[])

 

{

   FILE *archivo1, *archivo2;

	unsigned char c, c2;

 

	archivo1 = fopen("salida_make.txt","r");

   archivo2 = fopen("figuras_out.txt","r");

 

	if (archivo1 == NULL || archivo2 == NULL)

   {

      printf("\nError de apertura de archivos.\n\n");

 		getchar();

   }else{

      do{

    	   c=fgetc(archivo1);

         c2=fgetc(archivo2);

      }while(feof(archivo1)==0 && feof(archivo2)==0 && c == c2);

 

      if (c == c2){

         printf("\nSon iguales");

      }else {

         printf("\nNo son iguales");

      }

   }

   if(archivo1 != NULL)

      fclose(archivo1);

   if(archivo2 != NULL)

      fclose(archivo2);

	getchar();

   return 0;

}