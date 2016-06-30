// calc_fitness.cpp

#include "Fuji_GA.hpp"

using namespace std;

void Fuji_GA::calc_fitness( const int gene_num, const int frame_size, const double *target ){
  //cout << "##### GA is calclating gene fitness... " << endl;

  double F_min[ MORA_SIZE + 1 ]; // F_minを格納する
  double tau[ MORA_SIZE + 1]; // tauを格納しておく

  F_min[ 0 ] = 0.0; // F_min固定
  tau[ 0 ] = 7; // tau固定

  // ga_listに影響がないようにコピーしておく
  for(int i = 0; i < MORA_SIZE; ++i){
    F_min[ i + 1 ] = ga_list[ gene_num ]->F_min[ i ];
    tau[ i + 1 ] = ga_list[ gene_num ]->tau[ i ] + 10;
  }

  double F_diff[ MORA_SIZE ]; // F_min差を格納しておく

  for(int i = 0; i < MORA_SIZE; ++i){
    F_diff[ i ] = F_min[ i + 1 ] - F_min[ i ];
  }

  double accumuler = 0.0;
  double temp_time = 0.0;
  double temp = 0.0;
  double unit_step = 0.0;
  double F_result[ frame_size + 10 ];
  double result = 0.0;

  for(int s = 1; s < frame_size + 10; ++s){
    
    accumuler = 0.0;
    for(int i = 0; i < MORA_SIZE; ++i){
    
      temp_time = ( s - tau[ i ] ) / 100.0;

      temp = 1 - ( 1 + BETA * temp_time ) * exp( -1 * BETA * temp_time );

      if( temp_time >= 0.0 ){
        unit_step = 1.0;
      }else{
        unit_step = 0.0;
      }

      accumuler += F_diff[ i ] * temp * unit_step;
    }

    F_result[ s ] = F_min[ 0 ] + accumuler;
  }

  for(int s = 11; s < frame_size + 10; ++s){
    result += fabs( target[ s - 11 ] - F_result[ s ] );
  }
  ga_list[ gene_num ]->fitness = result;

}