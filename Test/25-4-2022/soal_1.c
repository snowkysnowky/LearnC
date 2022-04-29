#include "soal_common.c"

int main(int argc, char *argv[]){
	read_file("data_asli.txt");		//Membaca file bernama data_asli.txt
	printf("jumlah data = %d\n",number_data); //prtint number data
	
	reinput test;				//struct dengan nama test
	test = getdata();			
	dataInput dataBaca;			//membuat struct dengan nama dataBaca
	dataBaca.Input1 = calloc(9999,sizeof(char));	//alokasi memori 
	dataBaca.Input2 = calloc(9999,sizeof(char));	//alokasi memori
	
	
int count=0;
	for(int i=1;i<number_data+1;i++){ //perulangan sebanyak number data +1
		count++;		//count + 1
		dataBaca.Input1[count]=IntToChr(test.redata1[i]);	//Mengisi dataBaca.Input1
		dataBaca.Input2[count]=IntToStr(count);				//mengisi dataBaca.Input2
	}
																
	for(int i=1;i<number_data+1;i++){ //perulangan sebanyak number data +1
		count++;		//count + 1
		dataBaca.Input1[count]=IntToChr(test.redata2[i]);	//Mengisi dataBaca.Input1
		dataBaca.Input2[count]=IntToStr(count);				//mengisi dataBaca.Input2
	}
	
	dataBaca.ndata = count;    //Mengisi int dataBaca.ndata dengan numer data
	save_data_file("data_copy.txt",dataBaca);	//menyimpan data ke file baru
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;	//membebaskan memori
	free(dataBaca.Input2),dataBaca.Input2=NULL; //membebaskan memori
	
}
