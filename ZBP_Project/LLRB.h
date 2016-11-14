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
class LLRB
{
public:
	LLRB();
	~LLRB();


	template<typename T>
	void insert(T data)
	{
		root = insert(root, data);
		root->IsRed = false;
	}


	template<typename T>
	node<T>* rotateLeft(node<T>* h)
	{
		auto x = h->Right;
		h->Right = x->Left;

		if(h->Right)
			h->Right->Parent = h;

		x->Left = h;
		x->IsRed = h->IsRed;
		h->IsRed = true;

		x->Parent = h->Parent;
		h->Parent = x;

		return x;
	}

	template<typename T>
	node<T>* rotateRight(node<T>* h)
	{
		auto x = h->Left;
		h->Left = x->Right;

		if (h->Left)
			h->Left->Parent = h;

		x->Right = h;
		x->IsRed = h->IsRed;
		h->IsRed = true;

		h->Parent = x->Parent;
		x->Parent = h;

		return x;
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
		root->IsRed = false;
	}

	node<T>* findMin(node<T>* h)
	{
		node<T>* temp = h;
		while (temp->Left)
			temp = temp->Left;
		return temp;
	}


private:
	node<T>* root;



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
				h->data = findMin(h->Right)->data; //---------------------------------???????
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
