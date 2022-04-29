#include "soal_common.c"		//menggunakan file soal_common.c

int main(int argc, char *argv[]){
	read_file("data.txt");		//Membaca file bernama data.txt
	printf("jumlah data = %d\n",number_data); //prtint number data
	
	get_data_from_rawdata();	//mengambil data dari file dan mengganti ',' dengan spasi
	dataInput dataBaca;			//membuat struct dengan nama dataBaca
	dataBaca.Input1 = calloc(9999,sizeof(char));	//alokasi memori 
	dataBaca.Input2 = calloc(9999,sizeof(char));	//alokasi memori
	dataBaca.Input3 = calloc(9999,sizeof(char));	//alokasi memori
	dataBaca.Input4 = calloc(9999,sizeof(char));	//alokasi memori
	dataBaca.Input5 = calloc(9999,sizeof(char));	//alokasi memori
	
	for(int i=1;i<number_data+1;i++){	
		datainput_1[i] = decimalToBinary(datainput_1[i]); //merubah datainput_1 dari decimal menjadi binary
		datainput_2[i] = decimalToBinary(datainput_2[i]); //merubah datainput_2 dari decimal menjadi binary
		datainput_3[i] = decimalToBinary(datainput_3[i]); //merubah datainput_3 dari decimal menjadi binary
		datainput_4[i] = decimalToBinary(datainput_4[i]); //merubah datainput_4 dari decimal menjadi binary
		datainput_5[i] = decimalToBinary(datainput_5[i]); //merubah datainput_5 dari decimal menjadi binary
	}
	
	for(int i=1;i<number_data+1;i++){		//perulangan sebanyak number data+1
		dataBaca.Input1[i]=IntToStr(datainput_1[i]);//mengkonversi int ke string
		dataBaca.Input2[i]=IntToStr(datainput_2[i]);//mengkonversi int ke string
		dataBaca.Input3[i]=IntToStr(datainput_3[i]);//mengkonversi int ke string
		dataBaca.Input4[i]=IntToStr(datainput_4[i]);//mengkonversi int ke string
		dataBaca.Input5[i]=IntToStr(datainput_5[i]);//mengkonversi int ke string
	}
	
	
	dataBaca.ndata = number_data;    //Mengisi int dataBaca.ndata dengan numer data
	
	save_data_file("data_binary.txt",dataBaca);	//menyimpan data ke file baru
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;	//membebaskan memori
	free(dataBaca.Input2),dataBaca.Input2=NULL; //membebaskan memori
	free(dataBaca.Input3),dataBaca.Input3=NULL; //membebaskan memori
	free(dataBaca.Input4),dataBaca.Input4=NULL; //membebaskan memori
	free(dataBaca.Input5),dataBaca.Input5=NULL; //membebaskan memori
}
