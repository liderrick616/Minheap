/*
 * Our MinHeap implementation.
 *
 * Author (starter code): Akshay Arun Bapat.
 * Based on implementation from A. Tafliovich and F. Estrada
 */

#include "minheap.h"
//#include <time.h>
/*************************************************************************
 ** Suggested helper functions -- part of starter code
 *************************************************************************/

/*
 * Swaps contents of heap->arr[index1] and heap->arr[index2] if both
 * 'index1' and 'index2' are valid indices for minheap 'heap'.
 * Has no effect otherwise.
 */
void swap(MinHeap* heap, int index1, int index2){
    // Check for valid indices
    if (index1 >= 1 && index1 <= heap->size &&
        index2 >= 1 && index2 <= heap->size) {
        // Swap the nodes at index1 and index2
        HeapNode temp = heap->arr[index1];
        heap->arr[index1] = heap->arr[index2];
        heap->arr[index2] = temp;
    }
    // do nothing if both index invalid
}
/*
 * Returns the index of the parent of a node at index 'nodeIndex',
 * assuming it exists.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
int getParentIdx(int nodeIndex){
    return (nodeIndex / 2);
    //Returns the index of the parent node for a given node index in a heap
}
/*
 * Floats up the element at index 'nodeIndex' in minheap 'heap' such that
 * 'heap' is still a minheap.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
void floatUp(MinHeap* heap, int nodeIndex){
    while (nodeIndex > 0 && nodeIndex<= heap->size) {
        int parentIndex = getParentIdx(nodeIndex);
        // Compare current node's priority and parent's priority
        if (heap->arr[nodeIndex].priority < heap->arr[parentIndex].priority) {
            // Swap current node with parent
            swap(heap, nodeIndex, parentIndex);
            // Update nodeIndex to parent index
            nodeIndex = parentIndex;
        } else {
            // current node's priority is not smaller, break
            break;
        }
    }
}
/*
 * Returns the index of the left child of a node at index 'nodeIndex',
 * assuming it exists.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
int getLeftChildIdx(int nodeIndex){
    return 2 * nodeIndex;
}
/*
 * Returns the index of the right child of a node at index 'nodeIndex',
 * assuming it exists.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
int getRightChildIdx(int nodeIndex){
    return 2 * nodeIndex + 1;
}

/*
 * Returns True if 'nodeIndex' is currently a valid index in minheap 'heap'.
 * False otherwise.
 */
bool isValidIndex(MinHeap* heap, int nodeIndex){
    return (nodeIndex > 0 && nodeIndex <= heap->size);
}

/*
 * Returns priority of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 *               'heap' is non-empty
 */
int priorityAt(MinHeap* heap, int nodeIndex){
        return heap->arr[nodeIndex].priority;
    // Returns the priority of the node at nodeIndex
}

/*********************************************************************
 * Required functions
 ********************************************************************/
//Returns the minimum element in the heap
HeapNode getMin(MinHeap* heap)
{
    return heap->arr[1];
    // root is minimum in a minheap
}
//Restores minheap property from nodeIndex,
// adjusting heap downward.
void heapify(MinHeap* heap, int nodeIndex)
{
    int leftChildIndex = getLeftChildIdx(nodeIndex);
    int rightChildIndex = getRightChildIdx(nodeIndex);
    int smallest = nodeIndex;
    // Find the smallest among nodeIndex, left child and right child
    if (leftChildIndex <= heap->size &&
        heap->arr[leftChildIndex].priority < heap->arr[smallest].priority) {
        smallest = leftChildIndex;
    }
    if (rightChildIndex <= heap->size &&
        heap->arr[rightChildIndex].priority < heap->arr[smallest].priority) {
        smallest = rightChildIndex;
    }
    //smallest not current node, swap, recursion
    if (smallest != nodeIndex) {
        swap(heap, nodeIndex, smallest);
        heapify(heap, smallest);
    }
}
//Removes, returns minimum element from heap
//restructures heap, maintain minheap property
HeapNode extractMin(MinHeap* heap)
{
    HeapNode minNode = heap->arr[1];  // root, minimum
    heap->arr[1] = heap->arr[heap->size];  // Replace with last element
    heap->size--;  // Reduce heap size
    heapify(heap, 1);  // Restore heap property using heapify
    return minNode;
}
//Inserts a new node with given priority and ID into the heap
bool insert(MinHeap* heap, int priority, int id)
{
    // check space in the heap
    if (heap->size >= heap->capacity) {
        return false;  // Heap is full
    }
    // New node with given priority, id
    HeapNode newNode;
    newNode.priority = priority;
    newNode.id = id;
    // new node at end of heap
    heap->size++;
    heap->arr[heap->size] = newNode;
    floatUp(heap, heap->size);
    return true;
}
//Change priority of node at nodeIndex, also maintain balance
void changePriority(MinHeap* heap, int nodeIndex, int newPriority)
{
    int currentPriority = heap->arr[nodeIndex].priority;
    heap->arr[nodeIndex].priority = newPriority;
    if (newPriority < currentPriority) {
        // new priority is lower, float the node up
        floatUp(heap, nodeIndex);
    } else {
        // new priority is higher, push the node down or heapify
        heapify(heap, nodeIndex);
    }
}
//Creates a new heap
MinHeap* newHeap(int capacity)
{
// Allocate memory for the heap structure
    MinHeap* heap = (MinHeap*) calloc(1,sizeof(MinHeap));
    if (!heap) {
        return NULL; // Memory allocation failed
    }
    // Set heap's initial size to 0
    heap->size = 0;
    heap->capacity = capacity;
    // Allocate memory of heap's array with specified capacity
    heap->arr = (HeapNode*) calloc(capacity, sizeof(HeapNode));
    return heap;
}
// Deallocates memory used by the heap
void deleteHeap(MinHeap* heap)
{
    if (heap) {
        // Free the array with heap's nodes
        if (heap->arr) {
            free(heap->arr);
        }
        // Free heap structure
        free(heap);
    }
}

/*********************************************************************
 ** Helper function provided in the starter code
 *********************************************************************/
void printHeap(MinHeap* heap)
{
  printf("MinHeap with size: %d\n\tcapacity: %d\n\n", heap->size,
         heap->capacity);
  printf("index: priority [ID]\n");
  for (int i = 1; i <= heap->size; i++)
    printf("%d: %d [%d]\n", i, heap->arr[i].priority, heap->arr[i].id);
  printf("\n\n");
}

/****************************************************
** Experiments and Analysis
****************************************************/

/*
 * Both the following functions build a heap from scratch based on the input
 * array of priorites for IDs '0' to 'size-1'.
 *
 * You can assume both implementations are correct.
 */

MinHeap* buildHeap_Sajad(int values[], int size)
{
  MinHeap* heap = newHeap(size);
  heap->size = size;

  for (int i=0; i<size; i++)
  {
    heap->arr[i+1].priority = values[i];
    heap->arr[i+1].id = i;
  }

  for (int i=size/2; i>=1; i--)
  {
    heapify(heap, i);
  }

  return heap;
}

MinHeap* buildHeap_Elaheh(int values[], int size)
{
  MinHeap* heap = newHeap(size);

  for (int i=0; i<size; i++)
  {
    if (!insert(heap, values[i], i))
      return NULL;
  }

  return heap;
}

