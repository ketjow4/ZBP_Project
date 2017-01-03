#ifndef MAP_LLRB_H
#define MAP_LLRB_H

#include "LLRB.h"




template<class T, class key, class _Pr = less<T>, class _Alloc = allocator<std::pair<key,T>>>
class mapLLRB
	: public LLRB<std::pair<key, T>, key, _Pr, _Alloc, false>
{
public:
	typedef typename pair< key, T> value_type;
	typedef typename T mapped_type;

	 key _Kfn( value_type _Val) 
	{	
		 return _Val.first;
	}

	 //TODO
	 mapped_type& operator[] (const key& k)
	 {

	 }

	 //TODO
	 mapped_type& operator[] (key&& k)
	 {

	 }

	 //TODO
	 mapped_type& at(const key& k)
	 {

	 }

	 //TODO
	 const mapped_type& at(const key& k) const
	 {

	 }

	 using LLRB<std::pair<key, T>, key, _Pr, _Alloc, false>::insert;

	 //TODO
	 pair<iterator, bool> insert(const value_type& val)
	 {
		 std::cout << "Insert from map\n";
		 auto it = find(val);
		 if (false == false && it != end())
			 return std::pair<iterator, bool>(it, false);
		 _Sethead(insert(_Myhead(), val));
		 _Myhead()->IsRed = false;
		 _size++;
		 return std::pair<iterator, bool>(it, it != end());
	 }

	 //TODO
	 pair<iterator, bool> insert(value_type&& val)
	 {
		 std::cout << "Insert from map\n";
		 auto it = find(val);			//if not in set it == end()
		 if (false == false && it != end())
			 return std::pair<iterator, bool>(it, false);
		 _Sethead(insert(_Myhead(), val));
		 _Myhead()->IsRed = false;
		 _size++;
		 return std::pair<iterator, bool>(it, it != end());
	 }

private:

};


template<class T, class key, class _Pr = less<T>, class _Alloc = allocator<std::pair<key, T>>>
class multimapLLRB
	: public LLRB<std::pair<key, T>, key, _Pr, _Alloc, true>
{
	typedef typename pair< key, T> value_type;

	key _Kfn(value_type _Val)
	{
		return _Val.first;
	}

private:

};


#endif