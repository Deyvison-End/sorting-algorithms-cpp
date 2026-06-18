#ifndef ORDENACAO_H_AULA
#define ORDENACAO_H_AULA

#include <iostream>
#include <chrono>
#include <vector>

using namespace std;


template<class T>
void bubblesort(vector<T> &array) {
	
	T temp;
	for(int i = 0; i < array.size() - 1; i++)
	{
		for(int j = 0; j < array.size() - 1; j++)
		{
			if(array[j] > array[j + 1])
			{
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;
			}

		}
	}

}

template<class T>
void selectionsort(vector<T> &array) {

	T temp;
	for(int i = 0; i < array.size() - 1; i++)
	{
		int min = i;
		for(int j = i + 1; j < array.size(); j++)
		{
			if(array[min] > array[j])
			{
				min = j;
			}

		}
		temp = array[i];
		array[i] = array[min];
		array[min] = temp;
	}

}

template<class T>
void insertionsort(vector<T> &array) {
	

	for(int i = 1; i < array.size(); i++)
	{
		T key = array[i];
		int j = i - 1;


		while(j >= 0 && array[j] > key)
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}

}

// Faz o merge dos subarrays em aux para array, isto C), array[...] = aux[...]
template<class T>
void merge(vector<T> &array, vector<T> &aux, int start, int mid, int finish) {
	
	int k = start;
	int i = start;
	int j = mid;
	while(i < mid && j <= finish)
	{

		if(aux[i] <= aux[j])
		{
			array[k] = aux[i];
			i++;
		}
		else if(aux[j] < aux[i])
		{
			array[k] = aux[j];
			j++;
		}
		k++;
	}
	while(i < mid)
	{
		array[k] = aux[i];
		i++;
		k++;

	}
	while(j <= finish)
	{
		array[k] = aux[j];
		j++;
		k++;
	}
}

// Array: array que vai conter o resultado ordenado
// Aux: array auxiliar usado para ordenar as duas metades, esquerda e direita
// Repare que na chamada recursiva de mergesorte, array e aux se alternam
// Isto C), uma hora um C) o principal e o outro C) o auxiliar, depois invertem
template<class T>
void mergesort(vector<T> &array, vector<T> &aux, int start, int finish) {
	if (start >= finish) return;

	int mid = (start + finish)/2;

	mergesort(aux, array, start, mid);
	mergesort(aux, array, mid + 1, finish);

	merge(array, aux, start, mid + 1, finish);
}

// Função chamada inicialmente;
// Chama a função mergesorte() acima com os limites start e finish, e o clone do array (aux).
template<class T>
void mergesort(vector<T> &array) {
	vector<T> aux = array; // TODO errado!
	mergesort(array, aux, 0, array.size() - 1);
}


// template<class T>
// int partition(vector<T> &array, int start, int finish) {
// 	// TODO
// 	 T pivot = array[finish];
//     int i = start - 1;

//     for (int j = start; j < finish; j++) {
//         if (array[j] <= pivot) {
//             i++;
//             swap(array[i], array[j]);
//         }
//     }


//     swap(array[i + 1], array[finish]);
//     return i + 1;
// }

template<class T>
int partition(vector<T> &array, int start, int finish) {
	T pivot = array[start];      // PivC4 = primeiro elemento
	int i = start - 1;
	int j = finish + 1;

	while (true) {
		// Encontra elemento >= pivC4 da esquerda
		do {
			i++;
		} while (array[i] < pivot);

		// Encontra elemento <= pivC4 da direita
		do {
			j--;
		} while (array[j] > pivot);

		// Se os C-ndices se cruzaram, retorna ponto de divisC#o
		if (i >= j) {
			return j;
		}

		// Troca os elementos que estC#o nos lados errados
		swap(array[i], array[j]);
	}
}

template<class T>
void quicksort(vector<T> &array, int start, int finish) {
	if (finish <= start) return;
	int pivot = partition(array, start, finish);
	 quicksort(array, start, pivot);     
    quicksort(array, pivot + 1, finish);
}


template<class T>
void quicksort(vector<T> &array) {
	quicksort(array, 0, array.size() - 1);
}

template<class T>
void stdsort(vector<T> &array) {
	sort(array.begin(), array.end());
}

template<class T>
int validate(vector<T> &array) {
	for (int i = 0; i < array.size() - 1; i++) {
		if (array[i] > array[i + 1]) return 0;
	}
	return 1;
}

// Exibe um array na tela
template<class T>
void print(vector<T> &array) {
	for (int i = 0; i < array.size(); i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

// Testa um algoritmo passado como parC"metro.
template<class T>
void test(vector<T> &array, const char * name, void function(vector<T> &array), bool printFlag) {
	vector<T> copy = array;
	auto start = std::chrono::high_resolution_clock::now();

	function(copy);

	auto finish = std::chrono::high_resolution_clock::now();
	long elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count() / 1000;

	string status = "ok";
	if (!validate(copy)) {
		status = "error";
	} else {
		auto copy2 = array;
		sort(copy2.begin(), copy2.end());
		for (int i = 0; i < array.size(); i++) {
			if (copy[i] != copy2[i]) {
				status = "corrupted";
				break;
			}
		}
	}

	cout << name << ": " << status << " (tempo[us] = " << elapsed << ") ";

	if (printFlag) print(copy);
	else cout << endl;
}

#endif

