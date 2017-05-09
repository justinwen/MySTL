template <class T>
struct _list_node {
    typedef _list_node * void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};