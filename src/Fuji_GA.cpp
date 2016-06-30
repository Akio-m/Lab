// Fuji_GA.cpp

#include "Fuji_GA.hpp"

using namespace std;

// Fuji_GAコンストラクタ
Fuji_GA::Fuji_GA( const int frame_size, const int seed ){
  cout << "##### GA is initializing..." << endl;

  int search_range = frame_size / MORA_SIZE;

  Fuji_Para *param_gene_pointer = NULL; // メモリリーク阻止のためNULL

  for(int i = 0; i < GA_SIZE; ++i){

    // 乱数生成オブジェクト生成
    mt19937_64 engine( seed + i ); // 乱数を個体ごとに変更するためseed + i
    uniform_real_distribution< double > real_Distribution( -15.0, 15.0 );// 実数で-15.0 ~ 15.0まで
    uniform_int_distribution< int > int_Distribution( 1, search_range );// 整数で1 ~ 15まで

    // Fuji_Para構造体の初期化
    for(int j = 0; j < MORA_SIZE; ++j){

      // F_minの初期化
      param_gene[ i ].F_min[ j ] = real_Distribution( engine );
      
      // tauの初期化
      int temp = int_Distribution( engine ) + ( search_range * j ); // 1 ~ 7, 8 ~ 14, ...のように範囲選択 

      // tauの限界設定
      if( temp > frame_size ){
        // frame_sizeより小さくなるまで振りなおす
        while(temp > frame_size){
          temp = int_Distribution( engine ) + ( search_range * j ); // これうまくいくか？
        }

      }else{
        param_gene[ i ].tau[ j ] = temp;
      }
      //cout << "param_gene[ i ].tau[ j ] = " << param_gene[ i ].tau[ j ] << endl;
    }
    // fitnessの初期化
    param_gene[ i ].fitness = 0.0;

    // Fuji_GAオブジェクトでは関数で値変更をすることが多々あるため、アドレス渡しをする
    param_gene_pointer = &param_gene[ i ];
    // mapに初期化した構造体を渡す
    ga_list[ i ] = param_gene_pointer;
  }
}

// Fuji_GAのデコンストラクタ
Fuji_GA::~Fuji_GA(){
  cout << "##### Deleat GA ... bye!" << endl;
}