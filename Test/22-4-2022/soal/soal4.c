#include "soal_common.c"		//menggunakan file soal_common.c

int main(int argc, char *argv[]){
	read_file("data.txt");		//Membaca file bernama data.txt
	printf("jumlah data = %d\n",number_data); //prtint number data
	
	get_data_from_rawdata();	//mengambil data dari file dan mengganti ',' dengan spasi
	dataInput dataBaca;			//membuat struct dengan nama dataBaca
	dataBaca.Input1 = calloc(9999,sizeof(char));	//alokasi memori 
	dataBaca.Input2 = calloc(9999,sizeof(char));	//alokasi memori
	dataBaca.Input3 = calloc(9999,sizeof(char));	//alokasi memori
	
	int count=0;
	for(int i=1;i<number_data+1;i++){ //perulangan sebanyak number data +1
		count++;		//count + 1
		dataBaca.Input1[count]=IntToStr(datainput_1[i]);	//Mengisi databaca.Input1
		count++;		//count + 1
		dataBaca.Input1[count]=IntToStr(datainput_2[i]);	//Mengisi databaca.Input1
		count++;		//count + 1
		dataBaca.Input1[count]=IntToStr(datainput_3[i]);	//Mengisi databaca.Input1
	}
	dataBaca.ndata = count;
	for(int i=1;i<dataBaca.ndata+1;i++){
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";} //jika dataBaca.Input1 == NULL maka dataBaca.Input1 berisi ""
		dataBaca.Input2[i]=""; //mengganti dataBaca.Input2 dengan ""
		dataBaca.Input3[i]=""; // mengganti dataBaca.Input3 dengan ""
	}
	
	save_data_file("data_copy4.txt",dataBaca);	//menyimpan data ke file baru
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;	//membebaskan memori
	free(dataBaca.Input2),dataBaca.Input2=NULL; //membebaskan memori
	free(dataBaca.Input3),dataBaca.Input3=NULL; //membebaskan memori
}
