#ifndef GENERATE_H
#define GENERATE_H

#include <time.h>
#include <vector>

//RANDOM
int* getRandomArray(int n){
  srand(time(NULL));
	
  vector<int> v;
  int* r = (int*)malloc(sizeof(int)*n);
  for(int i =0; i < n; i++){
    v.push_back(i);	
  }
	
  for(int i =0; i < n; i++){
    int x = rand() % v.size();
    //cout << "i: " << i << " x: " << x << " Size: " << v.size() << " Element: " << v[x] << endl;
    r[i] = v[x];
    v.erase(v.begin()+x);
  }	
  
  cout << "done" <<endl;
  return r;
}

int* getSortedArray(int n){
  int* r = (int*)malloc(sizeof(int)*n);
  for(int i=0; i<n; i++)
    //r[i] = n - i;
    r[i] = i;
  return r;
};




#endif
