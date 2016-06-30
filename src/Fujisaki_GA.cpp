// Fujisaki_GA.cpp

#include "parameter.h"
#include "Fuji_GA.hpp"

#include <iostream>
#include <fstream>

//#include "include_list.h"

using namespace std; // stdを先頭につける必要がなくなる

int main(int argc, char const *argv[]){

  int arg_size = 4;

  // 引数チェック
  if( argc != arg_size ){
    cout << "Usage : ./Fujisaki_GA.exe $seed_value $target_file " << endl;
    exit(1);
  }

  // 引数読み込み
  int seed = stoi( argv[1] );
  int trial_times = stoi( argv[2] );
  ifstream reading_file( argv[3] );

  // ファイル読み込みチェック
  if( reading_file.fail() ){
    cout << "Target file Open failer." << endl;
    exit(1);
  }

  // ファイル読み込み開始
  // frame数読み込み
  string str;
  int frame_size = 0;
  getline( reading_file, str );
  frame_size = stoi( str );

  // target読み込み
  double target[ frame_size ]; // targetは0 ~ frame_size-1まで
  for (int i = 0; i < frame_size; ++i){
    getline( reading_file, str );
    target[ i ] = stod( str );
  }

  // GA開始
  // Fuji_GAオブジェクト生成
  Fuji_GA *ga;
  ga = new Fuji_GA( frame_size, seed );

  //誤差計算
  for( int i = 0; i < GA_SIZE; ++i){
    ga->calc_fitness( i, frame_size, target );
  }
  for (int k = 0; k < trial_times; ++k){
    ga->selection();
    ga->crossover();
    ga->mutation( frame_size );

    for( int i = 0; i < GA_SIZE; ++i){
      ga->calc_fitness( i, frame_size, target );
    }
    ga->sort_ga();
  }
  ga->show_gene();

  delete ga;

  return 0;
}