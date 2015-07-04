#ifndef PARAMETER_H_
#define PARAMETER_H_

static const int RANDOM_MAX = 100;
static const int LOOP_COUNT = 10;
static const double RANKING_RATE = 0.2;
static const int CLUSTER_NUM = 10;
static const int CLUST_PARAM_NUM = RANDOM_MAX / CLUSTER_NUM;
static const double INDIVIDUALS_NUMBER = CLUST_PARAM_NUM * RANKING_RATE;
static const double MUTATION_RATE = 0.01;
static const int MUTATION_POS = 6;
static const int PARAMETER_NUM = 3;
static const int SLEEP_TIME = 10;
static const int ZERO_POINT = 225;
#endif