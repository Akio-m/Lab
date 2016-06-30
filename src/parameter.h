//parameter.h 

//音声に関するパラメータ
#define MORA_SIZE 10
#define BETA 20.0
#define BUFFER_TIME 10

//GAに関するパラメータ
#define GA_SIZE 500
#define ELITE_COPY 0.002 //ELITE_COPY * GA_SIZE must 1 !!
#define MUTE_RATE 0.4

//ランキング戦略の選択確率
#define RANK_1 0.4
#define RANK_2 0.3
#define RANK_3 0.2
#define RANK_4 0.07
#define RANK_5 0.03