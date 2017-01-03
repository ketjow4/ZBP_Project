#ifndef MAP_LLRB_H
#define MAP_LLRB_H

#include "LLRB.h"




template<class T, class key, class _Pr = less<T>, class _Alloc = allocator<std::pair<key,T>>>
class mapLLRB
	: public LLRB<std::pair<key, T>, key, _Pr, _Alloc, false>
{
	typedef typename pair< key, T> value_type;


	bool operator()(const value_type& _Left, const value_type& _Right) const
	{	// test if _Left precedes _Right by comparing just keys
		return (comp(_Left.first, _Right.first));
	}

	 key _Kfn( value_type _Val) 
	{	
		 return _Val.first;
	}

private:
	_Pr comp;
};





#endif