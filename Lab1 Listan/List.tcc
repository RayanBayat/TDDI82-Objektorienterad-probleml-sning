// //-------------------------------------
template <typename T>
List<T>::List()
  : head{std::make_unique<Node>() }, tail{}, sz{}
{
    std::unique_ptr<Node> a;
    head -> next = std::make_unique<Node>(T{}, head.get(), a);
    tail = (head -> next).get();
}
//---------------- Copy Con ---------------------
template <typename T>
List<T>::List(List const & other)
  : List{}
{
    for (Node * tmp {(other.head -> next).get()}; tmp != other.tail ; )
    {
        push_back(tmp -> value);
        tmp = (tmp -> next).get();
    }
}
// // //---------------- Move Con ---------------------
template <typename T>
List<T>::List(List && tmp) noexcept
  :List{}
{
    swap(tmp);
}
   //----------------- INIT --------------------
template <typename T>
List<T>::List(std::initializer_list<T> lst)
  : List{}
{
    for ( auto const & val : lst )
    {
        push_back(val);
    }
}

template <typename T>
void List<T>::push_front(T const & value)
{
    Node * old_first {(head -> next).get()};
    head -> next = std::make_unique<Node>(value, head.get(), (head -> next));
    old_first -> prev = (head -> next).get();
    ++sz;
}

template <typename T>
void List<T>::push_back(T const & value)
{
    Node * old_last {tail -> prev};
    old_last -> next = std::make_unique<Node>(value, old_last, (old_last -> next));
    tail -> prev = (old_last -> next).get();
    ++sz;
}

template <typename T>
bool List<T>::empty() const noexcept
{
    return (head -> next).get() == tail;
}

template <typename T>
const T & List<T>::back() const noexcept
{
    return tail -> prev -> value;
}

template <typename T>
T & List<T>::back() noexcept
{
    return tail -> prev -> value;
}

template <typename T>
const T & List<T>::front() const noexcept
{
    return head -> next -> value;
}

template <typename T>
T & List<T>::front() noexcept
{
    return head -> next -> value;
}

template <typename T>
const T & List<T>::at(int idx)
{
    return const_cast<T &>(static_cast<List const *>(this) -> at(idx));
}

template <typename T>
T const & List<T>::at(int idx) const
{
    if (idx >= sz)
        throw std::out_of_range{"Index not found"};
    Node * tmp {(head -> next).get()};
    while ( idx > 0 )
    {
        tmp = (tmp -> next).get();
        --idx;
    }
    return tmp -> value;
}

template <typename T>
int List<T>::size() const noexcept
{
    return sz;
}
template <typename T>
void List<T>::swap(List & other) noexcept
{
    using std::swap;

    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);

}

template <typename T>
List<T> & List<T>::operator=( List const  & rhs) &
{
    List{rhs}.swap(*this);

    return *this;
}

template <typename T>
List<T> & List<T>::operator=(List && rhs)& noexcept
{
    swap(rhs);
    return *this;
}

//------------- List_Iterator---------------------------------------
template <typename T>
auto List<T>::begin()
{
    return List_Iterator((head -> next).get());
}

template <typename T>
auto List<T>::end()
{
    return List_Iterator(tail);
}

template <typename T>
List<T>::List_Iterator::List_Iterator(List::Node* const& n)
    : current{n}
{

}

template <typename T>
auto List<T>::List_Iterator::operator =(List_Iterator const& it)
{
	current = it.current;
	return *this;
}

template <typename T>
bool List<T>::List_Iterator::operator !=(List_Iterator const& it)
{
	if (current == it.current)
	{
		return false;
	}
	return true;
}

template <typename T>
bool List<T>::List_Iterator::operator ==(List_Iterator const& it)
{
    if (current == it.current)
	{
		return true;
	}
	return false;
}

template <typename T>
auto List<T>::List_Iterator::operator ++()
{
	current = (current -> next).get();
	return *this;
}

template <typename T>
auto List<T>::List_Iterator::operator ++(int it)
{
    ++*this;
    return *this;
}

template <typename T>
auto List<T>::List_Iterator::operator --(int it)
{
    --*this;
    return *this;
}

template <typename T>
auto List<T>::List_Iterator::operator--()
{
    current = (current -> prev);
	return *this;
}

template <typename T>
T & List<T>::List_Iterator::operator *()
{
	return current -> value;
}

template <typename T>
T * List<T>::List_Iterator::operator ->()
{
    return &(current -> value);
}




