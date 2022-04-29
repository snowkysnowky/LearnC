#include <stdio.h>

main()
{
	FILE *fp , *fy; 	//Pointer ke file
	int buff , x=0 ;	
	char angka[255];		//Untuk menampung file yang dibaca
	
	fp = fopen("/tmp/data.txt", "r"); //membuka file 
	if(fp == NULL) 
		{
		perror("Error in opening file\n");//Peringatan error membuka file
		return(-1);
		}
	while(1) 
		{
      buff = fgetc(fp);		//Membaca isi file
      if( feof(fp) ) 
			{ 
			break ;
			}
      angka[x] = buff;		//Menampung isi file ke text
      x++;
		}
	  fclose(fp);			//tutup file
	  for(int i = 0; i < sizeof(angka); i++)  //Mengganti ',' dengan ' '
		{	
	   if(angka[i] == ',')
			{
		   angka[i] = ' ';
			}
		} 
	fy = fopen("/tmp/data_copy1.txt", "w+"); //Membuat file baru
	printf("%s", angka);
	fputs(angka, fy);	//Menulis ke file baru
	fclose(fy);			//tutup file
}
