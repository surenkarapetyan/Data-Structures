#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

template<class T>
class dynamic_array 
{
private:
	T *_ptr;
	size_t _size;

public:
	dynamic_array();
	dynamic_array(const size_t&);
	dynamic_array(const dynamic_array&);
	dynamic_array(dynamic_array&&);
	dynamic_array& operator=(const dynamic_array&);
	dynamic_array& operator=(dynamic_array&&);
	T& operator[](const size_t&);
	void print();
	bool find(const T&);
	void push(const T&);
	T pop();
	void resize(const size_t&);
	void concat_arr(const dynamic_array&);
	void get_size();
	~dynamic_array();	
};

#endif
