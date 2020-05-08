#include<iostream>
#include<cassert>
#include"queue.hpp"

template<class T>
queue_node<T>::queue_node() : data(0),
			   next(nullptr),
			   prev(nullptr)
{

}

template<class T>
queue_node<T>::queue_node(const T & data) : data(data),
							   next(nullptr),
							   prev(nullptr)
{

}

template<class T>
queue<T>::queue() : front(nullptr),
				 rear(nullptr),
				 size(0)
{
	
}

template<class T>
queue<T>::queue(const queue & other) : size(other.size)
{
	if(!other.front){
		front = rear = nullptr;
		size = 0;
	} else {
		queue_node<T>* ptr = other.front;
		queue_node<T>* tmp = front = rear = new queue_node<T>(ptr->data);
		ptr = ptr->next;
		while(ptr) {
			tmp->next = rear = new queue_node<T>(ptr->data);
			rear->prev = tmp;
			tmp = rear;
			ptr = ptr->next;
		}
	}
}

template<class T>
queue<T>::queue(queue && other) : front(other.front),
							   rear(other.rear),
							   size(other.size)
{
	other.front = nullptr;
    other.rear  = nullptr;
    other.size  = 0;
}

template<class T>
queue<T>& queue<T>::operator=(const queue & other)
{
	if(this != &other && other.front) {
		queue_node<T>* ptr = other.front;
		for(int i = 0; i < other.size; ++i) {
			enqueue(ptr->data);
			ptr = ptr->next;
		}
		size += other.size;
	}
	return *this;
}

template<class T>
queue<T>& queue<T>::operator=(queue && other)
{
	if(this != &other) {
		queue_destroy(front);
		front = other.front;
		rear  = other.rear;
		size  = other.size;
		other.front = nullptr;
		other.rear  = nullptr;
		size = 0;
	}
	return *this;
}

template<class T>
void queue<T>::enqueue(const T & data)
{
	if(!front) {
		front = rear = new queue_node<T>(data);
		++size;
		return;
	}

	if(front == rear) {
		rear = new queue_node<T>(data);
		rear->prev = front;
		rear->next = nullptr;
		front->next = rear;
		++size;
		return;
	}
	
	queue_node<T>* ptr = rear;
	rear = new queue_node<T>(data);
	rear->prev = ptr;
	rear->next = nullptr;
	ptr->next = rear;
	++size;
	return;
}

template<class T>
T queue<T>::dequeue()
{
	assert(front && "Your Queue is empty\n");
	
	T tmp = front->data;
	
	if(!front->next) {
		delete front;
		front = nullptr;
		rear  = nullptr;
		--size;
		return tmp;
	}

	queue_node<T>* ptr = front;
	front = front->next;
	front->prev = nullptr;
	--size;
	delete ptr;
	return tmp;
}

template<class T>
void queue<T>::display_front() {
	if(!front) {
		std::cout << "Your queue is empty" << std::endl;
		return;
	} else {
		queue_node<T>* tmp = front;
		while(tmp) {
			std::cout << tmp->data << ' ';
			tmp = tmp->next;
		}
		std::cout << std::endl;
	}
}

template<class T>
void queue<T>::display_top()
{
	if(!front) {
		std::cout << "Your queue is empty" << std::endl;
		return;
	} else {
		std::cout << front->data << std::endl;
		return;
	}

}

template<class T>
void queue<T>::display_size()
{
	std::cout << "Your size is: " << size << std::endl;
}

template<class T>
void queue<T>::queue_destroy(queue_node<T>* ptr) {
	if(ptr){
		queue_node<T>* tmp = ptr;
		while(ptr) {
			ptr = ptr->next;
			delete tmp;
			tmp = ptr;
		}
		rear = nullptr;
	}
}

template<class T>
queue<T>::~queue()
{
	queue_destroy(front);
}
