#ifndef QUEUE
#define QUEUE

template<class T>
struct queue_node
{
	T data;
	queue_node<T>* next;
	queue_node<T>* prev;
	queue_node<T>();
	queue_node<T>(const T &);
};

template<class T>
class queue
{
public:
	queue();
	queue(const queue &);
	queue(queue &&);
	queue& operator=(const queue &);
	queue& operator=(queue &&);
	void display_front();
	void display_top();
	void display_size();
	void enqueue(const T & );
	T dequeue();
	~queue();
private:
	void destroy(queue_node<T>*);
	queue_node<T>* front;
	queue_node<T>* rear;
	size_t size;
};

#endif
