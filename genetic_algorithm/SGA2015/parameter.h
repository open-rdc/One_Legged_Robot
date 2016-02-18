#ifndef PARAMETER_H_
#define PARAMETER_H_

static const int RANDOM_MAX = 150;										//! 個体数
static const int LOOP_COUNT = 10;										//! 世代数
static const double RANKING_RATE = 0.2;									//! 次の世代に残す割合
static const double INDIVIDUALS_NUMBER = RANDOM_MAX * RANKING_RATE;		//! 次の世代に残す個体数
static const double MUTATION_RATE = 0.01;
static const int MUTATION_POS = 6;
static const int PARAMETER_NUM = 2;										//! パラメータの数 (the1, the2)
static const int SLEEP_TIME = 10;
static const int ZERO_POINT = 225;
#endif