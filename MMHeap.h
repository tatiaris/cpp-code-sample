#pragma once

#include <string>
#include <iostream>

using namespace std;

template <typename T>
class MMHeap
{
private:
    T** pData;
    size_t length;
    int level;

public:
    // constructor
    MMHeap() : pData(nullptr), length(0) {};

    // constructor with defined size
	MMHeap(const int& initialSize) : length(0) 
    {
        pData = new T*[initialSize+1];
    };

    // returns the size of the heap
    size_t size() const { return length; };

    // inserts new node px to the heap
    void insert(T* px)
    {
        for (int i = 0; i < length + 1; i++)
        {
            if (pData[i] == nullptr)
            {
                pData[i] = px;
                pushUp(i);
                break;
            }
        }
        length++;
    };

    // pushes down the misplaced node if it starts at a max level
    void pushDown(int i)
    {
        // call the appropriate level push down function for i's level
        if (isMinLevel(i))
        {
            pushDownMin(i);
        }
        else
        {
            pushDownMax(i);
        }
    };

    // pushes down the misplaced node if it starts at a min level
    void pushDownMin(int i)
    {
        // check if node i has children, or else it's in the right place no matter what
        if (hasChildren(i))
        {
            int m = getSmallestChild(i);
            if (i == getParent(getParent(m)))
            {
                // if i is larger than its grandchild, swap it with it and call pushDownMin again
                if (pData[m] < pData[i])
                {
                    swap(m, i);
                    if (getParent(m) > -1 && pData[m] > pData[getParent(m)])
                    {
                        swap(m, getParent(m));
                    }
                    pushDownMin(m);
                }
            }
            // if i is larger than it's child, swap them
            else if(pData[m] < pData[i])
            {
                swap(m, i);
            }
        }
    };

    // pushes a misplaced node down to where it belongs
    void pushDownMax(int i)
    {
        // check if node i has children, or else it's in the right place no matter what
        if (hasChildren(i))
        {
            int m = getLargestChild(i);
            if (i == getParent(getParent(m)))
            {
                // if i is smaller than its grandchild, swap it with it and call pushDownMax again
                if (pData[m] > pData[i])
                {
                    swap(m, i);
                    if (pData[m] < pData[getParent(m)])
                    {
                        swap(m, getParent(m));
                    }
                    pushDownMax(m);
                }
            }
            // if i is smaller than it's child, swap them
            else if(pData[m] > pData[i])
            {
                swap(m, i);
            }
        }
    };

    // returns the smallest child of node at index i amongst its immediate children and grandchildren
    int getSmallestChild(int i)
    {
        // compare all children and grandchildren of node at index i and return the smallest one's index
        int smallIndex = 2*i + 1;
        if (pData[2*i + 2] != nullptr && pData[2*i + 2] < pData[smallIndex])
        {
            smallIndex = 2*i + 2;
        }
        if (pData[4*i + 3] != nullptr && pData[4*i + 3] < pData[smallIndex])
        {
            smallIndex = 4*i + 3;
        }
        if (pData[4*i + 4] != nullptr && pData[4*i + 4] < pData[smallIndex])
        {
            smallIndex = 4*i + 4;
        }
        if (pData[4*i + 5] != nullptr && pData[4*i + 5] < pData[smallIndex])
        {
            smallIndex = 4*i + 5;
        }
        if (pData[4*i + 6] != nullptr && pData[4*i + 6] < pData[smallIndex])
        {
            smallIndex = 4*i + 6;
        }
        return smallIndex;
    };

    // returns the largest child of node at index i amongst its immediate children and grandchildren
    int getLargestChild(int i)
    {
        // compare all children and grandchildren of node at index i and return the largest one's index
        int largeIndex = 2*i + 1;
        if (pData[2*i + 2] != nullptr && pData[2*i + 2] > pData[largeIndex])
        {
            largeIndex = 2*i + 2;
        }
        if (pData[4*i + 3] != nullptr && pData[4*i + 3] > pData[largeIndex])
        {
            largeIndex = 4*i + 3;
        }
        if (pData[4*i + 4] != nullptr && pData[4*i + 4] > pData[largeIndex])
        {
            largeIndex = 4*i + 4;
        }
        if (pData[4*i + 5] != nullptr && pData[4*i + 5] > pData[largeIndex])
        {
            largeIndex = 4*i + 5;
        }
        if (pData[4*i + 6] != nullptr && pData[4*i + 6] > pData[largeIndex])
        {
            largeIndex = 4*i + 6;
        }
        return largeIndex;
    };

