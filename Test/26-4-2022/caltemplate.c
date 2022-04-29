#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "soal_common1.c"

#define restart system("./caltemplate");		//mendefinisikan restart untuk membuka ulang file program

int main(){
	Bool x = true;
    int year;
	int day = 0;
	printf("\nMasukkan Tahun:");
	while(scanf("%d", &year)==0 ) //if scanf failed to scan an integer
{
    printf("Invalid input. Try again\n");
    printf("\nMasukkan Tahun:");
    int c;
    while((c=getchar())!='\n'); //clear the stdin
}
    printf("\nMasukkan Bulan:");
	scanf("%d",&month.num);			//Input bulan
	
	if (month.num>0 && month.num<13){	//jika bulan 1-12 maka x=1,jika tidak x =0
		x = 1;							
		}else {x= 0;
			printf("Invalid input. Try again\n");	//print error20
			return main();				//Kembali ke main()
			}
	if (x == 1){
	month.num-=1;		
    int current = dayNumber(day, month.num, year);		//Menetapkan current dari fungsi dayNumber
  	current++;								//Menyesuaikan bulan agar 1 = Januari
    int num_days = get_days_in_month(year, month.num);	//Menetapkan num_days dari fungsi get_days_in_month
    int jum_baris = Baris(current,num_days);
    strcpy(month.str, months[month.num]); //menetapkan month.str dengan nama bulan dari array months[]
    printf("%38s %d\n\n", month.str, year);//print bulan dan tahun
    
  
	char *garisbatasHorizontal = "---------";//bisa diubah, posisi tanggal menyesuaikan secara otomatis
	char *garisbatasVertikal = "|";//bisa diubah
	char *latarTanggal[] = {" ",".","*","#"};//index bisa dipilih dari 0-3 (untuk merubah tampilan kalender)
	char *spasiAwalKalender = "   ";//bisa diubah
	int kolomMulaiHari = current;//Menyesuaikan dengan tanggal
	int JumlahBarisKalender = jum_baris;//Menyesuaikan dengan tanggal
	dataPrint dataoutprint;
	
	dataoutprint = ProcessData(kolomMulaiHari,garisbatasHorizontal,garisbatasVertikal,spasiAwalKalender,latarTanggal[1],Hari,JumlahBarisKalender,num_days);
	
	for(int i=0;i<dataoutprint.ndata;i++){
		printf("%s\n",dataoutprint.dataOut[i]);
	}
	
	printf("\n\n  Jumlah hari = %d\n",num_days);	//Print jumlah hari pada bulan yang di input
	
	free(dataoutprint.dataOut),dataoutprint.dataOut=NULL;

	if (goAgain()) { restart; }		//Jika input Y atau y maka restart
}
return 0;							//Menutup program
}
