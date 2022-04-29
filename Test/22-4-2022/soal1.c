#include "soal_common.c"		//menggunakan file soal_common.c

int main(int argc, char *argv[]){
	read_file("data.txt");		//Membaca file bernama data.txt
	printf("jumlah data = %d\n",number_data); //prtint number data
	
	get_data_from_rawdata();	//mengambil data dari file dan mengganti ',' dengan spasi
	dataInput dataBaca;			//membuat struct dengan nama dataBaca
	dataBaca.Input1 = calloc(9999,sizeof(char));	//alokasi memori 
	dataBaca.Input2 = calloc(9999,sizeof(char));	//alokasi memori
	dataBaca.Input3 = calloc(9999,sizeof(char));	//alokasi memori
	
	for(int i=1;i<number_data+1;i++){		//perulangan sebanyak number data+1
		dataBaca.Input1[i]=IntToStr(datainput_1[i]);//mengkonversi int ke string
		dataBaca.Input2[i]=IntToStr(datainput_2[i]);//mengkonversi int ke string
		dataBaca.Input3[i]=IntToStr(datainput_3[i]);//mengkonversi int ke string
	}
	dataBaca.ndata = number_data;    //Mengisi int dataBaca.ndata dengan numer data
	
	save_data_file("data_copy1.txt",dataBaca);	//menyimpan data ke file baru
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;	//membebaskan memori
	free(dataBaca.Input2),dataBaca.Input2=NULL; //membebaskan memori
	free(dataBaca.Input3),dataBaca.Input3=NULL; //membebaskan memori
}
