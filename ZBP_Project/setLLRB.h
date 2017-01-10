#ifndef SET_LLRB_H
#define SET_LLRB_H

#include "LLRB.h"






template<class T,class _Pr = less<T>, class _Alloc = allocator<T> >
	class setLLRB
	: public LLRB<T,T, _Pr, _Alloc, false>
{
public:

		typedef typename T value_type;
		typedef typename LLRB<T, T, _Pr, _Alloc, false> base;
		typedef typename setLLRB<T, _Pr, _Alloc> self_type;

		 T _Kfn( value_type _Val) 
		{
			return _Val;
		}


		 setLLRB() : base()
		 {
		 }

		 setLLRB(const self_type& x) : base(x)
		 {
		 }

		 setLLRB(const self_type&& x) : base(std::move(x))
		 {
		 }

		 setLLRB( initializer_list<value_type> _Ilist)
			 : base()
		 {	// construct from initializer_list, defaults
			 this->insert(_Ilist);
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