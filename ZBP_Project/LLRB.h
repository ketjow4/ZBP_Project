#ifndef LLRB_H
#define LLRB_H

#include <iostream>
#include <iomanip>

#include <stdexcept>
#include <iterator>

using namespace std;


template<typename T>
struct node
{
	T data;
	bool    IsRed;

	node<T>*   Left;
	node<T>*   Right;
	node<T>*   Parent;

	node(T data) : data(data), IsRed(true)
	{
		Parent = Left = Right = nullptr;
	}

	node() : IsRed(true)
	{
		//data = nullptr;
	}
};

template<class T, class key_type, class Compare, class Alloc, bool multi>
class LLRB;

template<typename T>
struct ItWrap
{
	typedef typename int difference_type;
	typedef typename T value_type;
	typedef typename const T * pointer;
	typedef typename const T & reference;
};

template<class T, class Compare, class Alloc, bool multi>
class const_iteratorLLRB
	: public iterator<bidirectional_iterator_tag,
	typename ItWrap<T>::value_type,
	typename ItWrap<T>::difference_type,
	typename ItWrap<T>::pointer,
	typename ItWrap<T>::reference>
{
public:
	typedef  const_iteratorLLRB<T,Compare,Alloc,multi> self_type;
	typedef bidirectional_iterator_tag iterator_category;

	typedef typename int difference_type;
	typedef typename T value_type;
	typedef typename const T * pointer;
	typedef typename const T & reference;
	typedef typename node<T>*  nodePtr;

	const_iteratorLLRB(nodePtr ptr, nodePtr root) : ptr_(ptr), root(root) { }

	self_type& operator++()	//preincrement
	{
		if (ptr_ == nullptr)
			;					//end() iterator value
		else if (ptr_->Right != nullptr)
		{
			ptr_ = ptr_->Right;
			while (ptr_->Left)		//it is find min function
			{
				ptr_ = ptr_->Left;
			}
			ptr_ = ptr_;
		}
		else
		{
			node<T>* y = ptr_->Parent;
			while (y != nullptr && ptr_ == y->Right)
			{
				ptr_ = y;
				y = y->Parent;
			}
			ptr_ = y;
		}
		return (*this);
	}
	self_type operator++(int)	// postincrement
	{
		self_type i = *this;
		++*this;
		return (i);
	}


	self_type operator--(int)	// postdecrement
	{
		self_type i = *this;
		--*this;
		return (i);
	}

	self_type& operator--()	// predecrement
	{
		if (ptr_ == nullptr)
			ptr_ = LLRB<T,T,Compare,Alloc,multi>::findMax(root);
		else if (ptr_->Left != nullptr)
		{
			ptr_ = ptr_->Left;
			while (ptr_->Right)		//it is find min function
			{
				ptr_ = ptr_->Right;
			}
			ptr_ = ptr_;
		}
		else
		{
			node<T>* y = ptr_->Parent;
			while (y != nullptr && ptr_ == y->Left)
			{
				ptr_ = y;
				y = y->Parent;
			}
			ptr_ = y;
		}
		return (*this);
	}

	reference operator*() const
	{
		return ptr_->data;
	}
	pointer operator->() const
	{
		return *ptr_->data;
	}
	bool operator==(const self_type& rhs) const
	{
		return ptr_ == rhs.ptr_;
	}
	bool operator!=(const self_type& rhs) const
	{
		return ptr_ != rhs.ptr_;
	}


	nodePtr ptr_;
private:
	nodePtr root;
};



template<class T, class Compare, class Alloc, bool multi>
class iteratorLLRB : public const_iteratorLLRB<T,Compare,Alloc,multi>
{
public:
	typedef  iteratorLLRB<T, Compare, Alloc, multi> self_type;
	typedef  const_iteratorLLRB<T, Compare, Alloc, multi> base_type;
	typedef bidirectional_iterator_tag iterator_category;

	typedef typename int difference_type;
	typedef typename T value_type;

	typedef typename node<T>*  nodePtr;

	iteratorLLRB(nodePtr ptr, nodePtr root) : base_type(ptr, root) { }

	self_type& operator++()	//preincrement
	{
		++static_cast<base_type&>(*this);
		return (*this);
	}
	self_type operator++(int)	// postincrement
	{
		self_type _Tmp = *this;
		++*this;
		return (_Tmp);
	}


	self_type operator--(int)	// postdecrement
	{
		self_type _Tmp = *this;
		--*this;
		return (_Tmp);
	}

