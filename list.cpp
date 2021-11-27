#include<iostream>
#include<iomanip>
using namespace std;

template<typename T> class Node {
public:
	Node<T>* next_node;
	Node<T>* prev_node;
	T data;
public:
	Node() : next_node(nullptr), prev_node(nullptr) {}
	Node(Node<T>* t_prev_node, Node<T>* t_next_node = nullptr) : prev_node(t_prev_node), next_node(t_next_node) {}
};



template<typename S>
class List {
private:
	Node<S>* root_node;
	Node<S>* tail_node;
public:
	List() : root_node(nullptr), tail_node(nullptr) {}
	List(unsigned int list_size) { 
		if (list_size == 0) {
			root_node = nullptr;
			tail_node = nullptr;
		}
		else {
			root_node = new Node<S>();
			tail_node = new Node<S>();
			tail_node = root_node;
			Node<S>* temp_root_node = root_node;
			for (int i = 0; i < list_size - 1; i++) {
				Node<S>* temp_prev_node = root_node;
				root_node = root_node->next_node;
				root_node = new Node<S>();
				root_node->prev_node = temp_prev_node;
				temp_prev_node->next_node = root_node;
				tail_node = root_node;
			}
			root_node = temp_root_node;
		}
	}
	~List(){}

	S& operator [](unsigned int index);
	void append_to_list(S append_data);
	void preapppend_to_list(S append_data);
	void delete_last_elem();
	void delete_first_elem();
	void delete_data(S delete_data);
	bool is_in_list(S search_data);
	void clear();
	void reverse_show();
};



template<typename S>
S& List<S>:: operator [](unsigned int index){
	Node<S>* temp_root_node = this->root_node;
	for (int i = 0; i < index; i++) {
		temp_root_node = temp_root_node->next_node;
	}
	return temp_root_node->data;
}

template<typename S>
void List<S>::append_to_list(S append_data) {
	if (this->root_node == nullptr) {
		this->root_node = new Node<S>();
		this->tail_node = this->root_node;
		this->root_node->data = append_data;
		return;
	}
	Node<S>* temp_root_node = this->tail_node;
	Node<S>* append_node = new Node<S>();
	append_node->data = append_data;
	this->tail_node->next_node = append_node;
	append_node->prev_node = tail_node;
	this->tail_node = append_node;
}

template<typename S>
void List<S>::preapppend_to_list(S append_data) {
	if (this->root_node == nullptr) {
		this->root_node = new Node<S>();
		this->root_node->data = append_data;
		this->tail_node = this->root_node;
	}
	else {
		Node<S>* new_first_node = new Node<S>();
		new_first_node->data = append_data;
		new_first_node->next_node = this->root_node;
		this->root_node->prev_node = new_first_node;
		root_node = new_first_node;
	}
}

template<typename S>
void List<S>::delete_last_elem() {
	if (this->root_node == nullptr) {
		return;
	}
	else {
		if (this->tail_node->prev_node == nullptr) {
			this->root_node = nullptr;
			this->tail_node = nullptr;
		}
		else {
			Node<S>* temp_for_del_node = tail_node->prev_node;
			Node<S>* temp_for_delete = tail_node;
			temp_for_del_node->next_node = nullptr;
			tail_node = temp_for_del_node;
			temp_for_delete->next_node = nullptr;
			temp_for_delete->prev_node = nullptr;
		}
	}
}

template<typename S>
void List<S>::delete_first_elem() {
	if (this->root_node == nullptr) return;
	else {
		if (this->root_node->next_node == nullptr) {
			this->root_node = nullptr;
			this->tail_node = nullptr;
		}
		else {
			Node<S>* temp_for_del = this->root_node;
			this->root_node = this->root_node->next_node;
			this->root_node->prev_node = nullptr;
			temp_for_del->next_node = nullptr;
			temp_for_del->prev_node = nullptr;
		}
	}
}

template<typename S>
void List<S>::delete_data(S delete_data) {
	Node<S>* temp_root_node = this->root_node;
	if (this->root_node == nullptr) return;
	while (temp_root_node->data != delete_data) {
		if (temp_root_node == nullptr) return;
		temp_root_node = temp_root_node->next_node;
	}
	if (temp_root_node->data == delete_data) {
		if (temp_root_node->next_node == nullptr && temp_root_node->prev_node == nullptr) {
			this->clear();
			return;
		}
		if (temp_root_node->next_node == nullptr) {
			this->delete_last_elem();
			return;
		}
		if (temp_root_node->prev_node == nullptr) {
			this->delete_first_elem();
			return;
		}
		Node<S>* temp_next_node = temp_root_node->next_node;
		Node<S>* temp_prev_node = temp_root_node->prev_node;
		temp_next_node->prev_node = temp_prev_node;
		temp_prev_node->next_node = temp_next_node;
		temp_root_node->next_node = nullptr;
		temp_root_node->prev_node = nullptr;
	}
}

template<typename S>
bool List<S>::is_in_list(S search_data) {
	Node<S>* temp_root_node = this->root_node;
	while (temp_root_node != nullptr) {
		if (temp_root_node->data == search_data) {
			return true;
		}
		temp_root_node = temp_root_node->next_node;
	}
	return false;
}

template<typename S>
void List<S>::clear() {
	this->root_node = nullptr;
	this->tail_node = nullptr;
}

template<typename S>
void List<S>::reverse_show() {
	Node<S>* temp_tail_node = this->tail_node;
	while (temp_tail_node != nullptr) {
		cout << temp_tail_node->data << " ";
		temp_tail_node = temp_tail_node->prev_node;
	}
	cout << endl;
}
