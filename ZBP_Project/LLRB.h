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

	node*   Left;
	node*   Right;
	node*	Parent;

	node(T data) : data(data), IsRed(true)
	{
		Parent = Left = Right = nullptr;
	}

	node() : IsRed(true)
	{
		//data = nullptr;
	}
};

template<typename T, class Compare = less<T> >
class LLRB;

template<typename T>
struct ItWrap
{
	typedef typename int difference_type;
	typedef typename T value_type;
	typedef typename const T * pointer;
	typedef typename const T & reference;
};

template<class T>		//, class _Base = _Iterator_base0
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

private:
	nodePtr ptr_;
	nodePtr root;
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

	iteratorLLRB(nodePtr ptr, nodePtr root) : base_type(ptr,root)   { }

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



template<typename T, class Compare = less<T> >
class LLRB
{
public:

	LLRB<T, Compare>::LLRB()
	{
		root = nullptr;
	}

	LLRB<T, Compare>::~LLRB()
	{
		delete root;
	}


	friend class iteratorLLRB<T>;
	friend class const_iteratorLLRB<T>;


	typedef typename T value_type;
	typedef typename iteratorLLRB<T> iterator;
	typedef typename const_iteratorLLRB<T> const_iterator;
	typedef typename std::reverse_iterator<iteratorLLRB<T>> reverse_iterator;
	typedef typename std::reverse_iterator<const_iteratorLLRB<T>> const_reverse_iterator;

	iteratorLLRB<T> begin()
	{
		return iteratorLLRB<T>(findMin(root),root);
	}

	iteratorLLRB<T> end()
	{
		return iteratorLLRB<T>(nullptr,root);
	}

	const_iteratorLLRB<T> cbegin()
	{
		return const_iteratorLLRB<T>(findMin(root), root);
	}

	const_iteratorLLRB<T> cend()
	{
		return const_iteratorLLRB<T>(nullptr, root);
	}

	reverse_iterator rbegin()
	{
		return  reverse_iterator(iteratorLLRB<T>(nullptr, root));;
	}

	reverse_iterator rend()
	{
		return reverse_iterator(iteratorLLRB<T>(findMin(root), root));;
	}

	const_reverse_iterator crbegin()
	{
		return  const_reverse_iterator(const_iteratorLLRB<T>(nullptr, root));;
	}

	const_reverse_iterator crend()
	{
		return const_reverse_iterator(const_iteratorLLRB<T>(findMin(root), root));;
	}

	template<typename T>
	void insert(T data)
	{
		root = insert(root, data);
		root->IsRed = false;
	}

	template<typename T>
	iterator insert(iterator it, T data)
	{
		root = insert(root, data);
		root->IsRed = false;
		return find(data);
	}

	template<typename T>
	void erase(T data)
	{
		root = erase(root, data);
		if(root != nullptr)
			root->IsRed = false;
	}


	template<typename T>
	iterator find(T data)
	{
		node<T>* temp = root;
		while (temp != nullptr)
		{
			if (!(cmp(data, temp->data)) && !(cmp(temp->data ,data)))
			{
				return iterator(temp, root);
			}
			if (cmp(data ,temp->data))
				temp = temp->Left;
			else
				temp = temp->Right;
		}
		return iterator(nullptr, root);;
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
	static node<T>* findMin(node<T>* h)
	{
		if (h != nullptr)
		{
			node<T>* temp = h;
			while (temp->Left)
				temp = temp->Left;
			return temp;
		}
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
	}

	node<T>* root;
private:
	Compare cmp;


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
			return new node<T>(data);

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
		if (cmp(h->data,data))			//operator <
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
				delete h;
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
			delete h;
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

