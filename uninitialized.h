#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_

#include "construct.h"
#include "algorithm.h"

namespace EasySTL {
    //未初始化的拷贝，在已获得的内存上创建一些元素
    template<class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
    ForwardIterator result, _true_type) {
        memcpy(result, first, (last - first)*sizeof(*first));
        return result+(last  - first);
    }
    template<class InputIterator, class ForwardIterator>
    ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type) {
        int i = 0;
        for ( ; first != last; ++first, ++i) {
            construct(result+i, *first);
        }
        return (result+i);
    }

    template<class InputIterator, class ForwardIterator, class T>
    ForwardIterator _uninitialized_copy(InputIterator first, InputIterator last,
    ForwardIterator result) {
        typedef typename _type_traits<T>::is_POD_type isPOD;
        return _unintialized_copy_aux(first, last, result, isPOD());
    }

    template<class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last,
    ForwardIterator result) {
        _uninitialized_copy(first, last, result, value_type(result));
    }
 
    template<class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwrdIterator last,
    const T& value, _true_type) {
        fill(first, last, value);
    }

    template<class ForwardIterator, class T>
    void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
    const T& value, _false_type) {
        for (;first != last; ++first) {
            construct(first, value);
        }
    }

    template<class ForwardIterator, class T>
    void uninitialized_fill(ForwardIterator first, ForwardIterator last,
    const T& value) {
        typedef typename _type_traits<T>::is_POD_type isPOD;
        _uninitialized_fill_aux(first, last, value, isPOD());
    }


    //未初始化的拷贝，以某一特定数量n初始化
    template<class ForwardIterator, class Size, class T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n,
    const T& x, _true_type) {
        return fill_n(first, n, x);
    }

    template<class ForwardIterator, class Size, class T>
    ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n,
    const T& x, _false_type) {
        int i = 0;
        for (;i != n;++i) {
            construct((T*)(first+i),x);
        }
        return (first+i);
    }

    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n,
    const T& x) {
        typedef typename _type_traits<T>::isPOD_type isPOD;
        _uninitialized_fill_n_aux(first, n, x, isPOD());
    }
}
#endif