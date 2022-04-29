#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Need to include enum, union,multidimensional array, pointer

//Array
static char months[12][20] = {"January","February","March","April","May","June","July","August","September","Oktober","November","December"};
static char *days[] = {"   Monday     ","Tuesday   ","Wednesday  ","Thursday    ","Friday    ","Saturday    ","Sunday"};
static int monthDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

//Enum
typedef enum {
  false ,
  true 
} Bool;

//Union
union monthtype{
	int num; 
	char str[20];
}month;

// Mengembalikan nilai 1 atau 0
static int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

//mengambil data banyaknya hari dalam satu bulan
static int get_days_in_month(int year, int month0) {
    if (month0 == 1) {							//untuk cek bulan febuari 
												//jika tahun kabisat maka febuari akan ditambah 1
        int leap_days = is_leap_year(year);
        return 28 + leap_days;
    } else {
        return monthDays[month0];
    }
}

//Menentukan awal hari dalam suatu bulan
static int get_dow(int year, int month0, int day) {
    int dow = 3;  // 1800-01-01 is a Wednesday.
	dow--;
    // For each year up to provided year (exclusive), starting with 1800.
    while (year-- > 1800) {
        int leap_days = is_leap_year(year);
        dow += 365 + leap_days;
    }

    // For each month up to provided month (exclusive)
    while (month0--)
        dow += monthDays[month0];

    // For each day up to the provided day (exlcusive)
    dow += day - 1;

    return dow % 7;
}

int main() {
	Bool x = true;
    int year;
    int day = 1; // 1-based day
    
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
			printf("Invalid input. Try again\n");	//print bulan salah
			return main();				//Kembali ke main()
			}
	if (x == 1){
		month.num-=1;
    int dow      = get_dow(year, month.num, day);		//Menetapkan dow dari fungsi get dow
    int num_days = get_days_in_month(year, month.num);	//Menetapkan num_days dari fungsi get_days_in_month

    strcpy(month.str, months[month.num]); //menetapkan month.str dengan nama bulan dari array months[]
    printf("%38s %d\n\n", month.str, year);//print bulan dan tahun
    
   for (int i = 0; i < 7; i++){
	    printf("%s",days[i]);		// print hari
	}printf("\n");
    printf("+----------+----------+----------+----------+----------+----------+----------+\n");

    for (int i=0; i<dow; ++i)		//print whitespace untuk megisi kekosongan sebelum tanggal 1
       printf("|          ");

    while (day <= num_days) {		// Perulangan print tanggal
		
        printf("|%10d", day++);
        dow = ( dow + 1 ) % 7;
        if (!dow)
          printf("|\n|          |          |          |          |          |          |          |\n"
					"|          |          |          |          |          |          |          |\n"
					"|          |          |          |          |          |          |          |\n"
					"|          |          |          |          |          |          |          |\n"
					"+----------+----------+----------+----------+----------+----------+----------+\n");
         
          
    }
    if (dow){
        printf("|\n|          |          |          |          |          |          |          |\n"
				  "|          |          |          |          |          |          |          |\n"
				  "|          |          |          |          |          |          |          |\n"
				  "|          |          |          |          |          |          |          |\n"
				  "+----------+----------+----------+----------+----------+----------+----------+\n");
       
	}

}
	while ((getchar()) != '\n');	//flush buffer agar dapat menerima input user kembali						
    char ch; 						//Membuat prompt untuk lanjut atau tidak
	printf(" 1 untuk melanjutkan 0 untuk menutup : ");
	ch = getchar();
	while(1){
		if((ch != '1') && (ch != '0')){ //looping terus hingga mendapatkan nilai char '1' atau '0'
			while ((getchar()) != '\n'); //flush
			printf("\n 1 untuk melanjutkan 0 untuk menutup : ");
			ch = getchar();
		}else if(ch == '1'){
			return main(); //kembali ke atas 
		}else {
			return 0; //program selesai
		}
	}
}

