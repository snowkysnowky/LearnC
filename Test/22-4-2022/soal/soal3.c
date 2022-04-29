#include "soal_common.c"		//menggunakan file soal_common.c

int main(int argc, char *argv[]){
	read_file("data.txt");		//Membaca file bernama data.txt
	printf("jumlah data = %d\n",number_data); //prtint number data
	
	get_data_from_rawdata();	//mengambil data dari file dan mengganti ',' dengan spasi
	dataInput dataBaca;			//membuat struct dengan nama dataBaca
	dataBaca.Input1 = calloc(9999,sizeof(char));	//alokasi memori 
	dataBaca.Input2 = calloc(9999,sizeof(char));	//alokasi memori
	dataBaca.Input3 = calloc(9999,sizeof(char));	//alokasi memori
	int count1=0;		//int untuk menampung angka genap
	int count2=0;		//int untuk menampung angka ganji
	for(int i=1;i<number_data+1;i++){	//perulangan sebanyak number data+1
		if(isGanjil(datainput_1[i])==0){	//jika modulus datainput 1==0 maka count1+1 
			count1++;						//dan mengisi dataBaca.Input1
			dataBaca.Input1[count1] = IntToStr(datainput_1[i]);
		}
		if(isGanjil(datainput_2[i])==0){	//jika modulus datainput 2==0 maka count1+1 
			count1++;						//dan mengisi dataBaca.Input1
			dataBaca.Input1[count1] = IntToStr(datainput_2[i]);
		}
		if(isGanjil(datainput_3[i])==0){	//jika modulus datainput 3==0 maka count1+1 
			count1++;						//dan mengisi dataBaca.Input1
			dataBaca.Input1[count1] = IntToStr(datainput_3[i]);
		}
		
		if(isGanjil(datainput_1[i])==1){	//jika modulus datainput 1==1 maka count2+1 
			count2++;						//dan mengisi dataBaca.Input2
			dataBaca.Input2[count2] = IntToStr(datainput_1[i]);
		}
		if(isGanjil(datainput_2[i])==1){	//jika modulus datainput 2==1 maka count2+1 
			count2++;						//dan mengisi dataBaca.Input2
			dataBaca.Input2[count2] = IntToStr(datainput_2[i]);
		}
		if(isGanjil(datainput_3[i])==1){	//jika modulus datainput 3==1 maka count2+1 
			count2++;						//dan mengisi dataBaca.Input2
			dataBaca.Input2[count2] = IntToStr(datainput_3[i]);
		}
	}
	
	dataBaca.ndata = (count1 > count2 ? count1 : count2); //Mengisi int dataBaca.ndata dengan count 1 
							//	jika count1 lebih besar dari count2 jika tidak maka diisi dengan count2
	
	for(int i=1;i<dataBaca.ndata+1;i++){
		if(dataBaca.Input1[i]==NULL){dataBaca.Input1[i]="";}//jika dataBaca.Input1 == NULL maka dataBaca.Input1 berisi ""
		if(dataBaca.Input2[i]==NULL){dataBaca.Input2[i]="";}//jika dataBaca.Input2 == NULL maka dataBaca.Input2 berisi ""
		dataBaca.Input3[i]="";			// mengganti dataBaca.Input3 dengan ""
	}
	
	save_data_file("data_copy3.txt",dataBaca); //menyimpan data ke file yang baru
	
	free(dataBaca.Input1),dataBaca.Input1=NULL;//membebaskan memori
	free(dataBaca.Input2),dataBaca.Input2=NULL;//membebaskan memori
	free(dataBaca.Input3),dataBaca.Input3=NULL;//membebaskan memori
}
