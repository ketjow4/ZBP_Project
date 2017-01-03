#ifndef SET_LLRB_H
#define SET_LLRB_H

#include "LLRB.h"






template<class T,class _Pr = less<T>, class _Alloc = allocator<T> >
	class setLLRB
	: public LLRB<T,T, _Pr, _Alloc, false>
{
		typedef typename T value_type;

		 T _Kfn( value_type _Val) 
		{
			return _Val;
		}
};



template<class T, class _Pr = less<T>, class _Alloc = allocator<T> >
class multisetLLRB
	: public LLRB<T,T, _Pr, _Alloc, true>
{
	typedef typename T value_type;

	 T _Kfn( value_type _Val) 
	{
		return _Val;
	}

};


#endif