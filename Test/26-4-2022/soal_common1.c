#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int goAgain() {
	    char ch;
	     
	    printf("Again? (Y/N): ");
	    scanf(" %c", &ch);
	    return (ch=='Y' || ch=='y');
	}


typedef struct{
 char **dataOut;
 int ndata;
 int nDay;
} dataPrint;
	
//Array
static char months[12][20] = {"January","February","March","April","May","June","July","August","September","Oktober","November","December"};
char *Hari[] = {"SENIN","SELASA","RABU","KAMIS","JUMAT","SABTU","MINGGU"};//bisa diubah, posisi string menyesuaikan panjang string secara otomatis
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
    return year % 400 == 0
            || (year % 4 == 0
                && year % 100 != 0);
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

int dayNumber(int day, int month, int year) // untuk menentukan hari pertama dalam bulan
{	
	month+=1;
	
  
    static int t[] = { 0, 3, 2, 5, 0, 3,
                       5, 1, 4, 6, 2, 4 };
    year -= month < 3;
    return (year + year / 4
            - year / 100
            + year / 400
            + t[month-1] + day)
           % 7;
}

int Baris(int hari_awal,int jumlah_hari){		//Untuk menyesuaikan jumlah baris
	int nbaris;
	int mbaris = (hari_awal-1)+jumlah_hari;
	
		if (mbaris == 28){					//jika hari awal+jumlah hari = 28,maka ada 4 baris 
		nbaris = 4;
		}
		else if(mbaris >35){				//jika hari awal+jumlah hari > 35,maka ada 6 baris 
			nbaris = 6;
		}else{nbaris = 5;}					//Selain itu 5 baris
		
		return nbaris;
}
				
char *IntToStr(int x){						//Merubah integer ke string
	char *str=(char *)malloc(1 * sizeof (char));
	sprintf(str, "%d", x);
	return str;
}

char *get_string_from_index(char *string, int in1, int in2){
	char *cr1 = (char*)malloc(strlen(string));
	char *cr2 = (char*)malloc(strlen(string));
	char *Result = (char*)malloc(strlen(string)); 
	
	strcpy(cr1,&string[in1]);
	strncat (cr2, cr1, (in2+1-in1));
	
	strcat(Result, cr2);
	return Result;
}