	self_type& operator--()	// predecrement
	{
		--static_cast<base_type&>(*this);
		return (*this);
	}

	reference operator*() const
	{
		return   ((reference)**(base_type*)this);
	}
	pointer operator->() const
	{
		return (pointer_traits<pointer>::pointer_to(**this));
	}

private:
};



template<class T,class key_type,  class Compare, class Alloc, bool multi>	
class LLRB
{
public:

	typedef typename LLRB<T, key_type, Compare,Alloc,multi> self_type;
	typedef typename T value_type;
	typedef typename iteratorLLRB<T, Compare, Alloc, multi> iterator;
	typedef typename const_iteratorLLRB<T, Compare, Alloc, multi> const_iterator;
	typedef typename std::reverse_iterator<iteratorLLRB<T, Compare, Alloc, multi>> reverse_iterator;
	typedef typename std::reverse_iterator<const_iteratorLLRB<T, Compare, Alloc, multi>> const_reverse_iterator;


	self_type::LLRB()
	{
		_size = 0;
		root = nullptr;
	}

	template <class InputIterator>
	LLRB(InputIterator first, InputIterator last, const Compare& comp = cmp, const Alloc&   allo = al)
	{
		this->insert(first, last);
	}

	LLRB(const self_type& x)
	{
		this = x;
	}


	LLRB(const self_type& x, const Alloc&  allo = al)
	{
		//operator=(x);
		al = allo;
	}
	
	LLRB(self_type&& x)
	{
		operator=(x);
	}
	
	LLRB(self_type&& x, const Alloc&  allo = al)
	{
		operator=(x);
		al = allo;
	}
	
	LLRB(initializer_list<value_type> il, const Compare& comp = cmp, const Alloc&  allo = al)
	{
		this->insert(il);
		cmp = comp;
		al = allo;
	}


	self_type::~LLRB()
	{
		if (root != nullptr)
			Clear();
	}
	
	self_type& operator= (const self_type& _Right)
	{
		if (this != &_Right) // different, move it
		{
			clear();
			swap();
		}
		return (*this);
	}
	self_type& operator= (self_type&& _Right)
	{
		if (this != &_Right) // different, move it
		{	
			clear();
			swap();
		}
		return (*this);
	}
	self_type& operator= (initializer_list<value_type> il)
	{
		this->clear();
		this->insert(il);
		return (*this);
	}

	
	void Clear() noexcept	//change to recursive deletion 
	{
		do
		{
			auto _First = this->begin();
			erase(*_First);
		} while (this->begin() != this->end());
	}

	Alloc get_allocator() const noexcept
	{
		return al;
	}


	iterator begin()
	{
		return iterator(findMin(root), root);
	}

	iterator end()
	{
		return iterator(nullptr, root);
	}

	const_iterator cbegin() const noexcept
	{
		return const_iterator(findMin(root), root);
	}

	const_iterator cend() const noexcept
	{
		return const_iterator(nullptr, root);
	}

	reverse_iterator rbegin()
	{
		return  reverse_iterator(iterator(nullptr, root));;
	}

	reverse_iterator rend()
	{
		return reverse_iterator(iterator(findMin(root), root));;
	}

	const_reverse_iterator crbegin() const noexcept
	{
		return  const_reverse_iterator(const_iterator(nullptr, root));;
	}

	const_reverse_iterator crend() const noexcept
	{
		return const_reverse_iterator(const_iterator(findMin(root), root));;
	}



	pair<iterator, bool> insert(const value_type& val)
	{
		auto it = find(val);
		if(multi == false && it != end())
			return std::pair<iterator, bool>(it, false);
		root = insert(root, val);
		root->IsRed = false;
		_size++;
		return std::pair<iterator, bool>(it, it != end());
	}

	pair<iterator, bool> insert(value_type&& val)
	{
		auto it = find(val);			//if not in set it == end()
		if (multi == false && it != end())
			return std::pair<iterator, bool>(it, false);
		root = insert(root, val);
		root->IsRed = false;
		_size++;
		return std::pair<iterator, bool>(it, it != end());
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		for (; first != last; first++)
			insert(*first);
	}
	void insert(initializer_list<value_type> il)
	{
		insert(il.begin(), il.end());
	}


	template <class... Args>
	pair<iterator, bool> emplace(Args&&... args)		//test!!!!
	{
		node<T>* _Newnode = createNode(std::forward<_Valty>(_Val)...);
		insert(root,_Newnode->data,_Newnode);
		return std::make_pair<iterator,bool>(iterator(_Newnode,root), find(_Newnode->data) != end())
	}


