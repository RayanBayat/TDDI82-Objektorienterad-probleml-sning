#ifndef LIST_H
#define LIST_H

#include <iterator>
#include <iostream>
#include <string>
#include <memory>
#include <initializer_list>

namespace List_NS
{
    template <typename T>
    class List
    {
    private:
       struct Node
        {
            Node() = default;
            Node(T const & v, Node* p, std::unique_ptr<Node> & n)
                : value{v}, prev{p}, next{std::move(n)} {}

            T value {};
            Node* prev {};
            std::unique_ptr<Node> next {};
        };
        //-------------------------------------
        std::unique_ptr<Node> head {};
        Node* tail {};
        int sz {};

    public:
        List();
        //-------------------------------------
        List(List const &);                      // Copy Con
        List(List &&) noexcept;                  // Move Con
        //-------------------------------------
        List(std::initializer_list<T>);          // INIT
        //-------------------------------------
        List & operator=(List const &) &;        // Copy OP
        List & operator=(List &&) & noexcept;    // Move OP
        //-------------------------------------
        void push_front(T const &);
        void push_back(T const &);

        const T & back() const noexcept;
        T & back() noexcept;

        const T & front() const noexcept;
        T & front() noexcept;

        const T & at(int idx);
        T const & at(int idx) const;

        int size() const noexcept;
        bool empty() const noexcept;

        void swap(List & other) noexcept;

        // Class List_Iterator
        class List_Iterator
        {
        public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = T;
            using difference_type = int;
            using pointer = value_type*;
            using reference = value_type&;

            auto operator =(List_Iterator const& n);
            auto operator ++();
            auto operator --();
            auto operator ++(int);
            auto operator --(int);

            bool operator ==(List_Iterator const& it);
            bool operator !=(List_Iterator const& it);
            T & operator *();
            T * operator ->();

        private:
            friend class List;
            List_Iterator(List::Node* const& n);
            List::Node* current;
        };
        // End of class List_Iterator

        auto begin();
        auto end();
    };
    #include "List.tcc"
}
#endif //LIST_H















