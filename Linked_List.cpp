#include <iostream>
#include <string>
#include <chrono>
using namespace std;
class test_class {
public:
	string name;
	int key = 0;
	friend bool operator>(const test_class& klasa1, const test_class& klasa2)
	{
		return klasa1.key > klasa2.key;
	}
	friend bool operator<(const test_class& klasa1, const test_class& klasa2)
	{
		return klasa1.key < klasa2.key;
	}
	friend bool operator==(const test_class& klasa1, const test_class& klasa2)
	{
		return klasa1.key == klasa2.key;
	}
	friend ostream& operator<<(ostream& os, const test_class klasa1)
	{
		os << klasa1.key;
		return os;
	}
	test_class(int i)
	{
		key = i;
	}
	test_class(int i, string namee)
	{
		key = i;
		name = namee;
	}
	test_class()
	{
		name = "none";
		key = 0;
	}
};

//ostream& operator<<(ostream& os,const vampire& vamp )
//{
//	os << "Name: " << vamp.name << "\n		Blood_amt: " << vamp.blood_amt << endl;
//	return os;
//}
//nie udało mi się niestety przeładować << dla obiektu
//wypisuje adresy :c

template <typename T> class list_obj {
public:
	T* obj=new T;//w  razie potrzeby się przeładuje operator gdyby trzeba było porówanć obiekty np
	list_obj<T>* next=NULL;
	list_obj<T>* prev=NULL;
	~list_obj() {
		next = NULL;
		prev = NULL;
	}
};


template <typename T> class linked_list {
private:
	int size;
protected:
	list_obj<T>* head;
	list_obj<T>* tail;
public:
	void add_head(T *data);
	void add_tail(T* data);
	void add_at_index(T* data, int n);
	bool remove_head();
	bool remove_tail();
	void clear();
	bool remove_obj(int n);
	bool is_empty();
	bool is_index_ok(int i);
	list_obj<T>* find_by_index(int i);
	void change_data(int i, T* data);
	list_obj<T>* find_by_data(T* data);
	void print_list();
	linked_list()
	{
		head = NULL;
		tail = NULL;
		size = 0;
	}
};



template <typename T> void linked_list<T>::print_list()//opcjonalnie dorobić tu overload opcje.
{
	list_obj<T>* ptr = head;
	cout << "_______________________________________\n";
	while (ptr != NULL)
	{
		cout << (*ptr->obj) << endl;
		ptr = ptr->next;
	}
	
}

template <typename T> bool linked_list<T>::is_empty()//nie ma head i tail -> empty
{
	if (head == NULL && tail == NULL)
		return 1;
	else
		return 0;
}

template <typename T> bool linked_list<T>::is_index_ok(int i)//WAŻNE! musi być wywołana przed każdą operacją inputu indexu przez użytkownika.
{
	if (is_empty() == 0 && i <= size && i>=0)
		return 1;
	return 0;
	
}

template <typename T> list_obj<T>* linked_list<T>::find_by_data(T* data)
{
	list_obj<T>* checker = head;
	while (checker != NULL)
	{
		if (checker->obj ==data)
			return checker;
		else
			checker = checker->next;
	}
	return NULL;
}

template <typename T> void linked_list<T>::change_data(int i, T *data)
{
	list_obj<T>* ptr = find_by_index(i);
	delete ptr->obj;
	ptr->obj = data;
}

//tworzy zmienna index, co każdą zmiane wskaźnika index wzrasta o 1, jeśli index się zgadza z szukanym to zwraca wskaźnik do poszukiwanego elementu
template <typename T> list_obj<T>* linked_list<T>::find_by_index(int i)
{
		int index = 0;
		list_obj<T>* checker = head;
		while (checker != NULL) 
		{
			if (index == i)
				return checker;
			else
			{
				index += 1;
				checker = checker->next;
			}
		}
		return NULL;
}

template <typename T> void linked_list<T>::add_head(T* data)//dodaje element na pierwsze miejsce
{
	list_obj<T> *nowy = new list_obj<T>;
	nowy->obj = data;
	if (head == NULL)//jesli nie ma heada to nie ma tez taila
	{
		head = nowy;
		tail = nowy;
	}
	else
	{
		nowy->next = head;
		nowy->prev = NULL;
		head->prev = nowy;
		head = nowy;
	}
	size += 1;
}

template <typename T> void linked_list<T>::add_tail(T* data)//dodaje element na ostatnie miejsce
{
	list_obj<T> *nowy = new list_obj<T>;
	nowy->obj = data;
	if (head == NULL)//jesli nie ma heada to nie ma tez taila
	{
		head = nowy;
		tail = nowy;
	}
	else
	{
		nowy->prev = tail;
		nowy->next = NULL;
		tail->next = nowy;
		tail = nowy;
	}
	size += 1;

}
template <typename T> void linked_list<T>::add_at_index(T* data, int n)//dodaje element na index n//do poprawki upewnienie sie ze jest git ten index :C
{
	list_obj<T>* temp = find_by_index(n-1);//znajdz tego ktory jest prev, czyli dodaje przed nim element
	if (temp == tail)
	{
		add_tail(data);
	}
	else
	{
		list_obj<T> *nowy = new list_obj<T>;
		nowy->obj = data;
		nowy->next = temp->next;
		nowy->prev = temp;
		temp->next = nowy;
	}
	size += 1;
}

template <typename T> bool linked_list<T>::remove_head()//usuwa pierwszy element
{
	if (head == NULL)
	{
		cout << "\nList empty\n";
		return false;
	}
	else
	{
		if (head == tail)
		{
			delete head;
			head = NULL;
			tail = NULL;
		}
		else
		{
			head = head->next;
			delete head->prev;
			head->prev = NULL;
		}
	}
	size -= 1;
	return true;
}

template <typename T> bool linked_list<T>::remove_tail()//usuwa ostatni element
{
	if (head == NULL)
	{
		return false;
	}
	else
	{
		if (head == tail)
		{
			delete head;
			head = NULL;
			tail = NULL;

		}
		else
		{
			tail = tail->prev;
			delete tail->next;
			tail->next = NULL;
		}

	}
	size -= 1;
	return true;

}
template <typename T> void linked_list<T>::clear()
{
	while (size!=0)
	{
		remove_head();
	}
}

//false nie zwroci bo sprawdzane jest czy jest poprawny index przed wywołaniem funkcji w interfejsie
template <typename T> bool linked_list<T>::remove_obj(int n)//usuwa element n-ty od początku
{
	list_obj<T>* obiekt = find_by_index(n);
	if (obiekt == NULL)
		return false;
	if (obiekt == head)
	{
		remove_head();
	}
	else if (obiekt == tail)
	{
		remove_tail();
	}
	else
	{
		obiekt->prev->next = obiekt->next;
		obiekt->next->prev = obiekt->prev;
		delete obiekt;
		size -= 1;
	}
	return true;
}

int main()
{
	linked_list<test_class> *lista = new linked_list<test_class>();
	for (int i = 0; i < 10; i++)
	{
		test_class* temp = new test_class(i, "seks");
		lista->add_head(temp);
	}
	lista->print_list();

	test_class* temp = new test_class(69, "seks");
	lista->add_tail(temp);
	lista->print_list();

	temp = new test_class(69, "seks");
	lista->add_at_index(temp, 5);
	lista->print_list();

	lista->change_data(1, temp);
	lista->print_list();
	delete lista;
	
	return 0;
}