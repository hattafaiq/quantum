#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <locale>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;
int total_pegawai=4;
vector<int> jumlah_kerja_pegawai[4];
string hari[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"} ;
int jumlah_orang_per_weekday = 2;
int total_orang_weekday=jumlah_orang_per_weekday*5;

int jumlah_orang_per_weekend = 3;
int total_orang_weekend=jumlah_orang_per_weekend*2;

vector<string> splitStringByDelimiters(string& inputString,string& delimiters) { 
	vector<string> result; // Vector to store the split substrings 
	int startPos = 0; 
	int endPos = 0; 

	// Loop until endPos is not equal to string::npos 
	while ((endPos = inputString.find_first_of(delimiters, 
											startPos)) 
		!= string::npos) { 

		if (endPos != startPos) { // Checking if the 
								// substring is non-empty 
			result.push_back(inputString.substr( 
				startPos, endPos - startPos)); 
		} 

		startPos 
			= endPos + 1; // Update startPos to the position 
						// after the delimiter 
	} 

	if (startPos != inputString.length()) { 
		result.push_back(inputString.substr(startPos)); 
	} 
	return result; 
} 

int cari_kuota_seimbang_weekday(int last, int jumlah_pegawai){
    int flag=0;
        if(jumlah_kerja_pegawai[last].size()>=4){
            flag=1;
            }
    return flag;
}
int cari_kuota_seimbang_weekend(int last, int jumlah_pegawai){
    int flag=0;
        if(jumlah_kerja_pegawai[last].size()>=5){
            flag=1;
            }
    return flag;
}

int cek_dayoff(int last, int index_day, vector<string> list_dayoff){
    int flag=0;
        string delimiterss = ","; 
        vector<string> dayoff 
        = splitStringByDelimiters(list_dayoff[last], delimiterss);
        for (const auto& subs : dayoff) { 
            if(hari[index_day]==subs){
                flag=1;
                return 1;
            }
            else{
                flag=0;
                return 0;
            }
            //reload hari kalau misalkan kondisi fault
    }
    return flag;
}

int hari_we(int last, int index_day, vector<string> list_dayoff){
    int flag=0;
        string delimiterss = ","; 
        vector<string> dayoff 
        = splitStringByDelimiters(list_dayoff[last], delimiterss);
        for (const auto& subs : dayoff) { 
            if(hari[index_day]==subs){
                flag=1;
                return 1;
            }
            else{
                flag=0;
                return 0;
            }
            //reload hari kalau misalkan kondisi fault
    }
    return flag;
}

int cek_dayoff_we(int last,int last_last, int index_day, vector<string> list_dayoff){
    int flag=0;
    int flag_1=hari_we(last, index_day, list_dayoff);
    int flag_2=hari_we(last_last, index_day, list_dayoff);
    if((flag_1+flag_2)!=0){
        flag=1;
    }       
    return flag;
}

int cari_orang_weekend(int last,int last_end, int jumlah_pegawai, vector<string> list_dayoff,int index_day){
    int RandIndex = rand() % jumlah_pegawai;
    int flag_putar=1;
    int last_rand=0;
    while(flag_putar){
        if(last!=RandIndex && last_end!=RandIndex){ 
            last_rand=RandIndex;
            flag_putar=cek_dayoff_we(last_rand, last_end, index_day,list_dayoff);
            if(!flag_putar)jumlah_kerja_pegawai[last_rand].push_back(index_day);
        }
        RandIndex = rand() % jumlah_pegawai;
    }

    return last_rand;
}
int last_pilih;
int cari_orang_weekday(int last, int jumlah_pegawai, vector<string> list_dayoff,int index_day){
    int RandIndex = rand() % jumlah_pegawai;
    int flag_putar=1;
    int last_rand=0;
    while(flag_putar){
        if(last!=RandIndex){ 
            last_rand=RandIndex;
            flag_putar=cek_dayoff(last_rand, index_day,list_dayoff);
            if(!flag_putar)jumlah_kerja_pegawai[last_rand].push_back(index_day);
        }
        RandIndex = rand() % jumlah_pegawai;
    }

    return last_rand;
}

int sort_day(vector<string> dayoff, vector<string> nama){
   int day;
   //cout <<"\n ****ceri weekday***"<< last_pilih<<endl;
   int urut_hari=0;
   for(int i=0; i<total_orang_weekday; i++){//week day
        last_pilih = cari_orang_weekday(last_pilih,nama.size(),dayoff,urut_hari);
        //if(i%2==0)//cout <<"WD:"<<hari[urut_hari]<<"-"<<"shif1:"<< nama[last_pilih] << endl;
        if(i%2==1){
            //cout <<"WD:"<<hari[urut_hari]<<"-"<<"shif2:"<< nama[last_pilih] << endl;
            urut_hari+=1;
            } 
        
   }
   //cout <<"\n ***ceri weekend***"<<endl;
   int last_last=0;

   for(int i=0; i<total_orang_weekend; i++){//weekend
        if(i==2 || i==5){//ini artinya orang ke 3 di weekend
            last_pilih = cari_orang_weekend(last_pilih,last_last,nama.size(),dayoff,urut_hari);
            //cout <<"WEND:"<<hari[urut_hari]<<"-"<<"shif3:"<<nama[last_pilih]<<endl;
            urut_hari+=1;
        }
        else if(i==1 || i==4){//ini artinya orang ke 2 di weekend
            last_last = last_pilih;
            last_pilih = cari_orang_weekday(last_pilih,nama.size(),dayoff,urut_hari);
            //cout <<"WEND:"<<hari[urut_hari]<<"-"<< "shif2:"<<nama[last_pilih]<<endl;
        }
        else{
            last_pilih = cari_orang_weekday(last_pilih,nama.size(),dayoff,urut_hari); //ini artinya orang ke 1 di weekend 
            //cout <<"WEND:"<<hari[urut_hari]<<"-" << "shif1:"<<nama[last_pilih] << endl;
            }

   }

    cout << "\n ***list daily masuk pegawai by name***"<<endl;
   for(int i=0; i<total_pegawai; i++){
        cout << "pegawai:" <<nama[i] << "=";
        for(int k=0; k<jumlah_kerja_pegawai[i].size(); k++){
            cout <<hari[jumlah_kerja_pegawai[i][k]];
            if(k<(jumlah_kerja_pegawai[i].size()-1))cout<<",";
            else cout <<"\n";
        } 
   }

   cout << "\n ***list daily masuk pegawai by day***"<<endl;
    for(int i=0; i<7; i++){
        cout << hari[i] <<"=";
        for(int s=0; s<4; s++){
            for(int k=0; k<jumlah_kerja_pegawai[s].size(); k++){
                if(i==jumlah_kerja_pegawai[s][k])cout << nama[s]<<",";
            }
        }
        cout << "\n";

    }

    cout << "\n ***info jumlah pegawai masuk per minggu***"<<endl;
    for(int i=0; i<total_pegawai; i++){
        cout << "pegawai:" <<nama[i]<< " masuk:"<<jumlah_kerja_pegawai[i].size() << endl;
        if(jumlah_kerja_pegawai[i].size()>5){
            cout << " ada pegawai " <<nama[i]<< " masuk terlalu banyak \n";
        } 
   }
   //cout << "jumlah pegawai:" <<jumlah_kerja_pegawai.size() << endl;
   return day;
}



int main(){
    srand ( time(NULL) ); //initialize the random seed

   string filename = "WorkerData.txt";
    vector<string> nama_pegawai;
    vector<string> dayoff_pegawai;

   ifstream getfile;
   getfile.open(filename);
   if(!getfile.is_open()) return 1;
   string T;
   std::vector<std::string> tampung;
   std::vector<std::string>::iterator it;
   it = tampung.begin();
   int count=1;
   while(getfile){
      while(getline(getfile, T)){
        tampung.push_back(T);
      }
    }

   for (it=tampung.begin(); it<tampung.end(); it++){
    std::cout << ' ' << *it;
    std::cout << '\n';
   }

   for (int i=0; i<tampung.size(); i++){
        string delimiters = ":"; 
        vector<string> substrings 
		= splitStringByDelimiters(tampung[i], delimiters);
        // Displaying the string after splitiing 
        int count=0;
        for (const auto& substring : substrings) {
            if(!count){
                nama_pegawai.push_back(substring);
                //cout << substring << "=" << endl; //nama pekerja
                }
            else{
                dayoff_pegawai.push_back(substring); //hari off kerja raw
                // string delimiterss = ","; 
                // vector<string> dayoff 
		        // = splitStringByDelimiters(substrings[count], delimiterss);
                // for (const auto& subs : dayoff) { 
                //      //cout << subs << endl;  //hari off kerja
                //    } 
            }
            count+=1;            
        } 
    }

    
    sort_day(dayoff_pegawai, nama_pegawai);
    
   getfile.close(); 

    //syarat 
    //tiap weekday 2 orang pekerja dan tiap weekend 3 orang pekerja
    //minimal 2x libur dalam 1 minggu
    //sort by name untuk pekerjaan mingguan
    //sort by day untuk pekerjaan mingguan
    //menentukan jadwal tiap minggu menggunakan random pekerja sehingga berbeda beda tiap minggu
}
