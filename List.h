#pragma once
#include <iostream>
#include <stdexcept>

using namespace std;

class ElemL2
{
public:

	ElemL2(char Inf, int Key)
	{
		next = nullptr;
		prev = nullptr;
		inf = Inf;
		key = Key;
	}

	friend class List;
	friend class Line;

	~ElemL2()
	{
		if (next)
			next->prev = prev;
		if (prev)
			prev->next = next;
	}

private:
	char inf;
	int key;
	ElemL2* next;
	ElemL2* prev;
};

class List
{
public:
	List(List* Copy = nullptr)
	{
		head = nullptr;
		last = nullptr;
		size = 0;
		if (Copy)
		{
			ElemL2* current = Copy->head;
			while (current)
			{
				push_back(current->inf, current->key);
				current = current->next;
			}
		}
	}
	bool isEmpty() { return size == 0; }
	size_t get_size() { return size; }

	void BubbleSort();
	void push_back(char inf, int key);
	void push_front(char inf, int key);
	void pop_back();
	void pop_front();
	ElemL2* at(size_t index);
	ElemL2* find_by_inf(char inf);
	void insert(char inf, int key, size_t index);
	void remove(size_t index);
	void set(char inf, int key, size_t index);
	void print_to_console();
	void clear();

	~List()
	{
		clear();
	}
private:
	ElemL2* head;
	ElemL2* last;
	size_t size;
};

void List::BubbleSort()
{
	ElemL2* E1, * E2;
	int temp_key;
	char temp_inf;
	bool is_swapped = 0;
	for (int i = 0; i < (size - 1); i++)
	{
		for (int j = 0; j < (size - 1) - i; j++)
		{
			E1 = at(j);
			E2 = at(j + 1);
			if (E1->key < E2->key)
			{
				is_swapped = true;
				temp_key = E1->key;
				temp_inf = E1->inf;
				set(E2->inf, E2->key, j);
				set(temp_inf, temp_key, j + 1);
			}
		}
		if (!is_swapped)
			break;
		is_swapped = false;
	}
}

void List::push_back(char inf, int key)
{
	if (!isEmpty())
	{
		last->next = new ElemL2(inf, key);
		last->next->prev = last;
		last = last->next;
	}
	else
	{
		head = new ElemL2(inf, key);
		last = head;
	}
	size += 1;
}

void List::push_front(char inf, int key)
{
	if (!isEmpty())
	{
		head->prev = new ElemL2(inf, key);
		head->prev->next = head;
		head = head->prev;
	}
	else
	{
		head = new ElemL2(inf, key);
		last = head;
	}
	size += 1;
}

void List::pop_back()
{
	if (isEmpty())
		throw runtime_error("List is empty\n");
	ElemL2* newLast = last->prev;
	delete last;
	last = newLast;
	if (!newLast)
		head = nullptr;
	size -= 1;
}

void List::pop_front()
{
	if (isEmpty())
		throw runtime_error("List is empty\n");
	ElemL2* newHead = head->next;
	delete head;
	head = newHead;
	if (!newHead)
		last = nullptr;
	size -= 1;
}

ElemL2* List::at(size_t index)
{
	if (index >= size)
		throw out_of_range("Index is out of range\n");
	if (index == 0)
		return head;
	if (index == (size - 1))
		return last;
	int count;
	ElemL2* current;
	if ((size / 2) > index)
	{
		current = head;
		count = 0;
		while (count != index)
		{
			current = current->next;
			count++;
		}
	}
	else
	{
		current = last;
		count = size - 1;
		while (count != index)
		{
			current = current->prev;
			count--;
		}
	}
	return current;
}

ElemL2* List::find_by_inf(char inf)
{
	ElemL2* current = head;
	while (current)
	{
		if (current->inf == inf)
			return current;
		current = current->next;
	}
	return nullptr;
}

void List::insert(char inf, int key, size_t index)
{
	if (index == 0)
		push_front(inf, key);
	else
	{
		try
		{
			ElemL2* Next = at(index);
			ElemL2* Prev = Next->prev;
			ElemL2* Include = new ElemL2(inf, key);
			Prev->next = Include;
			Include->prev = Prev;
			Next->prev = Include;
			Include->next = Next;
			size += 1;
		}
		catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
	}
}

void List::remove(size_t index)
{
	try
	{
		if (index == 0)
			pop_front();
		else if (index == (size - 1))
			pop_back();
		else
		{
			ElemL2* Exclude = at(index);
			delete Exclude;
			size -= 1;
		}
	}
	catch (runtime_error& exception) { throw runtime_error("List is empty\n"); }
	catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
}

void List::set(char inf, int key, size_t index)
{
	ElemL2* current;
	try
	{
		current = at(index);
		current->inf = inf;
		current->key = key;
	}
	catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
}

void List::print_to_console()
{
	if (isEmpty())
		throw runtime_error("List is empty\n");
	ElemL2* current = head;
	while (current)
	{
		cout << current->inf << ' ' << current->key << endl;
		current = current->next;
	}
}

void List::clear()
{
	while (!isEmpty())
		pop_front();
}