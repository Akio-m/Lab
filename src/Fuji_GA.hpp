// Fuji_GA.hpp

// includeガードで多重includeを防止

#ifndef _INCLUDE_Fuji_GA
#define _INCLUDE_Fuji_GA

// 後でinclude_list.hにまとめる
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <random>
#include <vector>
#include <iterator>
#include <stdint.h>
#include <map>
#include <cmath>
#include <math.h>

#include "parameter.h"

using namespace std;

// Fuji_Para構造体の宣言
typedef struct{
  double F_min[ MORA_SIZE ]; // 基底の高さ : 開始前の0番目は含めない // 後でとる
  int tau[ MORA_SIZE ]; // 立ち上がり時間
  double fitness; // 適応度
}Fuji_Para;

// Fuji_GAクラスの宣言
class Fuji_GA{
public:
  Fuji_GA( const int frame_size, const int seed );
  ~Fuji_GA();

private:
  Fuji_Para param_gene[ GA_SIZE ]; // Fuji_Para構造体の配列
  map< int , Fuji_Para* > ga_list; // Fuji_Para構造体のソートと探索を簡単かつ高速にする
  int seed; // seed値を保存しておく

public:
  void calc_fitness( const int gene_num, const int frame_size, const double *target ); //評価値の計算を行う
  void selection(); //選択を起こす
  void crossover(); //交叉を起こす
  void mutation( const int frame_size ); //突然変異を起こす
  void show_gene(); //個体を見せる
  void show_fitness(); //評価値を見せる
  void sort_ga(); //個体値順にソートする

};

#endif //_INCLUDE_Fuji_GA