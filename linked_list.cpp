#include<iostream>
#include"linked_list.hpp"

template<class T>
list_node<T>::list_node() : data(0),
				  next(nullptr)
{
}

template<class T>
list_node<T>::list_node(const T & data) : data(data),
								  next(nullptr)
{
}

template<class T>
list<T>::list() : head(nullptr),
				  tail(nullptr),
				  size(0)
{
}

template<class T>
list<T>::list(const list & other) : size(other.size)
{
	if(other.head){
		list_node<T>* tmp = other.head;
		list_node<T>* ptr; 
		ptr = head = tail = new list_node<T>(tmp->data);
		tmp = tmp->next;
		while(tmp) {
			tail = new list_node<T>(tmp->data);
			ptr->next = tail;
			ptr = tail;
			tmp = tmp->next;
		}
	} else {
		head = tail = nullptr;
	}
}

template<class T>
list<T>::list(list && other) : head(other.head),
							   tail(other.tail),
							   size(other.size)
{
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}

template<class T>
list<T>& list<T>::operator=(const list & other)
{
	if(this != &other && other.head) {
		list_node<T>* tmp = other.head;
		list_node<T>* ptr = tail;
		tail = new list_node<T>(tmp->data);
		if(!ptr) {
			ptr = head = tail;
		} else {
			ptr->next = tail;
			ptr = ptr->next;
		}
		tmp = tmp->next;
		while(tmp) {
			tail = new list_node<T>(tmp->data);
			ptr->next = tail;
			ptr = ptr->next;
			tmp = tmp->next;
		}
		size += other.size;
	}

	return *this;

}

template<class T>
list<T>& list<T>::operator=(list && other)
{
	list_destroy();
	head = other.head;
	tail = other.tail;
	size = other.size;
	other.head = nullptr;
	other.tail = nullptr;
	other.size = 0;
}

template<class T>
list_node<T>* list<T>::get_head()
{
	return head;
}

template<class T>
list_node<T>* list<T>::get_tail()
{
	return tail;
}

template<class T>
void list<T>::dispay()
{
	list_node<T>* ptr = head;
	while(ptr != nullptr) {
		std::cout << ptr->data << ' ';
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

template<class T>
void list<T>::push(const T & data)
{
	list_node<T>* tmp = new list_node<T>(data);

	if(!head) {
		head = tmp;
		tail = tmp;
		tmp = nullptr;
	} else {
		tail->next = tmp;
		tail = tmp;
	}

	++size;
}

template<class T>
void list<T>::get_list_size()
{
	std::cout << "Your size of list is :" << size << std::endl;
}

template<class T>
bool list<T>::empty()
{
	return (!head);
}

template<class T>
void list<T>::list_destroy()
{
	if(!empty()) {
		list_node<T>* temp = head;
		while(temp) {
			list_node<T>* ptr = temp;
			temp = temp->next;
			delete ptr;
		}
		head = tail = nullptr;
	}
}

template<class T>
list<T>::~list()
{
	list_destroy();
}
