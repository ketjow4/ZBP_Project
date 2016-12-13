#ifndef SET_LLRB_H
#define SET_LLRB_H

#include "LLRB.h"


template<class T,class _Pr = less<T>, class _Alloc = allocator<T> >
	class setLLRB
	: public LLRB<T, _Pr, _Alloc>
{

};


#endif