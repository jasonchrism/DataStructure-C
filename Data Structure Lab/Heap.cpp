#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//heap: binary tree, partially ordered
//maxheap: parentnya lebih besar daripada childnya
//minheap: parentnya lebih kecil daripada childnya

//define struct
struct Food{
	char foodName[100];
	int foodPrice;
};

struct Heap{
	Food *foods;
	int capacity; //MAXSIZE
	int lastIndex; //kalau punya data baru, masuk ke index berapa
}heap;

void initializeHeap()
{
	//arraynya, kapasitasnya, lastIndex
	heap = {NULL, 2, 1};
	//pesan tempat untuk arraynya
	//malloc sesuai kapasitas
	heap.foods = (Food*) malloc(sizeof(Food) *heap.capacity);
	return;
}

void resizeHeap()
{
	heap.capacity *= 2;
	heap.foods = (Food*)realloc(heap.foods, sizeof(Food) * heap.capacity);
	return; 
}

void swap(Food *a, Food *b)
{
	Food temp = *a;
	*a = *b;
	*b = temp;
	return;
}

//curr = index dari node yang sekarang lagi di cek 
void heapify(int curr, int size)
{
	//cari index anak kiri & anak kanan
	int left = 2 * curr;
	int right = left + 1;
	
	int largest = curr;
	
	//apakah ada anak kiri & anak kiri lebih besar?
	//kalau minheap tinggal diganti tanda > jadi <
	if(left < size && heap.foods[left].foodPrice > heap.foods[largest].foodPrice){
		largest = left;
	}
	
	//apakah ada anak kanan & anak kanan lebih besar?
	if(right < size && heap.foods[right].foodPrice > heap.foods[largest].foodPrice){
		largest = right;
	}
	
	//kalau largestnya bukan di curr
	if(largest != curr)
	{
		//swap
		swap(&heap.foods[largest], &heap.foods[curr]);
		//heapify (recursive ke bawah)
		heapify(largest, size);
	}
	return; //kalau largest tidak berubah, langsung return
}

void buildHeap()
{
	//looping semua data yang punya child (non-leaf)
	for(int i = heap.lastIndex/2; i >= 1; i--)
	{
		//heapify: proses memindahkan node heap ke posisi yang tepat
		heapify(i, heap.lastIndex);
	}
	
	return;
}

void insertFood(const char *foodName, int foodPrice)
{
	//cek apakah heapnya masih mudat
	if(heap.lastIndex == heap.capacity)
	{
		resizeHeap();
	}
	//masukin data dari parameter ke index yang sesuai
	strcpy(heap.foods[heap.lastIndex].foodName, foodName);
	heap.foods[heap.lastIndex].foodPrice = foodPrice;
	heap.lastIndex += 1;
	
	//cek dan atur apakah tree kita sudah sesuai aturan maxheap
	buildHeap();
	
	return;
}

int searchFood(int foodPrice)
{
	//linear search
	for(int idx = 1; idx < heap.lastIndex; idx++)
	{
		//kalau ketemu
		if(heap.foods[idx].foodPrice == foodPrice)
		{
			return idx;
		}
	}
	
	//kalau ga ketemu
	return -1;
}

void deleteFood(int foodPrice)
{
	//cari idx data yang mau dihapus
	int idx = searchFood(foodPrice);
	
	if(idx == -1)
	{
		return;
	}
	
	//swap dengan data terakhir (lastIndex-1)
	swap(&heap.foods[idx], &heap.foods[heap.lastIndex-1]);
	heap.lastIndex--;
	
	//cek & atur apakah tree kita sudah sesuai aturan maxheap
	buildHeap();
	
	return;
}

void heapSort()
{
	//pastiin dulu tree kita sudah berbentuk heap
	buildHeap();
	
	for(int i = heap.lastIndex-1; i > 1; i--)
	{
		//swap index pertama dengan terakhir
		swap(&heap.foods[1], &heap.foods[i]);
		heapify(1, i);
	}
	
	return;
}

void viewFoods()
{
	for(int i=1; i<heap.lastIndex; i++)
	{
		printf("%s %d\n", heap.foods[i].foodName, heap.foods[i].foodPrice);
	}
}

int main()
{
	initializeHeap();
	
	insertFood("Ayam", 30000);
	insertFood("Ayam", 28000);
	insertFood("Ayam", 37000);
	insertFood("Ayam", 42000);
	insertFood("Ayam", 76000);
	viewFoods();
	
	heapSort();
	printf("\n\nAfter HeapSort\n");
	viewFoods();
	
//	insertFood("Ayam", 36000);
//	printf("\n\nAfter 36000 inserted:\n");
//	viewFoods();
//	
//	deleteFood(36000);
//	printf("\n\nAfter 36000 deleted:\n");
//	viewFoods();
	
	return 0;
}
