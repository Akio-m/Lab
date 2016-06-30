// selection.cpp

#include "Fuji_GA.hpp"

using namespace std;

void Fuji_GA::selection(){
  //cout << "##### GA is doing selection... " << endl;

  // ga_listを適応度昇順にsortしておく
  sort_ga();

  // ga_listのコピーを作って、直接影響を与えないようにする
  Fuji_Para param_temp[ GA_SIZE ]; // ga_listのコピー 
  vector< pair< double, int > > temp;

  for( int i = 0; i < GA_SIZE; ++i ){
    for (int j = 0; j < MORA_SIZE; ++j){
      param_temp[ i ].F_min[ j ] = ga_list[ i ]->F_min[ j ];
      param_temp[ i ].tau[ j ] = ga_list[ i ]->tau[ j ];
      param_temp[ i ].fitness = ga_list[ i ]->fitness;
    }
    temp.push_back( pair< double, int > ( ga_list[ i ]->fitness, i ) );
  }

  // エリート戦略
  int elite_num = ( int )( GA_SIZE * ELITE_COPY ); // エリート数を決める
  int capacity = elite_num; 
  for( int i = 0; i < elite_num; ++i ){
    for (int j = 0; j < MORA_SIZE; ++j){
      param_temp[ i ].F_min[ j ] = ga_list[ temp[ i ].second ]->F_min[ j ];
      param_temp[ i ].tau[ j ] = ga_list[ temp[ i ].second ]->tau[ j ];
      param_temp[ i ].fitness = ga_list[ temp[ i ].second ]->fitness;
    }
  }

  //ランク戦略 
  mt19937_64 engine( seed );
  uniform_real_distribution< double > real_Distribution( 0.0, 1.0 );

  for (int i = capacity; i < GA_SIZE; ++i){
    double dice = real_Distribution( engine );
    if( dice <= RANK_1 ){
      
      for (int j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 0 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 0 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 0 ].second ]->fitness;
      ++capacity;

    }else if( dice <= RANK_1 + RANK_2 ){

      for (int j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 1 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 1 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 1 ].second ]->fitness;
      ++capacity;

    }else if( dice <= RANK_1 + RANK_2 + RANK_3 ){

      for (int j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 2 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 3 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 3 ].second ]->fitness;
      ++capacity;
    
    }else if( dice <= RANK_1 + RANK_2 + RANK_3 + RANK_4 ){

      for (int j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 4 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 4 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 4 ].second ]->fitness;
      ++capacity;

    }else{
    
      for (int j = 0; j < MORA_SIZE; ++j){
        param_temp[ i ].F_min[ j ] = ga_list[ temp[ 5 ].second ]->F_min[ j ];
        param_temp[ i ].tau[ j ] = ga_list[ temp[ 5 ].second ]->tau[ j ];
      }
      param_temp[ i ].fitness = ga_list[ temp[ 5 ].second ]->fitness;
      ++capacity;
    }
  }

  //ga_listに変更を書き込む
  for(int i = 0; i < GA_SIZE; ++i){
    for (int j = 0; j < MORA_SIZE; ++j){
      ga_list[ i ]->F_min[ j ] = param_temp[ i ].F_min[ j ];
      ga_list[ i ]->tau[ j ] = param_temp[ i ].tau[ j ];
    }
    ga_list[ i ]->fitness = param_temp[ i ].fitness;
  }

}