	iterator erase(const_iterator position)		//test
	{
		root = erase(root, *position);
		_size--;
		if (root != nullptr)
			root->IsRed = false;
		return iterator(++position.ptr_, root);
	}
	
	unsigned long erase(const value_type& val)		//test
	{
		auto _Where = equal_range(val);
		unsigned long _Num =  std::distance(_Where.first, _Where.second);
		erase(_Where.first, _Where.second);
		_size -= _Num;
		return (_Num);
	}
	iterator  erase(const_iterator first, const_iterator last)		//test but should work
	{
		if (first == begin() && last == end())
		{	// erase all
			Clear();
			return (begin());
		}
		else
		{	// partial erase, one at a time
			while (first != last)
				erase(first++);
			return (iterator(first.ptr_, root));
		}
	}



	Compare key_comp() const
	{
		return cmp;
	}
	
	Compare value_comp() const
	{
		return cmp;
	}

	
	void swap(self_type& _Right)
	{
		if (this != &_Right)
		{
			std::swap(_GetAl(), _Right._GetAl());
			//std::swap(_Myhead(), _Right._Myhead());
			node<T>* h1 = _Myhead();
			node<T>* h2 = _Right._Myhead();
			node<T>* tmp = h1;
			h1 = h2;
			h2 = tmp;
			_Sethead(h1);
			_Right._Sethead(h2);
			std::swap(_Mysize(), _Right._Mysize());
			std::swap(_GetComp(), _Right._GetComp());
		}
	}


	template<typename T>
	const_iterator find(const T& val) const
	{
		node<T>* temp = root;
		while (temp != nullptr)
		{
			if (!(cmp(data, temp->data)) && !(cmp(temp->data, data)))
			{
				return const_iterator(temp, root);
			}
			if (cmp(data, temp->data))
				temp = temp->Left;
			else
				temp = temp->Right;
		}
		return const_iterator(nullptr, root);
	}


	template<typename T>
	iterator find(const T& data)
	{
		node<T>* temp = root;
		while (temp != nullptr)
		{
			if (!(cmp(_Kfn(data), _Kfn(temp->data))) && !(cmp(_Kfn(temp->data), _Kfn(data))))
			{
				return iterator(temp, root);
			}
			if (cmp(_Kfn(data), _Kfn(temp->data)))
				temp = temp->Left;
			else
				temp = temp->Right;
		}
		return iterator(nullptr, root);
	}


	//--------------------------------------------------------------BEGIN print tree on std::out ------------------------------------------------------------
	static void postorder(ostream& out, node<T>* p, int indent = 0)
	{
		if (p != nullptr) {
			if (p->Right) {
				postorder(out, p->Right, indent + 4);
			}
			if (indent) {
				out << std::setw(indent) << ' ';
			}
			if (p->Right) out << " /\n" << std::setw(indent) << ' ';
			out << p->data << "\n ";
			if (p->Left) {
				out << std::setw(indent) << ' ' << " \\\n";
				postorder(out, p->Left, indent + 4);
			}
		}
	}

	friend ostream& operator<<(ostream& out, LLRB& tree)
	{
		postorder(out, tree.root, 0);
		return out;
	}
	//--------------------------------------------------------------END print tree on std::out ------------------------------------------------------------

	

	template<typename T>
	static node<T>* findMin(node<T>* h)
	{
		if (h != nullptr)
		{
			node<T>* temp = h;
			while (temp->Left)
				temp = temp->Left;
			return temp;
		}
		return nullptr;
	}

	template<typename T>
	static node<T>* findMax(node<T>* h)
	{
		if (h != nullptr)
		{
			node<T>* temp = h;
			while (temp->Right)
				temp = temp->Right;
			return temp;
		}
		return nullptr;
	}

	unsigned int size() const noexcept
	{
		return _size;
	}

	bool empty() const noexcept
	{
		return (_size == 0)
	}

	
	template<typename T>
	unsigned long count(const T& val) const
	{
		auto _Ans = equal_range(val);
		return (std::distance(_Ans.first, _Ans.second));
	}

	unsigned long max_size() const noexcept
	{
		return al.max_size();
	}


	iterator lower_bound(const value_type& val)
	{
		return iterator(_Lbound(val), root);
	}
	const_iterator lower_bound(const value_type& val) const
	{
		return const_iterator(_Lbound(val), root);
	}

	iterator upper_bound(const value_type& val)
	{
		return iterator(_Ubound(val), root);
	}
	const_iterator upper_bound(const value_type& val) const
	{
		return const_iterator(_Ubound(val), root);
	}

