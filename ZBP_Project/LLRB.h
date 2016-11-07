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

	}

	template<typename T>
	node<T> rotateRight(node<T> h)
	{

	}

	template<typename T>
	void flipColors(node<T> h)
	{

	}

	template<typename T>
	void erase(T data)
	{

	}

	template<typename T>
	T search(T data)
	{

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

