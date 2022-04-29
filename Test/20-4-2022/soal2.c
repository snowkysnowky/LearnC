#include <stdio.h>

main()
{
	FILE *fp ,*fy; 						//Pointer ke file
	int buff, x=0;						//Integer
	char angka [225];					//Char untuk menampung data
	
	fp = fopen("/tmp/data.txt", "r"); 	//membuka file 
	if(fp == NULL) 
		{
		perror("Error in opening file\n"); //Peringatan error membuka file
		return(-1);
		}
	while(1) 
		{
		buff = fgetc(fp);				//Membaca isi file
		if( feof(fp) ) 
			{ 
			break ;
			}
		angka[x] = buff;				//Menampung isi file ke text
		x++;
		}
	fclose(fp);							//tutup file 
	for(int i = 0; i < sizeof(angka); i++)	
		{	
		if(angka[1] == ',')				// Menghapus angka yang tidak perlu
			{
		   angka[2] = ' ';
		   angka[3] = ' ';
		   angka[8] = ' ';
		   angka[9] = ' ';
		   angka[14] = ' ';
		   angka[15] = ' ';
		   angka[20] = ' ';
		   angka[21] = ' ';
			}	  
		}
	fy = fopen("/tmp/data_copy2.txt", "w+"); 	//Membuat file baru
	printf("%s", angka);
	fputs(angka, fy);							//Menulis ke file baru
	fclose(fy);									//tutup file
  } 
 
	

