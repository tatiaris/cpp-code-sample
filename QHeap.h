#pragma once

#include "MMHeap.h"
#include "Int4MMH.h"

template <typename T>
class QHeap
{
	MMHeap<T>** heaps;
    int length = 0;

public:
    QHeap() : heaps(nullptr) {};

	// constructs the quartile heap given an initial size
    QHeap(const int& initialSize)
    {
        heaps = new MMHeap<T>*[4];

		// create 4 empty mmheaps of size initialSize/4 + 1
        for (int i = 0; i < 4; i++)
        {
            heaps[i] = new MMHeap<T>((initialSize/4) + 1);
        }
    };

	// inserts new node px to the heap
    void insert(T* px)
    {
		// if heap is less than size 4, follow special measures
		if (length < 4)
        {
			// if px is the first element, insert it in the first mmheap
			if (length == 0)
	        {
	            heaps[0]->insert(px);
	        }
			// else check where the px fits, and place it there
			else
			{
				for (int i = 0; i < length; i++)
	            {
	                if (px < heaps[i]->getMin())
	                {
	                    for (int j = length; j > i; j--)
	                    {
	                        heaps[j]->insert(heaps[j - 1]->getMin());
	                        heaps[j - 1]->deleteMin();
	                    }
	                    heaps[i]->insert(px);
	                    break;
	                }
	                else if (i == length - 1)
	                {
	                    heaps[length]->insert(px);
	                }
	            }
			}
        }
		// else, see where px fits and place is accordingly
        else
        {
            int c = 0;
            while (c < 3 && heaps[c]->getMax() < px)
            {
                c++;
            }
            heaps[c]->insert(px);
            arrangeSelf();
        }
        length++;
    };

	// rearrange nodes between heaps to keep them level
    void arrangeSelf()
    {
		// run a nested for loop to compare each heap with the other and transfer nodes if they are uneven
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 4; j++)
            {
				// the max difference between the sizes of heaps should be 1
                if (heaps[i]->size() > heaps[j]->size() + 1)
                {
                    for (int k = j; k > i; k--)
                    {
                        heaps[k]->insert(heaps[k - 1]->getMax());
                        heaps[k - 1]->deleteMax();
                    }
                }
				else if (heaps[j]->size() > heaps[i]->size() + 1)
				{
					for (int k = i; k < j; k++)
                    {
                        heaps[k]->insert(heaps[k + 1]->getMin());
                        heaps[k + 1]->deleteMin();
                    }
				}
            }
        }
    };

	// get the smallest node in the entire quartile heap
    T* getMin()
    {
        return heaps[0]->getMin();
    };

	// get the largest node in the entire quartile heap
    T* getMax()
    {
        return heaps[3]->getMax();
    };

	// get the 25th percentile node in the entire quartile heap
    T* get25()
    {
        return heaps[0]->getMax();
    };

	// get the 50th percentile node in the entire quartile heap
    T* get50()
    {
        return heaps[1]->getMax();
    };

	// get the 75th percentile node in the entire quartile heap
    T* get75()
    {
        return heaps[2]->getMax();
    };

	// print information about the quartile heap
    void dump()
    {
        cout << "***********************************\n***** Quartile heap statistics ..." << endl;
        cout << "  Minimum = " << getMin()->toString() << endl;
        cout << "  25th Percentile = " << get25()->toString() << endl;
        cout << "  Median = " << get50()->toString() << endl;
        cout << "  75th Percentile = " << get75()->toString() << endl;
        cout << "  Maximum = " << getMax()->toString() << endl;

        cout << "***** First Quartile heap dump ..." << endl;
        heaps[0]->dump();
        cout << "***** Second Quartile heap dump ..." << endl;
        heaps[1]->dump();
        cout << "***** Third Quartile heap dump ..." << endl;
        heaps[2]->dump();
        cout << "***** Fourth Quartile heap dump ..." << endl;
        heaps[3]->dump();

        cout << "***** End of Quartile heap dump\n***********************************" << endl;
    };
};
