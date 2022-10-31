#include "List.h"
#include <iostream>
#include "catch.hpp"

using namespace std;

TEST_CASE( "Create list" )
{
    List_NS::List<int> lst{1,4,2,6,8,9};
    CHECK(lst.at(2) == 2);
    CHECK(lst.size() == 6);

    List_NS::List<int> l2;
    l2 = lst;

    CHECK(l2.size() == lst.size());
    CHECK(l2.front() == lst.front());
    CHECK(l2.back() == lst.back());
}

TEST_CASE ( "Iterator" )
 {
   List_NS::List<int> L{2,5,7};

  for (auto it = L.begin(); it != L.end(); it++)
  {
         CHECK(L.front() == 2);
         CHECK(L.at(1) == 5);
         CHECK(L.back() == 7);
         CHECK(L.size() == 3);
  }
 }

// Här
TEST_CASE("Iterator operator * and ->")
{
  std::string y{};
  List_NS::List <std::string>lst2{"hello","ds","2"};
  auto rb2 { std::make_reverse_iterator(lst2.end()) };
  auto re2 { std::make_reverse_iterator(lst2.begin()) };
  for ( auto it = rb2; it != re2; ++it )
  {
    y = y + std::to_string(it->length());
  }

  CHECK(y == "125");

  y = "";
  List_NS::List<int> lst{2,3,1,5};
  auto rb { std::make_reverse_iterator(lst.end()) };
  auto re { std::make_reverse_iterator(lst.begin()) };
  for ( auto it = rb; it != re; ++it )
  {
    y += std::to_string(*it);
  }

  CHECK(y == "5132");

}
TEST_CASE(" Iterator ++ and --")
{
  List_NS::List<int> lst{2,3,1,5};
  auto  it = lst.end();
  it--;
  CHECK(*(--it) == 1);

  CHECK(*(it--) == 3);

  CHECK(*(++it) == 1);

  CHECK(*(it++) == 5);
}

TEST_CASE( "Iterator with Operator == and =!")
{
    List_NS::List<int> lst{2,3,1,5};
  auto  it = lst.end();
  auto  it2 = lst.end();

  CHECK(it == it2);
  CHECK_FALSE(it != it2);

}

