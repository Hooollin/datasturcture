#include <ctime>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cassert>
#include <random>
#include <map>

using namespace std;


int main(int argc, char *argv[]){
  if(argc != 2){
    printf("usage: ./avlspeedtest size");
    exit(-1);
  }
  
  int sz = atoi(argv[1]);
  clock_t start, end;
  vector<int> arr;

  for(int i = 0; i < sz; ++i){
    arr.push_back(i);
  }

  std::mt19937 rng;
  rng.seed(std::random_device()());
  shuffle(arr.begin(), arr.end(), rng);

  map<int, int> mp;

  printf("test inserting...\n");
  start = clock();
  for(int i = 0; i < sz; ++i){
    mp[arr[i]] = i;
  }
  end = clock();
  printf("\tinserting %d elements using %.3lfs.\n\n", sz, (double)(end - start) / CLOCKS_PER_SEC);
  
  printf("test searching...\n");
  start = clock();
  for(int i = 0; i < sz; ++i){
    assert(mp[arr[i]] == i);
  }
  end = clock();
  printf("\tsearching %d elements using %.3lfs.\n\n", sz, (double)(end - start) / CLOCKS_PER_SEC);
  
  printf("test deleting...\n");
  start = clock();
  for(int i = 0; i < sz; ++i){
    mp.erase(arr[i]);
  }
  end = clock();
  printf("\tdeleting %d elements using %.3lfs.\n\n", sz, (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}
