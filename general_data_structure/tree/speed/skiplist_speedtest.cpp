#include <ctime>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include "../skiplist.h"
using namespace std;


int main(int argc, char *argv[]){
  if(argc != 4){
    printf("usage: ./skiplistspeedtest size maxLevel P");
    exit(-1);
  }
  
  int sz = atoi(argv[1]);
  int maxLevel = atoi(argv[2]);
  double P = atof(argv[3]);
  clock_t start, end;

  vector<int> arr;

  for(int i = 0; i < sz; ++i){
    arr.push_back(i);
  }

  std::mt19937 rng;
  rng.seed(std::random_device()());
  shuffle(arr.begin(), arr.end(), rng);


  
  hollin::SkipList<int, int> list(maxLevel, P);
  
  // -------------INSERT-------------
  printf("test inserting...\n");
  start = clock();
  int level = 0;
  for(int i = 0; i < sz; ++i){
    assert(list.Insert(i, i) == true);
    int newLevel = list.Level();
    if(level != newLevel){
      printf("\tLevel expands from %d to %d\n", level, newLevel);
      level = newLevel;
    }
  }
  end = clock();
  printf("\tinserting %d elements using %.3lfs.\n\n", sz, (double)(end - start) / CLOCKS_PER_SEC);
  
  // -------------SEARCH-------------
  printf("test searching...\n");
  start = clock();
  for(int i = 0; i < sz; ++i){
    assert(list.Search(i) == i);
  }
  end = clock();
  printf("\tsearching %d elements using %.3lfs.\n\n", sz, (double)(end - start) / CLOCKS_PER_SEC);
  
  // -------------DELETE-------------
  printf("test deleting...\n");
  start = clock();
  for(int i = 0; i < sz; ++i){
    assert(list.Delete(i) == true);
    int newLevel = list.Level();
    if(level != newLevel){
      printf("\tLevel shrinks from %d to %d\n", level, newLevel);
      level = newLevel;
    }
  }
  end = clock();
  printf("\tdeleting %d elements using %.3lfs.\n\n", sz, (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}
