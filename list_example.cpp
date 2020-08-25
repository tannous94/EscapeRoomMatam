#include <functional>
#include "list.h"
#include "mtmtest.h"

/**
 * Function object for finding a target integer
 */
class EqualTo {
private:
  int target;
public:
  EqualTo(int i) : target(i) {}
  bool operator()(const int& i) const {
    return i == target;
  }
};


static void listExample(){
	List<int> list;
	list.insert(1, list.end());
	list.insert(2, list.end());
	list.insert(3, list.end());

	int counter = 1;
  for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
    ASSERT_EQUALS(counter++, *it);
  }

	// C++11 syntactic sugar Range-based for-loop
	counter = 1;
  for (int& element : list) {
    ASSERT_EQUALS(counter++, element);
  }

	List<int>::Iterator it = list.begin();
	ASSERT_EQUALS(3, list.getSize());
	list.remove(++it);
	it = list.begin();
	ASSERT_EQUALS(*it, 1);
	list.insert(4, list.begin());
	list.insert(2, list.begin());


	// std::less<int> is a function object defined in <functional>
	// it simply calls operator< of the type compared
	list.sort(std::less<int>());
	it = list.begin();
	ASSERT_EQUALS(1, *it);

	it = list.find(EqualTo(3));
	ASSERT_EQUALS(3, *it);
	*it = 3;


	// The following insert should add to end of list
	list.insert(5);

	List<int> list2(list);
	ASSERT_TRUE(list == list2);
	ASSERT_FALSE(list != list2);

	//test directions
	it = list.begin();
	it++;
	ASSERT_EQUALS(2, *it);
	++it;
	ASSERT_EQUALS(3, *it);
	it--;
	ASSERT_EQUALS(2, *it);
	it++;
	it++;
	ASSERT_EQUALS(4, *it);
	--it;
	ASSERT_EQUALS(3, *it);


}

static void test() {
	List<int> list;
	ASSERT_EQUALS(0, list.getSize());
	list.insert(2, list.end());
	ASSERT_EQUALS(1, list.getSize());
	ASSERT_EQUALS(2, *list.begin());
	ASSERT_EQUALS(2, *list.tail());
	ASSERT_THROWS(ElementNotFound, *list.end());
	ASSERT_EQUALS(2, *list.find(EqualTo(2)));
	list.insert(1, list.begin());
	ASSERT_EQUALS(2, list.getSize());
	ASSERT_EQUALS(2, *list.find(EqualTo(2)));
	ASSERT_EQUALS(1, *list.find(EqualTo(1)));
	ASSERT_EQUALS(2, *list.tail());
	ASSERT_EQUALS(1, *list.begin());
	list.insert(3, list.begin());
	ASSERT_EQUALS(3, *list.begin());
	ASSERT_EQUALS(2, *list.tail());
	List<int>::Iterator iter = list.begin();
	iter--;
	ASSERT_EQUALS(3, *iter);
	iter++;
	iter--;
	ASSERT_EQUALS(3, *iter);
	iter++;
	ASSERT_EQUALS(1, *iter);
	list.insert(4, iter);
	ASSERT_EQUALS(4, *list.find(EqualTo(4)));
	ASSERT_EQUALS(4, list.getSize());
	List<int>::Iterator iter1 = list.begin();
	ASSERT_EQUALS(3, *iter1);
	iter1++;
	ASSERT_EQUALS(4, *iter1);
	iter1++;
	ASSERT_EQUALS(1, *iter1);
	iter1++;
	ASSERT_EQUALS(2, *iter1);
	list.insert(5, list.end());
	iter1++;
	ASSERT_EQUALS(5, *iter1);
	ASSERT_EQUALS(5, list.getSize());
	List<int> list1;
	ASSERT_THROWS(ElementNotFound, list.insert(5, list1.end()));
	ASSERT_THROWS(ElementNotFound, list1.remove(list1.begin()));
	list1.insert(1);
	ASSERT_EQUALS(1, *list1.begin());
	ASSERT_EQUALS(1, *list1.tail());
	list1.insert(3);
	ASSERT_EQUALS(1, *list1.begin());
	ASSERT_EQUALS(3, *list1.tail());
	ASSERT_EQUALS(2, list1.getSize());
	list1.remove(list1.tail());
	ASSERT_EQUALS(1, *list1.begin());
	ASSERT_EQUALS(1, *list1.tail());
	ASSERT_EQUALS(1, list1.getSize());
	ASSERT_THROWS(ElementNotFound, list1.remove(list.begin()));
	ASSERT_THROWS(ElementNotFound, list1.remove(list1.end()));
	ASSERT_TRUE(list1 != list);
	List<int> list2(list);
	ASSERT_TRUE(list == list2);
	ASSERT_EQUALS(5, list2.getSize());
	List<int>::Iterator iter2 = list2.begin();
	ASSERT_EQUALS(3, *iter2);
	iter2++;
	ASSERT_EQUALS(4, *iter2);
	iter2++;
	ASSERT_EQUALS(1, *iter2);
	iter2++;
	ASSERT_EQUALS(2, *iter2);
	iter2++;
	ASSERT_EQUALS(5, *iter2);
	list2 = list1;
	ASSERT_EQUALS(1, list2.getSize());
	ASSERT_EQUALS(1, *list2.begin());
	ASSERT_EQUALS(1, *list2.tail());
	List<int>::Iterator iter22 = list.end();
	iter22--;
	ASSERT_EQUALS(5, *iter22);
	iter22--;
	ASSERT_EQUALS(2, *iter22);
	iter22--;
	ASSERT_EQUALS(1, *iter22);
	iter22--;
	ASSERT_EQUALS(4, *iter22);
	iter22--;
	ASSERT_EQUALS(3, *iter22);
	iter22--;
	ASSERT_EQUALS(3, *iter22);
	List<int>::Iterator iter23 = list1.end();
	iter23--;
	ASSERT_EQUALS(1, *iter23);
	iter23++;
	ASSERT_EQUALS(iter23, list1.end());
	--iter23;
	ASSERT_EQUALS(1, *iter23);
	iter23--;
	ASSERT_EQUALS(1, *iter23);
}

int main1() {
  RUN_TEST(listExample);
  RUN_TEST(test);
  return 0;
}
