#include<iostream>
#include<cassert>
#include"binary_search_tree.hpp"

template<class T>
bin_node<T>::bin_node() : data(0),
               left(nullptr),
               right(nullptr)
{
}

template<class T>
bin_node<T>::bin_node(T data) : data(data),
					   left(nullptr),
					   right(nullptr)
{
}

template<class T>
bst<T>::bst() : root(nullptr)		 
{
}

template<class T>
bin_node<T>* bst<T>::copy(const bin_node<T> * ptr)
{
	if(!ptr) return nullptr;
	bin_node<T> *copy_ptr = new bin_node<T>();
	copy_ptr->data = ptr->data;
	copy_ptr->left = copy(ptr->left);
	copy_ptr->right = copy(ptr->right);
	return copy_ptr;
}

template<class T>
bst<T>::bst(const bst & other)
{
	root = copy(other.root);
}

template<class T>
bst<T>::bst(bst && other)
{
	root = other.root;
	other.root = nullptr;
}

template<class T>
bst<T>& bst<T>::operator=(const bst & other)
{
	if(this != &other) {
		destroy_tree(root);
		root = copy(other.root);
	}
	return *this;
}

template<class T>
bst<T>& bst<T>::operator=(bst && other)
{
	if(this != &other) {
		destroy_tree(root);
		root = other.root;
		other.root = nullptr;
	}
	return *this;
}

template<class T>
T& bst<T>::get_max_el(bin_node<T> * leaf)
{
	assert(leaf && "Your pointer argument is nullptr\n");
	while(leaf->right != nullptr) {
		leaf = leaf->right;
	}
	return leaf->data;
}

template<class T>
T& bst<T>::get_min_el(bin_node<T> * leaf)
{
	assert(leaf && "Your pointer argument is nullptr\n");
	while(leaf->left != nullptr) {
		leaf = leaf->left;
	}
	return leaf->data;
}

template<class T>
bin_node<T>* bst<T>::delete_node(bin_node<T> * leaf, int k)
{
	if(!leaf) return leaf;

	if(leaf->data > k) {
		leaf->left = delete_node(leaf->left, k);
		return leaf;
	} else if(leaf->data < k) {
		leaf->right = delete_node(leaf->right, k);
		return leaf;
	}

	if(leaf->left == nullptr) {
		bin_node<T> * temp = leaf->right;
		delete leaf;
		return temp;
	} else if(leaf->right == nullptr) {
		bin_node<T> * temp = leaf->left;
		delete leaf;
		return temp;
	} else {
		bin_node<T>* parent = leaf;
		bin_node<T>* succ   = leaf->right;
		while(succ->left) {
			parent = succ;
			succ   = succ->left;
		}

		if(parent != leaf)
			parent->left  = succ->right;
		else 
			parent->right = succ->right;

		leaf->data = succ->data;

		delete succ;
		return leaf;
	}
}

template<class T>
bst<T>::~bst()
{
	destroy_tree();
}

template<class T>
void bst<T>::destroy_tree()
{
	destroy_tree(root);
}

template<class T>
void bst<T>::destroy_tree(bin_node<T> * leaf)
{
	if(leaf) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
		leaf = nullptr;
	}
}

template<class T>
void bst<T>::insert(T data)
{
	insert(data, root);
}

template<class T>
void bst<T>::search(T element)
{
	int level = 0;
	bin_node<T> * temp = new bin_node<T>();
	temp = root;
	while(temp) {
		++level;
		if(temp->data == element) {
			std::cout << "There is an element: " << element 
					  << " in level: " << level << std::endl;
			return;
		} else if(element < temp->data) {
			temp = temp->left;
		} else {
			temp = temp->right;
		}
	}
	std::cout << "There is no element" << std::endl;
	return;
}

template<class T>
void bst<T>::insert(T data, bin_node<T> * & leaf)
{
	if(!leaf) {
		leaf = new bin_node<T>(data);
		return;
	}

	if(data >= leaf->data){
		insert(data, leaf->right);
	} else {
		insert(data, leaf->left);
	}
	
	return;
}

template<class T>
void bst<T>::preorder(bin_node<T> *ptr)
{
	if(!ptr) return;

	std::cout << ptr->data << ' ';

	preorder(ptr->left);
	preorder(ptr->right);
}

template<class T>
void bst<T>::postorder(bin_node<T> *ptr)
{
	if(!ptr) return;

	postorder(ptr->left);
	postorder(ptr->right);

	std::cout << ptr->data << ' ';
}

template<class T>
void bst<T>::inorder(bin_node<T> *ptr)
{
	if(!ptr) return;

	inorder(ptr->left);
	
	std::cout << ptr->data << ' ';
	
	inorder(ptr->right);
}
