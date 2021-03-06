#ifndef LLRB_H
#define LLRB_H

#include <iostream>
#include <iomanip>

#include <stdexcept>
#include <iterator>

#include <type_traits>

using namespace std;


template<typename T>
struct node
{
	node<T>*   Left;
	node<T>*   Right;
	node<T>*   Parent;
	bool    IsRed;
	T data;

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
	typedef typename T& reference;
	typedef typename T* pointer;

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
	LLRB(InputIterator first, InputIterator last, const Compare& comp, const Alloc&   allo)
	{
		root = nullptr;
		this->insert(first, last);
	}

	LLRB(const self_type& x)
	{
		root = nullptr;
		*this = x;
	}

	LLRB(self_type&& x)
	{
		operator=(x);
	}

	LLRB(const self_type& x, const Alloc&  allo)
	{
		root = nullptr;
		operator=(x);
		al = allo;
	}
	

	
	LLRB(self_type&& x, const Alloc&  allo)
	{
		root = nullptr;
		operator=(x);
		al = allo;
	}
	
	LLRB(initializer_list<value_type> il, const Compare& comp, const Alloc&  allo)
	{
		root = nullptr;
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
		if (this != &_Right) // different, copy it
		{
			Clear();
			for(auto it = _Right.cbegin(); it != _Right.cend(); ++it)
			{
				auto val = *it; 		//deep copy here
				insert(val);
			}
		}
		return (*this);
	}
	
	
	self_type& operator= (self_type&& _Right)
	{
		if (this != &_Right) // different, move it
		{	
			Clear();
			swap(_Right);
		}
		return (*this);
	}

	self_type& operator= (initializer_list<value_type> il)
	{
		this->clear();
		this->insert(il);
		return (*this);
	}


	void Clear() noexcept	//recursive deletion 
	{
		if(root != nullptr)
		{
			_Erase(root);
			root = nullptr;
		}
		_size = 0;
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
		bool isInserted = false;
		node<T>* where_ = nullptr;
		root = _insert(root, val,where_, isInserted);
		root->IsRed = false;
		_size++;
		return std::pair<iterator, bool>(iterator(where_, root), isInserted);
	}

