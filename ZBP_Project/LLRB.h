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

template<typename T, class Compare = less<T>, class Alloc = allocator<T> >
class LLRB;

template<typename T>
struct ItWrap
{
	typedef typename int difference_type;
	typedef typename T value_type;
	typedef typename const T * pointer;
	typedef typename const T & reference;
};

template<class T>		
class const_iteratorLLRB
	: public iterator<bidirectional_iterator_tag,
	typename ItWrap<T>::value_type,
	typename ItWrap<T>::difference_type,
	typename ItWrap<T>::pointer,
	typename ItWrap<T>::reference>
{
public:
	typedef  const_iteratorLLRB<T> self_type;
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
			ptr_ = LLRB<T>::findMax(root);
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
	nodePtr root;
private:
	
};



template<class T>
class iteratorLLRB : public const_iteratorLLRB<T>
{
public:
	typedef  iteratorLLRB<T> self_type;
	typedef  const_iteratorLLRB<T> base_type;
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



template<typename T, class Compare = less<T>, class Alloc = allocator<T> >
class LLRB
{
public:

	LLRB<T, Compare, Alloc>::LLRB()
	{
		_size = 0;
		root = nullptr;
	}

	//TODO Add constructors
	//template <class InputIterator>
	//set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& = allocator_type());
	//set(const set& x);
	//set(const set& x, const allocator_type& alloc);
	//set(set&& x);
	//set(set&& x, const allocator_type& alloc);
	//set(initializer_list<value_type> il, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());


	LLRB<T, Compare, Alloc>::~LLRB()
	{
		if (root != nullptr)
			Clear();
	}

	//TODO implement this!
	/*set& operator= (const set& x);
	set& operator= (set&& x);
	set& operator= (initializer_list<value_type> il);*/

	
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


	typedef typename LLRB<T, Compare, Alloc> self_type;
	typedef typename T value_type;
	typedef typename iteratorLLRB<T> iterator;
	typedef typename const_iteratorLLRB<T> const_iterator;
	typedef typename std::reverse_iterator<iteratorLLRB<T>> reverse_iterator;
	typedef typename std::reverse_iterator<const_iteratorLLRB<T>> const_reverse_iterator;

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



	/*pair<iterator, bool> insert(const value_type& val);
	pair<iterator, bool> insert(value_type&& val);
	template <class InputIterator>
	void insert(InputIterator first, InputIterator last);
	void insert(initializer_list<value_type> il);*/


	template<typename T>
	void insert(T data)
	{
		root = insert(root, data);
		root->IsRed = false;
		_size++;
	}

	template<typename T>
	iterator insert(iterator it, T data)
	{
		root = insert(root, data);
		root->IsRed = false;
		return find(data);
		_size++;
	}


	/*template <class... Args>
	pair<iterator, bool> emplace(Args&&... args);*/


	iterator  erase(const_iterator position)		//test
	{
		root = erase(root, *position);
		if (root != nullptr)
			root->IsRed = false;
		return position++;
	}
	unsigned long erase(const value_type& val)		//------------------should erase all values (multimap / multiset)---------------------------
	{
		//_Pairii _Where = equal_range(_Keyval);
		//size_type _Num = _STD distance(_Where.first, _Where.second);
		//erase(_Where.first, _Where.second);
		//return (_Num);
		root = erase(root, val);
		if (root != nullptr)
			root->IsRed = false;
		_size--;
		return _size;
	}
	iterator  erase(const_iterator first, const_iterator last)		//test but should work
	{
		if (first == begin() && last == end())
		{	// erase all
			clear();
			return (begin());
		}
		else
		{	// partial erase, one at a time
			while (first != last)
				erase(first++);
			return (iterator(first.ptr_, root);
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
			if (!(cmp(data, temp->data)) && !(cmp(temp->data, data)))
			{
				return iterator(temp, root);
			}
			if (cmp(data, temp->data))
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

	//TODO
	template<typename T>
	unsigned int count(const T& val) const
	{
		//equal range
	}


	unsigned long max_size() const noexcept
	{
		return al.max_size();
	}


	iterator lower_bound(const value_type& val)
	{

	}
	const_iterator lower_bound(const value_type& val) const
	{

	}

	iterator upper_bound(const value_type& val)
	{

	}
	const_iterator upper_bound(const value_type& val) const
	{

	}

	pair<const_iterator, const_iterator> equal_range(const value_type& val) const
	{

	}
	pair<iterator, iterator> equal_range(const value_type& val)
	{

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
	node<T>* insert(node<T>* h, T data)
	{
		if (h == nullptr)
			return  createNode(data);		//new node<T>(data);

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

	template<typename T>
	node<T>* erase(node<T>* h, T data)
	{
		if (cmp(h->data, data))			//operator <
		{
			if (!IsRed(h->Left) && !IsRed(h->Left->Left))
				h = moveRedLeft(h);
			h->Left = erase(h->Left, data);
		}
		else
		{
			if (IsRed(h->Left))
				h = rotateRight(h);
			if (!(cmp(data, h->data)) && !(cmp(h->data, data)) && h->Right == nullptr)
			{
				destroyNode(h);		//delete h;
				return nullptr;
			}
			if (!IsRed(h->Right) && !IsRed(h->Right->Left))
				h = moveRedRight(h);
			if (!(cmp(data, h->data)) && !(cmp(h->data, data)))
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
};

#endif // !LLRB_H

