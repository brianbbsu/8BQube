#ifndef REFERENCE_POINTER
#define REFERENCE_POINTER
template <typename T> struct _RefCounter {
  T data;
  int ref;
  _RefCounter(const T &d = 0) : data(d), ref(0) {}
};
template <typename T> struct reference_pointer {
  _RefCounter<T> *p;
  T *operator->() { return &p->data; }
  T &operator*() { return p->data; }
  operator _RefCounter<T> *() { return p; }
  reference_pointer &operator=(
    const reference_pointer &t) {
    if (p && !--p->ref) delete p;
    p = t.p;
    p && ++p->ref;
    return *this;
  }
  reference_pointer(_RefCounter<T> *t = 0) : p(t) {
    p && ++p->ref;
  }
  reference_pointer(const reference_pointer &t)
    : p(t.p) {
    p && ++p->ref;
  }
  ~reference_pointer() {
    if (p && !--p->ref) delete p;
  }
};
template <typename T>
inline reference_pointer<T> new_reference(
  const T &nd) {
  return reference_pointer<T>(new _RefCounter<T>(nd));
}
#endif
// note:
reference_pointer<int> a;
a = new_reference(5);
a = new_reference<int>(5);
a = new_reference((int)5);
reference_pointer<int> b = a;

struct P {
  int a, b;
  P(int _a, int _b) : a(_a), b(_b) {}
} p(2, 3);
reference_pointer<P> a;
c = new_reference(P(1, 2));
c = new_reference<P>(P(1, 2));
c = new_reference(p);
