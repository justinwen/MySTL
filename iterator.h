#ifndef _ITERATOR_H_
#define _ITERATOR_H_
#include <cstddef>
namespace EasySTL {
    //五种迭代器
    struct input_iterator_tag{};                
    //这种迭代器所指的对象，不允许外界改变。只读(read only)
    struct output_iterator_tag{};               
    //唯写
    struct forward_iterator_tag: public input_iterator_tag {};   
    //允许写入型算法，在此迭代器所形成的区间上进行读写操作
    struct bidirectional_iterator_tag : public forward_iterator_tag{};   
    //可双向移动，某些算法需要逆向访问某个迭代器区间，可以使用Bidirectional iterator
    struct random_access_iterator_tag : public bidirectional_iterator_tag{};  
    //前四种迭代器都只供应一部分指针算术能力，前三种支持operator++,第四种支持operator--
    //这一种则涵盖所有指针算数能力，包括 p+n, p-n, p[n], p1-p2, p1<p2。

    template<class T, class Distance>
    struct input_iterator {
        typedef input_iterator_tag  iterator_category;
        typedef T                   value_type;
        typedef Distance            difference_type;
        typedef T*                  pointer;
        typedef T&                  reference;
    };

    template <class T, class Distance>
    struct output_iterator {
        typedef output_iterator_tag  iterator_category;
        typedef void                 value_type;
        typedef void                 difference_type;
        typedef void                 pointer;
        typedef void                 reference;
    };

    template <class T, class Distance>
    struct forward_iterator {
        typedef forward_iterator_tag  iterator_category;
        typedef T                     value_type;
        typedef Distance              difference_type;
        typedef T*                    pointer;
        typedef T&                    reference;
    };

    template <class T, class Distance>
    struct bidirectional_iterator {
        typedef bidirectional_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef Distance                    difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    template <class T, class Distance>
    struct random_access_iterator {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef Distance                    difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    template <class Category, class T, class Distance=ptrdiff_t,
    class Pointer=T*, class Reference = T&>
    struct iterator {
        typedef Category        iterator_category;
        typedef T               value_type;
        typedef Distance        difference_type;
        typedef Pointer         pointer;
        typedef Reference       reference;
    };

    //traits
    template<class Iterator>
    struct iterator_traits {
        typedef typename Iterator::iterator_category   iterator_category;
        typedef typename Iterator::value_type          value_type;
        typedef typename Iterator::difference_type     difference_type;
        typedef typename Iterator::pointer             pointer;
        typedef typename Iterator::reference           reference;
    };

    //针对原生指针而设计的traits偏特化
    template<class T>
    struct iterator_traits<T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef T*                          pointer;
        typedef T&                          reference;
    };

    //pointer to const的特化版本
    template<class T>
    struct iterator_traits<const T*> {
        typedef random_access_iterator_tag  iterator_category;
        typedef T                           value_type;
        typedef ptrdiff_t                   difference_type;
        typedef const T*                    pointer;
        typedef const T&                    reference;
    };

    template<class Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(const Iterator& It) {
        typedef typename iterator_traits<Iterator>::iterator_category category;
        return category();
    }

    template<class Iterator>
    inline typename iterator_traits<Iterator>::value_type*
    value_type(const Iterator& It) {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    template<class Iterator>
    inline typename iterator_traits<Iterator>::difference_type*
    difference_type(const Iterator& It) {
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }
}

#endif