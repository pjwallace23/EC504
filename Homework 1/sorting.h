/*
EC 504 Advanced Algorithms and Data Structures Spring 20201 - Professor Castanon
Software Homework1
Peter Wallace
Produced in collaboration with Jean Marc Achkar jmachkar@bu.edu
*/

#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <iostream>

using namespace std;

static int swapCount = 0;

void swap(int* a, int* b)
{
    //swapCount++;
    int temp;
    temp = *a; 
    *a = *b; 
    *b = temp; 
}


/* See Knuth's shuffles https://en.wikipedia.org/wiki/Random_permutation */



void insertionsort(int a[],  int n)
{ 
    for (int i = 0; i < n; i++)
    {
      int j = i;
      int temp = a[i];
      while ((temp < a[j-1]) && (j>0))
      {
        a[j] = a[j-1];
        j--;
      }
      a[j] = temp;
    }
} 

// Order Theta(NlogN) sorting
void mergeSort(int a[], int a_tmp[], int l, int r)
{
    // you program this.  a_tmp can be used for merging 
    int n = r-l + 1;
    int le[(int)ceil(n/2.0)], ri[(int)floor(n/2.0)];
    l = 0;
    int sl = sizeof(le)/sizeof(le[0]); 
    int sr = sizeof(ri)/sizeof(ri[0]);
    copy(a,a+sl,le);
    copy(a+sl,a+n,ri);
    //cout<<sl<<" "<<sr<<endl;

    if (sl > 1)
        mergeSort(le, a, l, sl-1);

    if (sr > 1)
        mergeSort(ri, a, l, sr-1);
    
    int i = 0; int j = 0; int k = 0;

    while (i < sl && j < sr)
    {
        if (le[i] < ri[j])
        {
            a[k] = le[i];
            k++;
            i++;
        }
        else if(le[i] > ri[j])
        {
            a[k] = ri[j];
            k++;
            j++;
        }
        else
        {
            a[k] = le[i];
            k++;
            i++;
            a[k] = ri[j];
            k++;
            j++;
        }
    }
    
    while (i < sl)
    {
        a[k] = le[i];
        k++;
        i++;
    }
    while (j < sr)
    {
        a[k] = ri[j];
        k++;
        j++;
    }
  return;
}

void mergeSortblend(int a[], int a_tmp[], int l, int r)
{
 // You program this
    int n = r-l + 1;

    if (n < 32)
    {
        for (int i = 0; i < n; i++)
        {
            int j = i;
            int temp = a[i];
            while(temp < a[j-1] && j > 0)
            {
                a[j] = a[j-1];
                j--;
            }
            a[j] = temp;
            
        }
        return;
    }

    int le[(int)ceil(n/2.0)], ri[(int)floor(n/2.0)];
    l = 0;
    int sl = sizeof(le)/sizeof(le[0]); 
    int sr = sizeof(ri)/sizeof(ri[0]);
    copy(a,a+sl,le);
    copy(a+sl,a+n,ri);
   
    if (sl > 1)
        mergeSort(le, a, l, sl-1);

    if (sr > 1)
        mergeSort(ri, a, l, sr-1);
    
    int i = 0; int j = 0; int k = 0;

    while (i < sl && j < sr)
    {
        if (le[i] < ri[j])
        {
            a[k] = le[i];
            k++;
            i++;
        }
        else if(le[i] > ri[j])
        {
            a[k] = ri[j];
            k++;
            j++;
        }
        else
        {
            a[k] = le[i];
            k++;
            i++;
            a[k] = ri[j];
            k++;
            j++;
        }
    }
    
    while (i < sl)
    {
        a[k] = le[i];
        k++;
        i++;
    }
    while (j < sr)
    {
        a[k] = ri[j];
        k++;
        j++;
    }

return;
}

void checkInorder(int a[],int left, int right){
  //checks  that a is in order from left to right
  for (int i = left;i <right; i++){
    if (a[i] > a[i+1]){
      int tmp = i;
    }
  }
}

void simpleTimsort(int a[], int a_tmp[], int n)
{ 
   //You program this
    int minrunsize = 32;
    int num_in_stack = 0;
    int runstack[5000];
    runstack[0] = 0;
    int run[n];
    int c = 1;

   // find a run of at least size 32 starting from a[0]
   for (int i = 0; i < n; i++)
   {
     if (i == 0)
        {
            run[i] = a[i];
            c++;
        }
      else
      { 
        if (a[i] >= run[i-1])
        {
          run[i] = a[i];
          c++;
        }
        else
        {
          if (c < minrunsize)
          {
            int j = i;
            int temp = a[i];
            while ((temp < run[i-1]) && (j >= runstack[num_in_stack]))
            {
              run[j] = temp;
              j--;
            }
            run[j] = temp;
            c++;
          }
          else 
          {
            c = 1;
            num_in_stack++;
            runstack[num_in_stack] = i;
            run[i] = a[i];
          }
        }
      }
      if (i == n-1)
      {
        num_in_stack++;
        runstack[num_in_stack] = n;
      }
   }

   while (num_in_stack > 1)
   {
      int i = runstack[num_in_stack-2];
      int j = runstack[num_in_stack - 1];
      int k = i;
      int v = i;
      int l = j;
      while ((i < l) && (j < n))
      {
          if (run[i] <= run[j])
            {
              a_tmp[k] = run[i];
              k++;
              i++; 
            }
          else
            {
              a_tmp[k] = run[j];
              k++;
              j++;
            }
      }

      while (i < l)
        {
            a_tmp[k] = run[i];
            k++;
            i++;
        }
        while (j < n)
        {
            a_tmp[k] = run[j];
            k++;
            j++;
        }

        num_in_stack--;
        runstack[num_in_stack] = n;

        copy(run, run+v, run);
        copy(a_tmp+v, a_tmp +n,run+v);
   }
   copy(a_tmp,a_tmp+n,a);
  
}// end function





#endif 
