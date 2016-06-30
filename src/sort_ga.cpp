// sort_ga.cpp

#include "Fuji_GA.hpp"

using namespace std;

void Fuji_GA::sort_ga(){
  //cout << "##### GA is sorting... " << endl;

  // vectorにFuji_Para構造体を借り置きして、sortしやすくする
  Fuji_Para param_temp[ GA_SIZE ]; // ga_listのコピー
  vector< pair< double, int > > temp;

  for( int i = 0; i < GA_SIZE; ++i ){
    for (int j = 0; j < MORA_SIZE; ++j){
      param_temp[ i ].F_min[ j ] = ga_list[ i ]->F_min[ j ];
      param_temp[ i ].tau[ j ] = ga_list[ i ]->tau[ j ];
      param_temp[ i ].fitness = ga_list[ i ]->fitness;
    }
    // pairで個体適応度と構造体番号を入れるから、sortしたあとでも呼び出せる
    temp.push_back( pair< double, int > ( ga_list[ i ]->fitness, i ) ); // 個体適応度, 構造体番号 
  }

  // tempをソート
  sort( temp.begin(), temp.end() );

  //ga_listに変更を書き込む
  for(int i = 0; i < GA_SIZE; ++i){
    for (int j = 0; j < MORA_SIZE; ++j){
      ga_list[ i ]->F_min[ j ] = param_temp[ temp[ i ].second ].F_min[ j ];
      ga_list[ i ]->tau[ j ] = param_temp[ temp[ i ].second ].tau[ j ];
    }
    ga_list[ i ]->fitness = param_temp[ temp[ i ].second ].fitness;
  }
  
}