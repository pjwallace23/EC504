/*
EC504 Spring 2021 Professor Castanon
Peter Wallace
Software Homework 2
Produced in collaboration with Jean Marc Achkar
*/


#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include <math.h>

using namespace std;

const int MAX_SIZE = 100000; //the maximum amount of elements our heap should have.

template <typename Object>
class Heap
{
public:
   Heap(){
      elements = 0;
   };
   void insert(Object* item){// Add the object pointer item to the heap
	   if (elements >= MAX_SIZE){
		   cout << "Heap is full; can't insert "<< endl;
      }
      // FILL IN THE REST
      else
      {
         item->position = elements;
         array[elements] = item;
         upHeap(item->position);
         elements++;
      }
			return;

   };  	
   Object* remove_min(){
      if (elements ==0){
		   cout << "empty heap error, can't delete"<<endl;
	   }
      Object* temp = array[0];
      array[0]->position = -1;
      // FILL IN THE REST
      array[elements - 1]->position = 0; // swap last inserted element into root
      array[0] = array[elements - 1];
      elements--; // decrease elements
      downHeap(array[0]->position); // downheap root to maintain min heap property
      return temp;
   };       // Remove the smallest element in the heap & restructure heap

   
   void decreaseKey(int pos, int val)// Decreases Key in pos to val
   {
         // FILL IN THE REST
         array[pos]->key = val;
         upHeap(pos);
         return;
   }; 
   

   bool IsEmpty() const {  return (elements <= 0);};
   bool IsFull() const {return (elements >=MAX_SIZE );};
   int count() const {return elements;};
   Object* value(int pos) const{ //return a pointer to an object in heap position
	   if (pos >= elements){
		   cout << "Out of range of heap " << pos << "elements " << elements << endl;
	   }
      return (array[pos]);
   };  
protected:
   Object* array[MAX_SIZE];
   int elements;       //  how many elements are in the heap
private:
   void downHeap(int pos){// starting with element in position pos, sift it down the heap 
                       // until it is in final min-heap position
      // FILL THIS IN
      Object* item = array[pos];
      int p = pos;
      bool l;

      // FILL THIS IN
      while (p<=elements/2 -1)
      {
         if(array[2*p+1]->key <= array[2*p+2]->key)      //Check if left child smaller than right child or not
            l = true;
         else
            l = false;

         if (l && array[p]->key > array[2*p+1]->key)
         {
            item = array[p];
            array[p] = array[2*p+1];
            array[2*p+1] = item;
            array[p]->position = p;
            array[2*p+1]->position = 2*p+1;
            p = 2*p+1;
            //cout<<"left"<<endl;
         }
         else if (!l && array[p]->key > array[2*p+2]->key)
         {
            item = array[p];
            array[p] = array[2*p+2];
            array[2*p+2] = item;
            array[p]->position = p;
            array[2*p+2]->position = 2*p+2;
            p = 2*p+2;
            //cout<<"right"<<endl;
         }
         else
         {
            //cout<<"done"<<endl;
            break;
         }
         //cout<<"stuck"<<endl;
      }
      return;
         

   }; 

   void upHeap(int new_pos){// starting with element in position int, sift it up the heap
                       // until it is in final min-heap position
     Object* item = array[new_pos];
      int p = new_pos;

      while (p != 0)
      {
         if (array[p]->key < array[(p-1)/2]->key)
         {
            item = array[p];
            array[p] = array[(p-1)/2];
            array[(p-1)/2] = item;
            array[p]->position = p;
            array[(p-1)/2]->position = (p-1)/2;
            p = (p-1)/2;
         }
         else
            break;  
      }
      return;
   };   
};
#endif