	pair<iterator, bool> insert(value_type&& val)
	{
		bool isInserted = false;
		node<T>* where_ = nullptr;
		root = _insert(root, val, where_, isInserted);
		root->IsRed = false;
		_size++;
		return std::pair<iterator, bool>(iterator(where_,root), isInserted);
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
	pair<iterator, bool> emplace(Args&&... args)
	{
		node<T>* _Newnode = createNode(std::forward<Args>(args)...);
		root = _insert(root,_Newnode->data,_Newnode);
		_size++;
		return std::make_pair<iterator, bool>(iterator(_Newnode, root), find(_Kfn(_Newnode->data)) != end());
	}


	iterator erase(const_iterator position)
	{
		auto valueCopy = *position;
		root = erase(root, *position);
		_size--;
		if (root != nullptr)
			root->IsRed = false;
		return upper_bound(_Kfn(valueCopy));
	}
	
	unsigned long erase(const key_type& val)
	{
		auto _Where = equal_range(val);
		unsigned long _Num =  std::distance(_Where.first, _Where.second);
		erase(_Where.first, _Where.second);
		return (_Num);

	}
	iterator  erase(const_iterator first, const_iterator last)		
	{
		if (first == begin() && last == end())
		{	// erase all
			Clear();
			return (begin());
		}
		else
		{	// partial erase, one at a time
			if(!multi)
			{
				while (first != last)
					erase(first++);
			}
			else
			{
				throw std::exception("Not implemented - LLRB are not designed for multivalues");
				//auto it = find(_Kfn(*first)); //should be head of subtree with same values
				//_Erase(it.ptr_);  //not working throwing some errors
			}
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



	const_iterator find(const key_type& val) const
	{
		//return lower_bound(val);
		node<T>* temp = root;
		while (temp != nullptr)
		{
			if (!(cmp((val), _Kfn(temp->data))) && !(cmp(_Kfn(temp->data), (val))))
			{
				return const_iterator(temp, root);
			}
			if (cmp((val), _Kfn(temp->data)))
				temp = temp->Left;
			else
				temp = temp->Right;
		}
		return const_iterator(nullptr, root);
	}



	iterator find(const key_type& data)
	{
		//return lower_bound(data);
		node<T>* temp = root;
		while (temp != nullptr)
		{
			if (!(cmp((data), _Kfn(temp->data))) && !(cmp(_Kfn(temp->data), (data))))
			{
				return iterator(temp, root);
			}
			if (cmp((data), _Kfn(temp->data)))
				temp = temp->Left;
			else
				temp = temp->Right;
		}
		return iterator(nullptr, root);
	}


//Compile print tree to console only for debug build
#ifdef _DEBUG
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
#endif // DEBUG
	

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
		return (_size == 0);
	}


	unsigned long count(const key_type& val) 
	{
		auto _Ans = equal_range(val);
		return (std::distance(_Ans.first, _Ans.second));
	}

	unsigned long max_size() const noexcept
	{
		return al.max_size();
	}


	iterator lower_bound(const key_type& val)
	{
		return iterator(_Lbound(val, T()), root);
	}
	const_iterator lower_bound(const key_type& val) const
	{
		return const_iterator(_Lbound(val, T()), root);
	}

	iterator upper_bound(const key_type& val)
	{
		return iterator(_Ubound(val, T()), root);
	}
	const_iterator upper_bound(const key_type& val) const
	{
		return const_iterator(_Ubound(val, T()), root);
	}

	
	pair<const_iterator, const_iterator> equal_range(const key_type& val) const
	{
		node<T>* Hi = _Ubound(val, T());
		node<T>* Lo = _Lbound(val, T());
		return make_pair<const_iterator, const_iterator>(const_iterator(Lo, root), const_iterator(Hi, root));
	}
	
	pair<iterator, iterator> equal_range(const key_type& val)
	{
		node<T>* Hi = _Ubound(val, T());
		node<T>* Lo = _Lbound(val, T());
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



private:
	Compare cmp;
	Alloc al;
	node<T>* root;
	unsigned int _size;




	template<class T, class key_type>
	node<T>* _Lbound(const key_type& _Keyval, T empty)  // find leftmost node not less than _Keyval
	{	
		node<T>* tmp = root;
		node<T>* _Wherenode = nullptr;	// end() if search fails

		while (tmp)
			if (cmp(_Kfn(tmp->data), _Keyval))
				tmp =  tmp->Right;	// descend right subtree
			else
			{	// tmp not less than _Keyval, remember it
				_Wherenode = tmp;
				tmp = tmp->Left;	// descend left subtree
			}

		return (_Wherenode);	// return best remembered candidate
	}

	template<class T, class key_type>
	node<T>* _Ubound(const key_type& _Keyval, T empty) 
		// find leftmost node greater than _Keyval
	{	
		node<T>* tmp = root;
		node<T>* _Wherenode = nullptr;	// end() if search fails

		while (tmp)
			if (cmp(_Keyval, _Kfn(tmp->data)))
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
			a.construct(std::addressof(temp->Left), nullptr);
			a.construct(std::addressof(temp->Right), nullptr);
			a.construct(std::addressof(temp->Parent), nullptr);
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
		a.destroy(std::addressof(free->data));			//TODO test memory leaks
		a.destroy(free->Left);
		a.destroy(free->Right);
		a.destroy(free->Parent);
		a.deallocate(free, 1);
	}



	template<typename T>
	node<T>* _insert(node<T>* h, T data, node<T>*& where_, bool& isInserted)
	{
		if (h == nullptr)
		{
			isInserted = true;
			where_ = createNode(data);
			return where_;
		}

		if (!multi)
		{
			if (cmp(_Kfn(h->data), _Kfn(data)))
			{
				h->Right = _insert(h->Right, data, where_, isInserted);
				h->Right->Parent = h;
			}
			else if (cmp(_Kfn(data), _Kfn(h->data)))
			{
				h->Left = _insert(h->Left, data, where_, isInserted);
				h->Left->Parent = h;
			}
			else
			{
				where_ = h;
				return h;
			}
		}
		else
		{
			if (cmp(_Kfn(h->data), _Kfn(data)))
			{
				h->Right = _insert(h->Right, data, where_, isInserted);
				h->Right->Parent = h;
			}
			else
			{
				h->Left = _insert(h->Left, data, where_, isInserted);
				h->Left->Parent = h;
			}
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
	node<T>* _insert(node<T>* h, T data, node<T>* node)
	{
		if (h == nullptr)
			return  node;

		if (cmp(_Kfn(h->data), _Kfn(data)))
		{
			h->Right = _insert(h->Right, data, node);
			h->Right->Parent = h;
		}
		else
		{
			h->Left = _insert(h->Left, data, node);
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

	//recursion deletion of tree
	void _Erase(node<T>* Rootnode)
	{
		for (node<T>* tmp = Rootnode; tmp != nullptr; Rootnode = tmp)
		{	// free subtrees, then node
			_Erase(tmp->Right);
			tmp = tmp->Left;
			destroyNode(Rootnode);
		}
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
		if(h != nullptr)
		{
			h->IsRed = !h->IsRed;
			if(h->Left != nullptr)
				h->Left->IsRed = !h->Left->IsRed;
			if(h->Right != nullptr)
				h->Right->IsRed = !h->Right->IsRed;
		}
	}


	template<typename T>
	node<T>* erase(node<T>* h, T data)
	{
		if (cmp(_Kfn(data), _Kfn(h->data)))			//operator <
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
		if(h->Right != nullptr)
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
		if(h->Left != nullptr)
		if (IsRed(h->Left->Left))
		{
			h = rotateRight(h);
			flipColors(h);
		}
		return h;
	}

	template<typename T>
	inline bool IsRed(node<T>* h)
	{
		return h == nullptr ? false : h->IsRed;
	}

	virtual  key_type _Kfn(value_type _Val) = 0;
};

#endif // !LLRB_H

