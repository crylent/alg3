#include <iostream>
#include "BinaryHeap.h"

using namespace std;

void print_wft(BinaryHeap* heap) {
    Iterator* iter = heap->create_wft_iterator();
    while (iter->has_next()) {
        cout << iter->next() << ' ';
    }
    cout << '\n';
}

int main()
{
    BinaryHeap* heap = new BinaryHeap(0, 1, 2, 3, 4, 5, 6, 7, 8);
    print_wft(heap);
    heap->insert(6, 12, 6, 3);
    print_wft(heap);
    heap->remove(1);
    heap->remove(2);
    heap->remove(4);
    heap->remove(8);
    print_wft(heap);
}