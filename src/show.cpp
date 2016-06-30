//show.cpp

#include "Fuji_GA.hpp"

using namespace std;

// 遺伝子の中身を表示する
void Fuji_GA::show_gene(){
  cout << "##### Show GA genes..." << endl;

  for( int i = 0; i < GA_SIZE; ++i ){
  
    for(int j = 0; j < MORA_SIZE; ++j){
      if( j == 0 ){
        cout << "F_min" << endl;
      }
      cout << ga_list[ i ]->F_min[ j ] << endl;
    }

    for(int j = 0; j < MORA_SIZE; ++j){
      if( j == 0 ){
        cout << "tau" << endl;
      }
      cout << ga_list[ i ]->tau[ j ] << endl;
    }

    cout << "ga[" << i << "].fitness = "<< ga_list[ i ]->fitness << endl;
  }

  cout << "End." << endl;
}

void Fuji_GA::show_fitness(){
  cout << "##### Show GA gene's fitnesses..." << endl;


}