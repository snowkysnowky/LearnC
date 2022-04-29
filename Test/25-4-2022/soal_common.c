#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int datainput_1[99999],datainput_2[99999];
int number_data;
char *txtResult = NULL;
char datain1[200],dataraw[999999][200];

typedef struct{
 char **Input1;
 char **Input2;

 int ndata;
} dataInput;

typedef struct{
 int redata1[999];
 int redata2[999];
} reinput;

//Mengubah karakter yang dinginkan menjadi karakter lain
char* replaceWordInString(const char* s, const char* oldW, const char* newW){ 
    char* result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 	//mengecek panjang neW
    int oldWlen = strlen(oldW); 	//mengecek panjang oldW
    for (i = 0; s[i] != '\0'; i++) { 	//loop hingga akhir char s
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

char *trim(char *s) {
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

char *shift_trim(char *s) {
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

 char *IntToStr(int x){ 	//Untuk mengubah Integer ke String
	char *str=(char *)malloc(1 * sizeof (char)); //Alokasi memory ke *str
	sprintf(str, "%d", x);		//Menyimpan int x ke str
	return str;					//memindahkan nilai str ke *IntToStr
}

char *IntToChr(int x){ 	//Untuk mengubah Integer ke Char
	char *str=(char *)malloc(1 * sizeof (char)); //Alokasi memory ke *str
	sprintf(str, "%c", x);		//Menyimpan int x ke str
	return str;					//memindahkan nilai str ke *IntToStr
}

void read_file(char *namafile){
	FILE *fileinput = fopen(namafile, "r");		//Membuka file sesuai nama file
    	
	int i = 0;
	int j = 0;
	while(!feof(fileinput)){			//
		i++;							//i+1
		fgets(datain1,200,fileinput);	//mengambil satu baris data dari file
		strcpy(dataraw[i], shift_trim(datain1));
		if(strlen(dataraw[i])>=0){j++;strcpy(dataraw[j], shift_trim(datain1));}
	}
	
	fclose(fileinput);					//Menutup file
	number_data = j;					

	if(strlen(dataraw[number_data]) == strlen(dataraw[number_data-1])){number_data=j-1;}
	else{number_data = j;}
}


reinput getdata(){
	reinput get;
	char datain1[20],datain2[20];
	for(int i=1;i<number_data+1;i++){
		txtResult = replaceWordInString(dataraw[i],","," ");
		sscanf(txtResult,"%s %s ",datain1,datain2);
		get.redata1[i] = *datain1; 
		get.redata2[i] = *datain2;	
	} 
	return get;
}

void save_data_file(char *namafile, dataInput datatulis){
	FILE *fileoutput = fopen(namafile, "w"); 
    for (int i = 1;i < (datatulis.ndata+1);i++){
		fprintf(fileoutput, "%s%s\n",  datatulis.Input1[i], datatulis.Input2[i]);
	}
    fclose(fileoutput);
}

int c_round(double x){
	return x < 0 ? x - 0.5 : x + 0.5;	//jika x kurang dari 0
}										//maka x - 0.5
										//jika tidak x + 0.5

double c_modulus(double a,double b){
	double tempres;					
	tempres = c_round(b*((double)(a/b)-(int)(a/b)));
	return tempres;
}

	long decimalToBinary(int decnum)
	{							//Untuk merubah data decimal menjadi binary
		long binum = 0;
		int rem, temp = 1;

		while (decnum!=0)
		{
			rem = decnum%2;
			decnum = decnum / 2;
			binum = binum + rem*temp;
			temp = temp * 10;
		}
		return binum;
	}


int isGanjil(int num)
{
	if (num == 0 || num == 1)
		return 1;
	else
		return (c_modulus(num,2) == 0 ? 0 : 1) ;
}

int convert(long long n) {		//untuk mengkonversi data binary ke decimal
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }
  return dec;
}


