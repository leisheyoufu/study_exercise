template<typename T1, typename T2>
decltype(x+y) add(T1 x, T2 y);

template<typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x+y);

typdef typename decltype(obj)::iterator iType;
// 类似 typedef typename T::iterator iType;
decltype(obj) anotherObj(obj);


auto cmp = [] (const Person& p1, const Person &p2) {
  return /* 给出Person类比大小的准则 */
}

//...
std::set<Person, decltype(cmp)> coll<cmp>;