char* gabung_kata(const char *s1, const char *s2)		//Menggabungkan 2 char atau string
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char* replaceWordInString(const char* s, const char* oldW, const char* newW){ 
    char* result; 						//Mengganti karakter lama dengan karakter baru
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
    for (i = 0; s[i] != '\0'; i++) { 
        if (strstr(&s[i], oldW) == &s[i]) { 
            cnt++; 
            i += oldWlen - 1; 
        } 
    } 
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
    i = 0; 
    while (*s) { 
        if (strstr(s, oldW) == s) { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
}

char *trim(char *s) {				//Menghapus space diawal string
	int count = -1;
	for(int i=0;i<strlen(s)+1;i++){
		if(isspace(s[i])==0){
			count = i;
			break;
		}
	}
	
	char *result = calloc((strlen(s)+1),sizeof(char));
	int count1 = -1;
	for(int i=count;i<strlen(s)+1;i++){
		count1++;
		result[count1] = s[i];
	}
	
	return result;
}

char *shift_trim(char *s) {		// Menghapus space diakhir string
	int count;
	for(int i=1;i<strlen(s)+1;i++){
		count = strlen(s)-i;
		if(isspace(s[count])==0){
			count = strlen(s)-i;
			break;
		}
	}
	char *result = calloc((strlen(s)+1),sizeof(char));
	int count1 = -1;
	for(int i=0;i<count+1;i++){
		count1++;
		result[count1] = s[i];
	}
	
	result = trim(result);
	return result;
}

int c_round(double x){					//Untuk Pembulatan
	return x < 0 ? x - 0.5 : x + 0.5;
}

dataPrint ProcessData(int DayBegin, char *lineborderTop, char *lineborderVet, char *space, char *whitespace, char *dayName[], int nBaris,int numdays){
	static int TanggalDummy[50];
	static int nHari = 7;
	static char *valBaris[200];
	static int HitungHari=-1;
	static char *lineborderTop1;
	static int BatasMargin1,BatasMargin2;
	static char *txtResult = NULL;
	char **datain = calloc(9999,sizeof(char));
	static int countBorder = 0;
	static char *tmpchar1 = "";
	static char *tmpchar = "";
	static char *sspace = " ";
	static char *space1[7],*space2[7];
	static int pt1[7],pt2[7];
	lineborderTop1 = gabung_kata("+",lineborderTop);
	datain[0] = "";
	
	if(DayBegin<1 || DayBegin>7){printf("Error! Day coloumn must be between 1-7\n");exit(1);}
	
	for(int i=0;i<numdays;i++){TanggalDummy[i]=i+1;}	//Pengulangan sebanyak numdays
	for(int i=0;i<nHari;i++){							//mengisi TanggalDummy sebanyak numdays
		space1[i]="";									
		space2[i]="";
		pt1[i] = c_round((strlen(lineborderTop)+2-strlen(dayName[i]))/2);
		pt2[i] = strlen(lineborderTop)+1-(strlen(dayName[i])+pt1[i]);
		
		for(int s=0;s<pt1[i];s++){space1[i] = gabung_kata(sspace,space1[i]);}
		for(int s=0;s<pt2[i];s++){space2[i] = gabung_kata(sspace,space2[i]);}
	}
	
	for(int i=0;i<nHari;i++){
		datain[0] = gabung_kata(datain[0],gabung_kata(gabung_kata(space1[i],dayName[i]),space2[i]));
	}
	
	for(int k=0;k<nBaris+2;k++){
		countBorder++;
		datain[countBorder] = "";
		for(int i=0;i<nHari;i++){
			txtResult = i<(nHari)-1 ? lineborderTop1 : gabung_kata(lineborderTop1,"+");
			datain[countBorder] = gabung_kata(datain[countBorder],txtResult);
		}
		if(k<nBaris){
			
			for(int j=0;j<3;j++){
				txtResult=space;
				countBorder++;
				int ndata = (strlen(lineborderTop1)*(nHari+1));
				for(int i=0;i<ndata;i++){
					tmpchar1 = tmpchar;
					if(i%strlen(lineborderTop1) == 0 || i==0){
						BatasMargin1 = i+1;
						BatasMargin2 = i+2;
						if(j==1 && i<strlen(lineborderTop1)*(nHari)){
							if(k==0 && i>=(DayBegin-1)*strlen(lineborderTop1)){HitungHari++;}
							else if(k>0){HitungHari++;}
						}
						valBaris[i]=lineborderVet;
					}
					else{valBaris[i]=" ";}
					
					if(j==1 && i<=BatasMargin2 && i>BatasMargin1 && i<strlen(lineborderTop1)*(nHari)){
						valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),0,0);
					}
					
					tmpchar = shift_trim(get_string_from_index(valBaris[i],0,0));
					
					if(TanggalDummy[HitungHari] > 9 && TanggalDummy[HitungHari] < 20){
						if(atoi(tmpchar1)==1){valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),1,1);}
					}else if(TanggalDummy[HitungHari] > 19 && TanggalDummy[HitungHari] < 30){
						if(atoi(tmpchar1)==2){valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),1,1);}
					}else if(TanggalDummy[HitungHari] > 29 && TanggalDummy[HitungHari] < 40){
						if(atoi(tmpchar1)==3){valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),1,1);}
					}else if(TanggalDummy[HitungHari] > 39 && TanggalDummy[HitungHari] < 50){
						if(atoi(tmpchar1)==4){valBaris[i]=get_string_from_index(IntToStr(TanggalDummy[HitungHari]),1,1);}
					}

					txtResult = gabung_kata(txtResult,valBaris[i]);
					for(int i=32;i<50;i++){
						if(strstr(txtResult, shift_trim(IntToStr(i))) != NULL){txtResult=replaceWordInString(txtResult,shift_trim(IntToStr(i)),"0 ");}
					}
					if(strstr(txtResult, gabung_kata(lineborderVet," 0")) != NULL){
						txtResult=replaceWordInString(txtResult,gabung_kata(lineborderVet," 0"),gabung_kata(lineborderVet,"  "));
					}
				}
				datain[countBorder] = shift_trim(txtResult);
				if(strstr(datain[countBorder], " ") != NULL){datain[countBorder]=replaceWordInString(datain[countBorder]," ",whitespace);}
			}
		}
	
	}
	
	dataPrint dataout;
	dataout.dataOut = calloc(9999,sizeof(char));
	for(int i=0;i<countBorder;i++){
		dataout.dataOut[i] = gabung_kata(space,datain[i]);
	}
	dataout.ndata = countBorder;
	dataout.nDay = TanggalDummy[HitungHari] > 31 ? 31 : TanggalDummy[HitungHari];
	
	free(datain),datain=NULL;
	
	return dataout;
}