	pair<const_iterator, const_iterator> equal_range(const value_type& val) const
	{
		node<T>* Hi = _Ubound(val);
		node<T>* Lo = _Lbound(val);
		return make_pair<const_iterator, const_iterator>(const_iterator(Lo, root), const_iterator(Hi, root));
	}
	pair<iterator, iterator> equal_range(const value_type& val)
	{
		node<T>* Hi = _Ubound(val);
		node<T>* Lo = _Lbound(val);
		return make_pair<iterator, iterator>(iterator(Lo, root), iterator(Hi, root));
	}


	node<T>* _Myhead()
	{
		return root;
	}

	void _Sethead(node<T>* ptr)
	{
		root = ptr;
	}

	unsigned int& _Mysize()
	{
		return _size;
	}

	Alloc& _GetAl()
	{
		return al;
	}

	Compare& _GetComp()
	{
		return cmp;
	}








	template<typename T>
	node<T>* insert(node<T>* h, T data)
	{
		if (h == nullptr)
			return  createNode(data);		//new node<T>(data);

		if (cmp(_Kfn(data), _Kfn(h->data)))
		{
			h->Right = insert(h->Right, data);
			h->Right->Parent = h;
		}
		else
		{
			h->Left = insert(h->Left, data);
			h->Left->Parent = h;
		}
		if (IsRed(h->Right) && !IsRed(h->Left))
			h = rotateLeft(h);
		if (IsRed(h->Left) && IsRed(h->Left->Left))
			h = rotateRight(h);
		if (IsRed(h->Left) && IsRed(h->Right))
			flipColors(h);

		return h;
	}

	template<typename T>
	node<T>* insert(node<T>* h, T data, node<T>* node)
	{
		if (h == nullptr)
			return  node;

		if (cmp(data, h->data))
		{
			h->Right = insert(h->Right, data);
			h->Right->Parent = h;
		}
		else
		{
			h->Left = insert(h->Left, data);
			h->Left->Parent = h;
		}
		if (IsRed(h->Right) && !IsRed(h->Left))
			h = rotateLeft(h);
		if (IsRed(h->Left) && IsRed(h->Left->Left))
			h = rotateRight(h);
		if (IsRed(h->Left) && IsRed(h->Right))
			flipColors(h);

		return h;
	}






	unsigned int _size;

private:
	Compare cmp;
	Alloc al;
	node<T>* root;




	template<class T>
	node<T>* _Lbound(const T& _Keyval)  // find leftmost node not less than _Keyval
	{	
		node<T>* tmp = root;
		node<T>* _Wherenode = _Myhead();	// end() if search fails

		while (!tmp)
			if (cmp(_Kfn(tmp->data), _Kfn(_Keyval)))
				tmp =  tmp->Right;	// descend right subtree
			else
			{	// tmp not less than _Keyval, remember it
				_Wherenode = tmp;
				tmp = tmp->Left;	// descend left subtree
			}

		return (_Wherenode);	// return best remembered candidate
	}

	template<class T>
	node<T>* _Ubound(const T& _Keyval)  // find leftmost node greater than _Keyval
	{	
		node<T>* tmp = root;
		node<T>* _Wherenode = _Myhead();	// end() if search fails

		while (!tmp)
			if (cmp(_Kfn(_Keyval), _Kfn(tmp->data)))
			{	// _Pnode greater than _Keyval, remember it
				_Wherenode = tmp;
				tmp = tmp->Left;	// descend left subtree
			}
			else
				tmp = tmp->Right;	// descend right subtree

		return (_Wherenode);	// return best remembered candidate
	}


	template<typename T>
	node<T>* createNode(T data)
	{
		auto a = Alloc::rebind<node<T>>::other(al);
		node<T>* temp = a.allocate(1);
		try
		{
			a.construct(temp, data);
		}
		catch (...)
		{
			a.deallocate(temp, 1);
			throw std::bad_alloc();
		}
		return temp;
	}

	template<class... _Valty>
	node<T>* createNode(_Valty&&... _Val)
	{	// allocate a node with defaults and set links and value
		auto a = Alloc::rebind<node<T>>::other(al);
		node<T>* temp = a.allocate(1);

		try {
			a.construct(std::addressof(temp->Left, nullptr));
			a.construct(std::addressof(temp->Right, nullptr));
			a.construct(std::addressof(temp->Parent, nullptr));
		}
		catch(...)
		{
			a.deallocate(temp, 1);
			throw std::bad_alloc();
		}
		temp->IsRed = true;

		try
		{
			a.construct(std::addressof(temp->data),std::forward<_Valty>(_Val)...);
		}
		catch(...)
		{
			a.deallocate(temp, 1);
			throw std::bad_alloc();		
		}
		return (temp);
	}

