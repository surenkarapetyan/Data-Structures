#ifndef LINKED_LIST
#define LINKED_LIST

template<class T>
class list_node
{
public:
	int data;
	list_node<T>* next;
	list_node(); 
	list_node(const T & );
};

template<class T>
class list
{
private:
	list_node<T>* head;
	list_node<T>* tail;
	size_t size;

public:
	list();		  
	list(const list &);
	list(list && );
	list& operator=(const list &);
	list& operator=(list &&);
	void dispay();
	void push(const T &);
	void list_destroy();
	void get_list_size();
	list_node<T>* get_head();
	list_node<T>* get_tail();
	bool empty();
	~list();
};

#endif
