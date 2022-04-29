#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	FILE *fp ,*fy; 	//Pointer ke file
	char buff [255];	
	char angka [15][15];
	char ree [10];	
	int i=2, j=0, y;
	

	
	fp = fopen("/tmp/data.txt", "r"); //membuka file 
	if(fp == NULL) {
      perror("Error in opening file");
      return(-1);
   }  while(fgets(buff, sizeof(buff), fp)){
	   strcat(angka[i],buff);
        printf("%s", angka[i]);
        i++;
    } 
    for(i = 2; i<=7; i++){
		if(strlen(angka[i]) != 0){ 
	 for(int j=0; j<=6; j++)
	 {
	 if(angka[i][j] == ',')
	 { // Memisah koma dari string coba
		angka[i][j] = ' ';
		
	 }
	
	printf("%C", angka[i][j]); //Cek print didalam konsol	
	 }
	 }
	printf("%c", y); //Cek print didalam konsol
   fclose(fp);
   return(0);


}
