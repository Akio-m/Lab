//mutation.cpp

#include "Fuji_GA.hpp"

using namespace std;

void Fuji_GA::mutation( const int frame_size ){
  //cout << "##### GA is doing mutation... " << endl;

  double mute_num = 0.0;
  int temp_1 = 0;
  int search_range = ( frame_size - 1 ) / MORA_SIZE;

  // 乱数オブジェクト生成
  mt19937_64 engine( seed );
  uniform_real_distribution< double > real_Distribution_Fmin( 0.0, 1.0 );
  uniform_real_distribution< double > real_Distribution_Fmin_value( -15.0, 15.0 );
  uniform_real_distribution< double > real_Distribution_tau( 0.0, 1.0 );
  uniform_int_distribution< int > int_Distribution_tau_value( 1, 10 );

  for( int i = 1; i < GA_SIZE; ++i ){
    for( int j = 0; j < MORA_SIZE; ++j ){

      // 0.0 ~ 1.0までのサイコロを振る
      mute_num = real_Distribution_Fmin( engine );

      // MUTE_RATE以下なら突然変異
      if( mute_num <= MUTE_RATE ){
        ga_list[ i ]->F_min[ j ] = real_Distribution_Fmin_value( engine );
      }

      // 0.0 ~ 1.0までのサイコロを振る
      mute_num = real_Distribution_tau( engine );

      // MUTE_RATE以下なら突然変異
      if( mute_num <= MUTE_RATE ){

        // MORA_SIZE-1の時は例外処理 : 最後の数を超える可能性があるから
        if(j != (MORA_SIZE - 1)){

          temp_1 = int_Distribution_tau_value( engine ) + ( search_range * j );
          
          if(temp_1 > frame_size - 1){
            ga_list[ i ]->tau[ j ] = frame_size - 1; // ここ要検討
          }else{
            ga_list[ i ]->tau[ j ] = temp_1;
          }

        }else{ // 最大tau位置から1 ~ 10までの乱数を引いて調整
          temp_1 = ( frame_size - 1 ) - int_Distribution_tau_value( engine );
          ga_list[ i ]->tau[ j ] = temp_1;
        }

      }

    }
  }

}
