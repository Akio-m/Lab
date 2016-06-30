// crossover.cpp

#include "Fuji_GA.hpp"

using namespace std;

void Fuji_GA::crossover(){
  //cout << "##### GA is doing crossover... " << endl;  

  // 交叉位置決定
  double temp_1 = 0.0;
  double temp_2 = 0.0;
  int temp_1_tau = 0;
  int temp_2_tau = 0;
  int list_temp = 0;
  double value_temp = 0.0;
  int value_temp_tau = 0;

  // 乱数オブジェクト生成
  mt19937_64 engine( seed ); // MT法による乱数生成
  uniform_int_distribution< int > int_Distribution( 0, (MORA_SIZE - 1) );

  for (int i = 1; i < GA_SIZE; ++i){

    // F_min交叉位置決定
    list_temp = int_Distribution( engine );
    temp_1 = ga_list[ i - 1 ]->F_min[ list_temp ]; // if 5.4
    temp_2 = ga_list[ i ]->F_min[ list_temp ]; // if 9.0

    // F_min値決定
    uniform_real_distribution< double > real_Distribution( temp_1, temp_2 ); // 5.4 ~ 9.0の間で乱数マスク 
    value_temp = real_Distribution( engine );
    ga_list[ i ]->F_min[ list_temp ] = value_temp;

    // tau交叉位置決定
    list_temp = int_Distribution( engine );
    temp_1_tau = ga_list[ i - 1 ]->tau[ list_temp ]; // if 34 or 59
    temp_2_tau = ga_list[ i ]->tau[ list_temp ]; // if 59 or 32
    
    //tau値決定
    //uniform_int_distributionオブジェクトは引数の大小を見ない。
    if( temp_1_tau <= temp_2_tau){
      uniform_int_distribution< int > int_Distribution_2( temp_1_tau, temp_2_tau ); // 34 ~ 59の間で乱数マスク
      value_temp_tau = int_Distribution_2( engine );
    }else{ // 59と32のとき、uniform_int_distributionが誤作動しないようにするため
      // 6/30 ここは順序関係まで正せてるか微妙。エラー時に要検討
      uniform_int_distribution< int > int_Distribution_2( temp_2_tau, temp_1_tau ); // 32 ~ 59の間で乱数マスク
      value_temp_tau = int_Distribution_2( engine );
    }
    
    ga_list[ i ]->tau[ list_temp ] = value_temp_tau;
  } 

}