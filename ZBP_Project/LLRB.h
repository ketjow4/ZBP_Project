#ifndef LLRB_H
#define LLRB_H


template<typename T>
struct node
{
	T data;
	bool    IsRed;

	node*   Left;
	node*   Right;

	node(T data) : data(data)
	{}
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

	}


	

	template<typename T>
	node<T> rotateLeft(node<T> h)
	{
		auto x = h.Right;
		h.Right = x.left;
		x.left = h;
		x.IsRed = h.IsRed;
		h.IsRed = true;
		return x;
	}

	template<typename T>
	node<T> rotateRight(node<T> h)
	{
		auto x = h.Left;
		h.Left = x.Right;
		x.Right = h;
		x.IsRed = h.IsRed;
		h.IsRed = true;
		return x;
	}

	template<typename T>
	void flipColors(node<T> h)
	{
		h.IsRed = !h.IsRed;
		h.Left.IsRed = !h.Left.IsRed;
		h.Right.IsRed = !h.Right.IsRed;
	}

	template<typename T>
	void erase(T data)
	{

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

private:
	node<T> root;



	template<typename T>
	void insert(node<T> h, T data)
	{

	}

	template<typename T>
	void erase(node<T> h, T data)
	{

	}

	template<typename T>
	node<T> moveRedLeft(node<T> h)
	{

	}

	template<typename T>
	node<T> moveRedRight(node<T> h)
	{

	}
};

template<typename T>
LLRB::LLRB()
{
}

template<typename T>
LLRB::~LLRB()
{
}

#endif // !LLRB_H

