#include<iostream>
#include<limits>
#include<stdexcept>
#include<exception>
#include"dynamic_array.hpp"

template<class T>
dynamic_array<T>::dynamic_array() : _ptr(nullptr),
   									_size(0)
{
}

template<class T>
dynamic_array<T>::dynamic_array(const size_t & size) : _size(size)
{
	if(!size) {
		_ptr = nullptr;
	} else {		
		_ptr = new T[_size];

		for(size_t i = 0; i < _size; ++i) {
			_ptr[i] = 0;
		}
	}
}

template<class T>
dynamic_array<T>::dynamic_array(const dynamic_array & other) : _size(other._size)
{
	if(!_size) {
		_ptr = nullptr;	
	} else {
		_ptr = new T[_size];
		for(size_t i = 0; i < _size; ++i) {
			_ptr[i] = other._ptr[i];
		}
	}
}

template<class T>
dynamic_array<T>::dynamic_array(dynamic_array && other) : _size(other._size)
													   
{
	(!_size) ? _ptr = nullptr : _ptr = other._ptr;
	other._ptr  = nullptr;
	other._size = 0;
}

template<class T>
dynamic_array<T>& dynamic_array<T>::operator=(const dynamic_array & other)
{
	if(this != &other) {
		if(_size < other._size) {
			delete[] _ptr;
			_size = other._size;
			_ptr = new T[_size];
			for(size_t i = 0; i < _size; ++i) {
				_ptr[i] = other._ptr[i];
			}
		} else {
			for(size_t i = 0; i < other._size; ++i) {
				_ptr[i] = other._ptr[i];
			}
		}
	}
	return *this;
}

template<class T>
dynamic_array<T>& dynamic_array<T>::operator=(dynamic_array && other)
{
	if(this != &other) { 
		delete[] _ptr;
		_size = other._size;
		_ptr  = other._ptr;
		other._ptr  = nullptr;
		other._size = 0;
	}
	return *this;
}

template<class T>
T& dynamic_array<T>::operator[](const size_t & index)
{	
	try 
	{
		if(index > _size || _ptr == nullptr) {
			throw std::out_of_range("Invalid index of array");
		}
	}
	catch(const std::out_of_range& index)
	{
		std::cerr << index.what() << std::endl;
		exit(0);
	}
	
	return _ptr[index];
	
}

template<class T>
void dynamic_array<T>::print()
{
	std::cout << "elements of array:\n";
	for(size_t i = 0; i < _size; ++i)
		std::cout << _ptr[i] << ' ';
	std::cout << std::endl;
}

template<class T>
void dynamic_array<T>::resize(const size_t & size)
{
	if(size == _size) return;

	if(!size) {
		delete[] _ptr;
		_ptr  = nullptr;
		_size = 0;
		return;
	}

	_size = size;
	
	if(_ptr == nullptr) {
		_ptr = new T[_size];
	} else { 
		T *ptr = _ptr;
		_ptr = new T[_size];
		for(size_t i = 0; i < _size; ++i) {
			_ptr[i] = ptr[i];
		}
		delete[] ptr;
	}
}

template<class T>
void dynamic_array<T>::concat_arr(const dynamic_array & other)
{
	T *ptr = _ptr;
	size_t new_size = _size + other._size;
	_ptr = new T[new_size];

	for(size_t i = 0,j = 0; i < new_size & j < other._size; ++i) {
		if(i < _size) {
			_ptr[i] = ptr[i];
		} else {
			_ptr[i] = other._ptr[j];
			++j;
		}
	}

	_size = new_size;
	delete[] ptr;
}

template<class T>
void dynamic_array<T>::push(const T& element)
{
	if(!_size) {
		++_size;
		_ptr = new T[_size];
		_ptr[0] = element;
		return;
	}

	T *ptr = _ptr;
	++_size;
	_ptr = new T[_size];
	for(int i = 0; i < _size - 1; ++i) {
		_ptr[i] = ptr[i];
	}
	_ptr[_size - 1] = element;
	delete[] ptr;
	return;
}

template<class T>
T dynamic_array<T>::pop()
{
	try
	{
		if(!_size) throw std::length_error("You can`t pop empty array"); 
	}
	catch(const std::length_error & p)
	{
		std::cerr << p.what() << std::endl;
		exit(0);
	}
	
	T element = _ptr[_size - 1];
	--_size;

	if(!_size) {
		delete[] _ptr;
		_ptr = nullptr;
		return element;
	}

	T *ptr = _ptr;
	_ptr = new T[_size];
	for(int i = 0; i < _size; ++i) {
		_ptr[i] = ptr[i];
	}
	delete[] ptr;
	return element;
}

template<class T>
bool dynamic_array<T>::find(const T& element)
{
	for(int i = 0; i < _size; ++i) {
		if(_ptr[i] == element) return true;
	}
	
	return false;
}

template<class T>
void dynamic_array<T>::get_size()
{
	std::cout << "your array size is: " << _size << std::endl;
}

template<class T>
dynamic_array<T>::~dynamic_array()
{
	delete[] _ptr;
	_ptr = nullptr;
}
