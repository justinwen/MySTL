#ifndef _LIST_H_
#define _LIST_H_

#include "listIterator.h"
#include "algorithm.h"
#include "construct.h"
#include "allocator.h"
#include <iostream>

namespace EasySTL {
    template <class T, class Alloc = alloc>
    class list {
    public:
        typedef T value_type;
        typedef value_type* pointer;
        typedef value_type& reference;

        typedef _list_node<T> list_node;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        typedef list_node* link_type;
        typedef simple_alloc<list_node, Alloc> list_node_allocator;

        typedef _list_iterator<T, T&, T*> iterator;
        //配置一个节点并传回
        link_type get_node() {
            return list_node_allocator::allocate();
        }

        //释放一个节点
        void put_node(link_type x) {
            list_node_allocator::deallocate(x);
        }

        //产生一个节点，并且带有元素值
        link_type create_node(const T& x) {
            link_type newListNode = get_node();
            construct(&newListNode->data, x);
            return newListNode;
        }

        //销毁一个元素点，析构并释放
        void destroy_node(link_type d) {
            destroy(&d->data);
            put_node(d);
        }

        public:
            iterator begin() const {return node->next};
            iterator end() const {return node;}
            bool empty() const {return node->next == node;}
            size_type size() const {
                size_type result = 0;
                result = distance(begin(), end());
                return result;
            }

            reference front() {return *begin();}
            reference back() {return *(--end());}

            //构造函数
            list() { empty_initialize();}
            ~list() {
                clear();
                erase(end());
            }

            //尾部插入节点
            void push_back(const T& x) {
                insert(end(), x);
            }

            //头部插入节点
            void push_front(const T& x) {
                insert(end(), x);
            }

            //删除头部节点
            void pop_front(const T& x) {
                erase(begin());
            }

            void pop_back() {
                erase(--end());
            }

            void clear() {
                iterator s = begin();
                while (s!= end()) {
                    s = erase(s);
                }

                node->next = node;
                node->prev = node;
            }

            //删除所有节点值为x的节点
            void remove(const T& x) {
                iterator s = begin();
                while (s != end()) {
                    if (*s == x)
                        s = erase(s);
                    else
                        s++;
                }
            }

            //移除连续并相同的元素
            void unique() {
                iterator first = begin();
                iterator last = end();
                if (first == end) return;
                iterator next = first
                while (++next != last) {
                    if (*first == *next)
                        erase(next);
                    else
                        first = next;
                    next = first;
                }
            }

            iterator erase(iterator position, const T& x) {
                link_type tmp = create_node(x);
                tmp->next = position.node;
                tmp->prev = position.node->prev;
                position.node->prev->next = tmp;
                position.node->prev = tmp;
                return tmp;
            }

            //将[first,last)之间的元素移动到postion之前
            void transfer(iterator position, iterator first, iterator last) {
                if (last == position) {
                    return;
                }

                link_type last_node = last.node->prev;
                //将first last取下来
                first.node->prev->next = last.node->prev;
                last.node->prev = first.node->prev;

                linktype prev_node = position.node->prev;
                prev_node->next = first.node;
                first.node->prev = prev_node;

                last_node->next = position.node;
                position.node->prev = last_node;
            }

            //链表x接合于position之前
            void splice(iterator position, list& x) {
                if (x.empty())
                    return;
                transfer(position, x.begin(), x.end());
            }

            //将某一个位置上的元素接合到position之前
            void splice(iterator position, iterator i) {
                iterator j = i;
                j++;
                transfer(position, i, j);
            }

            void splice(iterator position, iterator first, iterator last) {
                if (last == position)
                    return;
                transfer(position, first, last);
            }

            void merge(list& x) {
                iterator p = begin();
                iterator x_start = x.begin();

                while(p != end() && x_start != x.end()) {
                    std::cout << *p << std::endl;
                    if (*x_start > *p)
                        p++;
                    else {
                        iterator next = x_start+1;
                        splice(p, x_start);
                        x_start = next;
                    }
                }

                if (!x.empty()) {
                    splice(end(), x_start, x.end());
                }
            }

            void reverse() {
                iterator start = begin();
                iterator last = end();
                if (size() == 0 || size() == 1)
                    return;
                start++;
                while (start != last) {
                    iterator next = start + 1;
                    splice(begin(),start);
                    start = next;
                }
                    
            }

            void swap(list& x) {
                link_type tmp = x.node;
                x.node = this->node;
                this->node = tmp;
            }

            void  sort() {
                if (size() == 0 || size() == 1) {
                    return;
                }
                list<T, Alloc> tmp;
                iterator q = begin();
                while(!empty()) {
                    iterator p = tmp.begin();
                    while (p!=tmp.end() && *p < *q)
                        p++;
                    tmp.splice(p, q);
                    q = begin();
                }

                swap(tmp);
            }
    protected:
        link_type node;

        void empty_initialize() {
            node = get_node();
            node->next = node;
            node->prev = node;
        }
    };
}

#endif