#include "iterator.h"
namespace EasySTL {
    template <class T, class Ref, class Ptr, size_t BufSize>
    struct _deque_iterator {
        typedef _deque_iterator<T, T&, T*, BufSize> iterator;
        typedef _deque_iterator<const T, const T&, const T*, BufSize> const_iterator;

        static size_t buffer_size() {return _deque_buf_size(BufSize, sizeof(T));}


        //没有继承std的iterator，所以必须指明五个必要的迭代器的相应类别
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef Ptr pointer;
        typedef Ref reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T** map_pointer;

        typedef _deque_iterator self;

        T* cur;
        T* first;
        T* last;
        map_pointer node;

        static size_t _deque_buf_size(size_t n, size_t sz) {
            return n != 0 ? n: (sz < 512 ? size_t(512/sz) : size_t(1));
        }

        //将迭代器指向新的缓冲区的第一个位置
        void set_node(map_pointer new_node) {
            node = new_node;
            first = *new_node;
            last = first + difference_type(buffer_size());
        }

        reference operator*() const {return *cur;}
        pointer operator*() const {return &(operator*());}
        difference_type operator-(const self& x) const {
            return difference_type(buffer_size()) * (node - x.node - 1) +
            (cur - first) + (x.last - x.cur);
        }

        self& operator++() {
            ++cur;
            if (cur == last) {
                set_node(node+1);
                cur = first;
            }
            return *this;
        }

        self& operator++(int) {
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self& operator--() {
            if (cur == first) {
                set_node(node - 1);
                cur = last;
            }
            cur--;
            return *this;
        }

        self& operator--(int) {
            self tmp = *this;
            --*this;
            return tmp;
        }

        self& operator+=(difference_type n) {
            difference_type diff = n+cur-first;
            if (diff < (difference_type)buffer_size() && diff > 0) {
                cur += n;
                return *this;
            }

            if (diff > 0) {
                difference_type left = n-(last-cur);
                difference_type node_diff = left / (difference_type)buffer_size();
                set_node(node + node_diff);
                cur = left%(difference_type)buffer_size();
                return *this;
            }

            if (diff < 0) {
                difference_type left = n - (cur-first);
                difference_type node_diff = left / (difference_type)buffer_size();
                set_node(node - node_diff);
                cur = last - (left%(difference_type)buffer_size());
                return *this;
            }
        }

        self operator+(difference_type n) const {
            self tmp = *this;
            return tmp+=n;
        }

        self& operator-=(difference_type n) {return *this += -n;}

        self operator-(difference_type n) const {
            self tmp = *this;
            return tmp -= n;
        }

        bool operator==(const self& x) const {return cur == x.cur;}
        bool operator!=(const self& x) const {return cur != x.cur;}
        bool operator<(const self& x) const {
            return (node != x.node) ? (cur < x.cur) : (node < x.node);
        }
    };
}