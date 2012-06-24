#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>

template <class T>
void deleteInVector(std::vector<T*>* deleteme) {
	T *t;
    while(!deleteme->empty()) {
        t = deleteme->back();
        delete t;
		t = nullptr;
        deleteme->pop_back();
    }

    delete deleteme;
	deleteme = nullptr;
}

template <class T>
void deleteInVector(std::vector<T*> deleteme) {
	T *t;

    while(!deleteme.empty()) {
		t = deleteme.back();
        delete t;
		t = nullptr;
        deleteme.pop_back();
    }

    
}
#endif