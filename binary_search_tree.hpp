#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template<class T>
struct bin_node
{
	bin_node();
	bin_node(T);
	T data;
	bin_node *left, *right;
};

template<class T>
class bst 
{
public:
	bin_node<T> *root;
	bst();
	bst(const bst &);
	bst(bst&&);
	bst& operator=(const bst &);
	bst& operator=(bst&&);
	bin_node<T> * copy(const bin_node<T>*);
	bin_node<T> * delete_node(bin_node<T>* ,int);
	~bst();
	T& get_min_el(bin_node<T>* );
	T& get_max_el(bin_node<T>* );
	void insert(T );
	void destroy_tree();
	void inorder(bin_node<T>* );
	void preorder(bin_node<T>* );
	void postorder(bin_node<T>* );
	void search(T );
private:
	void destroy_tree(bin_node<T>* );
	void insert(T ,bin_node<T>*& );
};

#endif