    // returns true if node at index i has a child
    bool hasChildren(int i)
    {
        if (pData[2*i + 1] != nullptr) return true;
        return false;
    };

    // bubbles up new node i
    void pushUp(int i)
    {
        if (i != 0)
        {
            // if i is not the root of the heap, check which level i is at and proceed accordingly
            if (isMinLevel(i))
            {
                // replace with parent if they're in contradicting spots
                if (pData[i] > pData[getParent(i)])
                {
                    swap(i, getParent(i));
                    pushUpMax(getParent(i));
                }
                else
                {
                    pushUpMin(i);
                }
            }
            else
            {
                // replace with parent if they're in contradicting spots
                if (pData[i] < pData[getParent(i)])
                {
                    swap(i, getParent(i));
                    pushUpMin(getParent(i));
                }
                else
                {
                    pushUpMax(i);
                }
            }
        }
    };

    // bubbles up a newly inserted node up if it was initially in a max level
    void pushUpMax(int i)
    {
        // compare node_i with it's grandparent and swap them if their values contradicts according to their level
        if (hasGrandParent(i) && pData[i] > pData[getParent(getParent(i))])
        {
            swap(i, getParent(getParent(i)));
            pushUpMax(getParent(getParent(i)));
        }
    };

    // bubbles up a newly inserted node up if it was initially in a min level
    void pushUpMin(int i)
    {
        // compare node_i with it's grandparent and swap them if their values contradicts according to their level
        if (hasGrandParent(i) && pData[i] < pData[getParent(getParent(i))])
        {
            swap(i, getParent(getParent(i)));
            pushUpMin(getParent(getParent(i)));
        }
    };

    // checks if node at index i has a grandparent node
    bool hasGrandParent(int i)
    {
        if (i > 2) return true;
        return false;
    };

    // returns the index of the parent of i
    int getParent(int i)
    {
        return (i - 1)/2;
    };

    // swaps positions of 2 values in the heap
    void swap(int i1, int i2)
    {
        T* temp = pData[i1];
        pData[i1] = pData[i2];
        pData[i2] = temp;
        temp = nullptr;
    };

    // returns true if index i is on an a min level and false if on a max
    bool isMinLevel(int i)
    {
        // if root, return true
        if (i == 0) return true;

        int c = 0;
        int k = 2;

        // increase k by the power of 2 till it's greater than i, this will tell us the level of node_i
        while (i + 1 >= k)
        {
            k *= 2;
            c++;
        }

        if (c%2 == 0) return true;
        return false;
    };

    // prints information about the heap
    void dump()
    {
        string l;
        if (isMinLevel(length - 1)) l = "even";
        else l = "odd";

        cout << "---------------------------------------" << endl;
        cout << "--- min-max heap dump ---" << endl;
        cout << "  Size = " << length << endl;
        cout << "  Minimum = " << getMin()->toString() << endl;
        cout << "  Maximum = " << getMax()->toString() << endl;
        cout << "  Last level is " << l << endl;
        cout << "--- heap data items ---" << endl;

        // print the entire heap
        for (int i = 0; i < length; i++)
        {
            if (pData[i] != nullptr)
                cout << "H[" << i + 1 << "] = " << pData[i]->toString() << endl;
        }
        cout << "---------------------------------------" << endl;
    };

    // deletes element i and replaces it with the last element
    void replaceLastElement(int i)
    {
        pData[i] = pData[length - 1];
        pData[length - 1] = nullptr;
    }

    // returns the min data in the heap
    T* getMin()
    {
        // return first element
        if (pData[0])
        {
            return pData[0];
        }
        return nullptr;
    };

    // returns the max data in the heap
    T* getMax()
    {
        // compare the nodes at level 1 if they exist and return the higher one
        if (pData[1] && pData[2])
        {
            if (pData[1] >= pData[2]) return pData[1];
            return pData[2];
        }
        else
        {
            if (pData[1])
            {
                return pData[1];
            }
            if (pData[2])
            {
                return pData[2];
            }
            // if level one does not exist yet, return the first value of the heap
            if (pData[0])
            {
                return pData[0];
            }
        }
        return nullptr;
    };

    // deletes the min data in the heap
    T deleteMin()
    {
        // delete first item
        T dat = *pData[0];
        replaceLastElement(0);
        length--;
        pushDown(0);
        return dat;
    };

    // deletes the max data in the heap
    T deleteMax()
    {
        int i;
        // compare the values at level one and delete the larger one
        if (pData[1] > pData[2]) i = 1;
        else i = 2;

        T dat = *pData[i];
        replaceLastElement(i);
        length--;
        pushDown(i);
        return dat;
    };
};
