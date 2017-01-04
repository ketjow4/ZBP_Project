#ifndef MAP_LLRB_H
#define MAP_LLRB_H

#include "LLRB.h"




template<class T, class key, class _Pr = less<T>, class _Alloc = allocator<std::pair<key,T>>>
class mapLLRB
	: public LLRB<std::pair<key, T>, key, _Pr, _Alloc, false>
{
public:
	typedef typename std::pair< key, T> value_type;
	typedef typename T mapped_type;
	typedef typename key key_type;

	 key _Kfn( value_type _Val) 
	{	
		 return _Val.first;
	}



	 template<class _Keyty,
		 class... _Mappedty>
		 std::pair<iterator,bool> _Try_emplace(_Keyty&& _Keyval,
			 _Mappedty&&... _Mapval)
	 {	// fail if _Keyval present, else emplace
		 iterator _Where = lower_bound(_Keyval);
		 if (_Where == end())
			 return (std::pair<iterator,bool>(emplace(piecewise_construct,
					 std::forward_as_tuple(std::forward<_Keyty>(_Keyval)),
					 std::forward_as_tuple(std::forward<_Mappedty>(_Mapval)...)).first ,
				 true));
		 else
			 return (std::pair<iterator,bool>(_Where, false));
	 }

	 template<class... _Mappedty>
	 std::pair<iterator,bool> try_emplace(const key_type& _Keyval,
		 _Mappedty&&... _Mapval)
	 {	// fail if _Keyval present, else emplace
		 return (_Try_emplace(_Keyval, std::forward<_Mappedty>(_Mapval)...));
	 }

	 template<class... _Mappedty>
	 iterator try_emplace(const_iterator, const key_type& _Keyval,
		 _Mappedty&&... _Mapval)
	 {	// fail if _Keyval present, else emplace, ignore hint
		 return (_Try_emplace(_Keyval,
			 std::forward<_Mappedty>(_Mapval)...).first);
	 }

	 template<class... _Mappedty>
	 std::pair<iterator,bool> try_emplace(key_type&& _Keyval,
		 _Mappedty&&... _Mapval)
	 {	// fail if _Keyval present, else emplace
		 return (_Try_emplace(std::move(_Keyval),
			 std::forward<_Mappedty>(_Mapval)...));
	 }

	 template<class... _Mappedty>
	 iterator try_emplace(const_iterator, key_type&& _Keyval,
		 _Mappedty&&... _Mapval)
	 {	// fail if _Keyval present, else emplace, ignore hint
		 return (_Try_emplace(std::move(_Keyval),
			 std::forward<_Mappedty>(_Mapval)...).first);
	 }


	 //TODO
	 mapped_type& operator[] (const key& k)
	 {
		 return (try_emplace(k).first->second);
	 }

	 //TODO
	 mapped_type& operator[] (key&& k)
	 {
		 auto result = try_emplace(k).first;
		 int a = 1;
		 return a;//result->second;
	 }

	 //using LLRB<std::pair<key, T>, key, _Pr, _Alloc, false>::lower_bound;
	 //using LLRB<std::pair<key, T>, key, _Pr, _Alloc, false>::const_iterator;

	 //TODO
	 mapped_type& at(const key& k)
	 {
		 iterator _Where = lower_bound(k);
		 if (_Where == end())
			 std::out_of_range("invalid map<K, T> key");
		 return (_Where->second);
	 }

	 //TODO
	 const mapped_type& at(const key& k) const
	 {
		 const_iterator _Where = lower_bound(k);
		 if (_Where == end())
			 std::out_of_range("invalid map<K, T> key");
		 return (_Where->second);
	 }

	 using LLRB<std::pair<key, T>, key, _Pr, _Alloc, false>::insert;

	 //TODO
	 pair<iterator, bool> insert(const value_type& val)
	 {
		 auto it = find(val);
		 if (it != end())
			 return std::pair<iterator, bool>(it, false);
		 _Sethead(insert(_Myhead(), val));
		 _Myhead()->IsRed = false;
		 _size++;
		 return std::pair<iterator, bool>(it, it != end());
	 }

	 //TODO
	 pair<iterator, bool> insert(value_type&& val)
	 {
		 auto it = find(val);			//if not in set it == end()
		 if (it != end())
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