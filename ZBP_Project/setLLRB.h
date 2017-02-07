#ifndef SET_LLRB_H
#define SET_LLRB_H

#include "LLRB.h"


#include <functional>



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

		 template<class iter>
		 setLLRB(iter begin, iter end)
			 : base()
		 {	// construct from range
			 this->insert(begin,end);
		 }
};



template<class T, class _Pr = less<T>, class _Alloc = allocator<T> >
class multisetLLRB
	: public LLRB<T,T, _Pr, _Alloc, true>
{
public:
	typedef typename T value_type;
	typedef typename LLRB<T, T, _Pr, _Alloc, true> base;
	typedef typename multisetLLRB<T, _Pr, _Alloc> self_type;


	 T _Kfn( value_type _Val) 
	{
		return _Val;
	}


	 multisetLLRB() : base()
	 {
	 }

	 multisetLLRB(const self_type& x) : base(x)
	 {
	 }

	 multisetLLRB(const self_type&& x) : base(std::move(x))
	 {
	 }

	 multisetLLRB(initializer_list<value_type> _Ilist)
		 : base()
	 {	// construct from initializer_list, defaults
		 this->insert(_Ilist);
	 }

	 template<class iter>
	 multisetLLRB(iter begin, iter end)
		 : base()
	 {	
		 this->insert(begin, end);
	 }

};


#endif