	void destroyNode(node<T>* free)
	{
		//delete free;
		auto a = Alloc::rebind<node<T>>::other(al);
		a.destroy(free->Left);
		a.destroy(free->Right);
		a.destroy(free->Parent);
		a.deallocate(free, 1);
	}


	template<typename T>
	node<T>* deleteMin()
	{
		if (root != nullptr)
		{
			root = deleteMin(root);
			if (root)
				root->IsRed = false;
		}
	}

	template<typename T>
	node<T>* rotateLeft(node<T>* a)
	{
		auto b = a->Right;

		if (a->Right = b->Left)
			a->Right->Parent = a;

		b->Left = a;
		b->IsRed = a->IsRed;
		a->IsRed = true;

		b->Parent = a->Parent;
		a->Parent = b;

		return b;
	}

	template<typename T>
	node<T>* rotateRight(node<T>* b)
	{
		auto a = b->Left;

		if (b->Left = a->Right)
			b->Left->Parent = b;

		a->Right = b;
		a->IsRed = b->IsRed;
		b->IsRed = true;

		a->Parent = b->Parent;
		b->Parent = a;

		return a;
	}

	template<typename T>
	void flipColors(node<T>* h)
	{
		h->IsRed = !h->IsRed;
		h->Left->IsRed = !h->Left->IsRed;
		h->Right->IsRed = !h->Right->IsRed;
	}


	template<typename T>
	node<T>* erase(node<T>* h, T data)
	{
		if (cmp(_Kfn(h->data), _Kfn(data)))			//operator <
		{
			if (!IsRed(h->Left) && !IsRed(h->Left->Left))
				h = moveRedLeft(h);
			h->Left = erase(h->Left, data);
		}
		else
		{
			if (IsRed(h->Left))
				h = rotateRight(h);
			if (!(cmp(_Kfn(data), _Kfn(h->data))) && !(cmp(_Kfn(h->data), _Kfn(data))) && h->Right == nullptr)
			{
				destroyNode(h);		//delete h;
				return nullptr;
			}
			if (!IsRed(h->Right) && !IsRed(h->Right->Left))
				h = moveRedRight(h);
			if (!(cmp(_Kfn(data), _Kfn(h->data))) && !(cmp(_Kfn(h->data), _Kfn(data))))
			{
				h->data = findMin(h->Right)->data;
				h->Right = deleteMin(h->Right);
			}
			else
				h->Right = erase(h->Right, data);
		}
		return fixUp(h);
	}


	template<typename T>
	node<T>* fixUp(node<T>* h)
	{
		if (IsRed(h->Right))
			h = rotateLeft(h);
		if (IsRed(h->Left) && IsRed(h->Left->Left))
			h = rotateRight(h);
		if (IsRed(h->Left) && IsRed(h->Right))
			flipColors(h);

		return h;
	}

	template<typename T>
	node<T>* deleteMin(node<T>* h)
	{
		if (h->Left == nullptr)
		{
			destroyNode(h);	//delete h;
			return nullptr;
		}
		if (!IsRed(h->Left) && !IsRed(h->Left->Left))
			h = moveRedLeft(h);

		h->Left = deleteMin(h->Left);

		return fixUp(h);
	}

	template<typename T>
	node<T>* moveRedLeft(node<T>* h)
	{
		flipColors(h);
		if (IsRed(h->Right->Left))
		{
			h->Right = rotateRight(h->Right);
			h = rotateLeft(h);
			flipColors(h);
		}
		return h;
	}

	template<typename T>
	node<T>* moveRedRight(node<T>* h)
	{
		flipColors(h);
		if (IsRed(h->Left->Left))
		{
			h = rotateRight(h);
			flipColors(h);
		}
		return h;
	}

	template<typename T>
	bool IsRed(node<T>* h)
	{
		if (h == nullptr)
			return false;
		else
			return h->IsRed;
	}




	virtual  key_type _Kfn(value_type _Val) = 0;


	//const key_type& _Key(_Nodeptr _Pnode) const
	//{	// return reference to key in node
	//	return ((const key_type&)this->_Kfn(this->_Myval(_Pnode)));
	//}

};

#endif // !LLRB_H

