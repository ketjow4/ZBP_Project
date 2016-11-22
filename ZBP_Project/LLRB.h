#ifndef LLRB_H
#define LLRB_H

#include <iostream>
#include <iomanip>

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


template<typename T>
class iteratorLLRB : public iteratorLLRB<bidirectional_iterator_tag>
{
	typedef  iteratorLLRB<T> self_type;
	typedef bidirectional_iterator_tag iterator_category;
	typedef int difference_type;
	//typedef size_t size_type;
	typedef T value_type;
	typedef T * pointer;
	typedef T & reference;
	typedef node<T>*  nodePtr;

	iteratorLLRB(nodePtr ptr) : ptr_(ptr) { }

	self_type operator++() { self_type i = *this; ptr_->next(); return i; }
	self_type operator++(int) { ptr_->next(); return *this; }
	reference operator*() { return *ptr_->data; }
	pointer operator->() { return ptr_; }
	bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
	bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
private:
	nodePtr ptr_;
};


template<typename T>
class LLRB
{
public:
	LLRB();
	~LLRB();


	friend class iteratorLLRB<T>;


	template<typename T>
	void insert(T data)
	{
		root = insert(root, data);
		root->IsRed = false;
	}


	template<typename T>
	node<T>* rotateLeft(node<T>* a)
	{
		auto b = a->Right;

		if(a->Right = b->Left)
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
	void erase(T data)
	{
		root = erase(root, data);
		if(root != nullptr)
			root->IsRed = false;
	}

	template<typename T>
	T search(T data)
	{
		node<T> temp = root;
		while (temp != nullptr)
		{
			if (!(data > temp.data) && !(temp.data > data))
			{
				return temp.data;
			}
			if (data > temp.data)
				temp = temp.Left;
			else
				temp = temp.Right;
		}
		return nullptr;
	}


	friend ostream& operator<<(ostream& out, LLRB& tree)
	{
		postorder(out, tree.root, 0);
		return out;
	}

	template<typename T>
	friend void postorder(ostream& out, node<T>* p, int indent = 0)
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


	template<typename T>
	node<T>* deleteMin()
	{
		root = deleteMin(root);
		if(root)
			root->IsRed = false;
	}

	template<typename T>
	node<T>* findMin(node<T>* h)
	{
		node<T>* temp = h;
		while (temp->Left)
			temp = temp->Left;
		return temp;
	}

	template<typename T>
	node<T>* next(node<T>* h)
	{
		if (h->Right != nullptr)
		{
			h = h->Right;
			while (h->Left)		//it is find min function
			{
				h = h->Left;
			}
			return h;
		}
		node<T>* y = h->Parent;
		while (y != nullptr && h == y->Right)
		{
			h = y;
			y = y->Parent;
		}
		return y;
	}

	node<T>* root;
private:
	



	template<typename T>
	node<T>* insert(node<T>* h, T data)
	{
		if (h == nullptr)
			return new node<T>(data);

		if (data > h->data)
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
		if (data < h->data)
		{
			if (!IsRed(h->Left) && !IsRed(h->Left->Left))
				h = moveRedLeft(h);
			h->Left = erase(h->Left, data);
		}
		else
		{
			if (IsRed(h->Left))
				h = rotateRight(h);
			if (data == h->data && h->Right == nullptr)
			{
				delete h;
				return nullptr;
			}
			if (!IsRed(h->Right) && !IsRed(h->Right->Left))
				h = moveRedRight(h);
			if (data == h->data)
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

template<typename T>
inline LLRB<T>::LLRB()
{
	root = nullptr;
}

template<typename T>
inline LLRB<T>::~LLRB()
{
	delete root;
}
