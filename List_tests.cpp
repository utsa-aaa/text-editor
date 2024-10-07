#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

// TEST(test_stub) {
//     // Add test code here
//     ASSERT_TRUE(true);
// }

TEST(test_empty){
    List <int> emp_list;
    ASSERT_TRUE(emp_list.empty());
}

TEST(test_size){
    List<int> l1;
    ASSERT_EQUAL(l1.size(),0);

    List<string> l2;
    l2.push_back("orange");
    l2.push_back("apple");
    l2.push_back("kiwi");
    ASSERT_EQUAL(l2.size(),3);
}

TEST(test_front){
    List<string> l1;
    l1.push_back("orange");
    l1.push_back("apple");
    l1.push_back("kiwi");
    ASSERT_EQUAL(l1.front(),"orange");

    List<double> l2;
    l2.push_front(2.3);
    l2.push_front(4.5);
    l2.push_front(7.1);
    ASSERT_EQUAL(l2.front(),7.1);
}

TEST(test_back){
    List<string> l1;
    l1.push_back("orange");
    l1.push_back("apple");
    l1.push_back("kiwi");
    ASSERT_EQUAL(l1.back(),"kiwi");

    List<double> l2;
    l2.push_front(2.3);
    l2.push_front(4.5);
    l2.push_front(7.1);
    ASSERT_EQUAL(l2.back(),2.3);
}

TEST(test_pop_front){
    List<int> l1;
    l1.push_back(5);
    l1.push_back(88);
    l1.push_back(32);
    ASSERT_EQUAL(l1.front(),5);
    l1.pop_front();
    ASSERT_EQUAL(l1.front(),88);
}

TEST(test_pop_back){
    List<int> l1;
    l1.push_back(5);
    l1.push_back(88);
    l1.push_back(32);
    ASSERT_EQUAL(l1.back(),32);
    l1.pop_back();
    ASSERT_EQUAL(l1.back(),88);
}

TEST(test_clear_more){
    List<string> l1;
    l1.push_back("red");
    l1.push_back("yellow");
    l1.push_back("blue");
    ASSERT_FALSE(l1.empty());
    l1.clear();
    ASSERT_TRUE(l1.empty());
}

TEST(test_empty_on_new_list) {
    List<int> list;
    ASSERT_TRUE(list.empty());
}

TEST(test_push_back_and_front) {
    List<int> list;
    list.push_back(1);
    list.push_front(0);
    ASSERT_EQUAL(list.size(), 2);
    // Additional checks to ensure the order is correct
    ASSERT_EQUAL(*list.begin(), 0);
    auto it = list.begin();
    ++it; // Move to the second element
    ASSERT_EQUAL(*it, 1);
}

TEST(test_size_after_insertions) {
    List<int> list;
    list.push_back(10);
    list.push_front(20);
    ASSERT_EQUAL(list.size(), 2);
}

TEST(test_order_after_insertions) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    auto it = list.begin();
    ASSERT_EQUAL(*it, 0);
    ++it;
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
}

TEST(test_remove_operations) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.pop_back();
    list.pop_front();
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(*list.begin(), 2);
}

TEST(test_copy_constructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    List<int> copy = original;
    ASSERT_EQUAL(copy.size(), 2);
    auto it = copy.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
}

TEST(test_assignment_operator) {
    List<int> list1;
    list1.push_back(1);
    List<int> list2;
    list2 = list1;
    ASSERT_EQUAL(list2.size(), 1);
    ASSERT_EQUAL(*list2.begin(), 1);
}

TEST(test_clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.clear();
    ASSERT_TRUE(list.empty());
}

TEST(test_iterators) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it, ++i) {
        ASSERT_EQUAL(*it, i);
    }
}

// TEST(test_erase){

// }

TEST(test_insert_one){
    List<int> l1;
    List<int>::Iterator it1 = l1.begin();
    l1.push_back(56);
    l1.push_back(98);
    l1.push_back(109);
    l1.push_back(3);
    List<int>::Iterator it2= l1.insert(it1,66);
    // {66,0,56,98,109,3}
    ASSERT_EQUAL(*it2, 66);
    ASSERT_EQUAL(it1,++it2);
}

TEST(test_insert_two){
    List<string> l1;
    List<string>::Iterator it1 = l1.end();
    l1.push_back("folklore");
    l1.push_back("evermore");
    l1.push_back("lover");
    l1.push_back("midnights");
    List<string>::Iterator it2= l1.insert(it1,"red");
    //{folklore,evermore,lover,midnights,red}
    ASSERT_EQUAL(*it2,"red");
}

TEST(test_insert_three){
    List<string> l1;
    List<string>::Iterator it1 = l1.begin();
    List<string>::Iterator it2= l1.insert(it1,"london");
    ASSERT_EQUAL(*it2,"london");
}

// TEST(test_erase_one){
//     List<int>l1;
//     List<int>::Iterator it1 = l1.begin();
//     l1.push_back(56);
//     l1.push_back(98);
//     l1.push_back(109);
//     l1.push_back(3);
//     //{56,98,109,3}
//     List<int>::Iterator it2= l1.erase(it1);
//     ASSERT_EQUAL(*it2,98);
// }

// TEST(test_erase_two){
//     List<string> l1;
//     List<string>::Iterator it1 = l1.end();
//     l1.push_back("folklore");
//     l1.push_back("evermore");
//     l1.push_back("lover");
//     l1.push_back("midnights");
//     //{folklore,evermore,lover,midnights}
//     it1--;
//     List<string>::Iterator it2= l1.erase(it1);
//     ASSERT_EQUAL(*it2,nullptr);
// }

// TEST(test_erase_three){
//     List<string> l1;
//     List<string>::Iterator it1 = l1.begin();
//     List<string>::Iterator it2= l1.erase(it1);
//     ASSERT_EQUAL(*it2,nullptr);
// }
// Test push_front and push_back
TEST(test_push_front_and_back) {
    List<int> list;
    list.push_front(1);
    list.push_back(2);
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(*list.begin(), 1); // Front element check
    auto it = list.begin();
    ++it;
    ASSERT_EQUAL(*it, 2); // Back element check
}

// Test pop_front and pop_back
TEST(test_pop_front_and_back) {
    List<int> list;
    list.push_front(1);
    list.push_back(2);
    list.pop_front();
    list.pop_back();
    ASSERT_TRUE(list.empty());
}

// Test begin and end
TEST(test_begin_and_end) {
    List<int> list;
    list.push_back(1);
    ASSERT_EQUAL(*list.begin(), 1);
    ASSERT_TRUE(list.end() == list.begin() + 1); // Assuming operator+ is implemented for simplicity
}

// Test insert at position 3
TEST(test_insert_3) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(4);
    auto it = list.begin();
    ++it; ++it; // Move to position before which 3 will be inserted
    list.insert(it, 3);
    ASSERT_EQUAL(list.size(), 4);
    it = list.begin(); ++it; ++it; // Move to the third position
    ASSERT_EQUAL(*it, 3);
}

// Test insert at position 2
TEST(test_insert_2) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);
    auto it = list.begin();
    ++it; // Move to position before which 2 will be inserted
    list.insert(it, 2);
    ASSERT_EQUAL(list.size(), 3);
    it = list.begin(); ++it; // Move to the second position
    ASSERT_EQUAL(*it, 2);
}

// Test insert at position 1
TEST(test_insert_1) {
    List<int> list;
    list.push_back(2);
    list.insert(list.begin(), 1); // Insert at the beginning
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(*list.begin(), 1);
}

// Test erase 3 elements
TEST(test_erase_3) {
    List<int> list;
    for (int i = 1; i <= 3; ++i) {
        list.push_back(i);
    }
    auto it = list.begin();
    ++it; // Position to the second element
    list.erase(it);
    ASSERT_EQUAL(list.size(), 2);
    it = list.begin();
    ASSERT_EQUAL(*it, 1); // Check remaining elements
    ++it;
    ASSERT_EQUAL(*it, 3);
}

// Test erase 2 elements
TEST(test_erase_2) {
    List<int> list;
    for (int i = 1; i <= 3; ++i) {
        list.push_back(i);
    }
    auto it = list.begin();
    list.erase(it); // Erase first element
    ASSERT_EQUAL(list.size(), 2);
    it = list.begin();
    ASSERT_EQUAL(*it, 2); // Check first element is now what was the second
}

// Test empty and size
TEST(test_empty_and_size) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    list.push_back(1);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.size(), 1);
}

TEST(list_test_assignment_2) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    List<int> list2;
    list2 = list1; // Assignment
    list1.push_back(3); // Modify list1 after assignment

    ASSERT_EQUAL(list2.size(), 2); // list2 should remain unchanged after list1 modification
    auto it = list2.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
}
TEST(list_test_erase_1) {
    List<int> list;
    list.push_back(1);
    list.erase(list.begin()); // Erase the only element
    ASSERT_TRUE(list.empty());
}
TEST(list_test_assignment_1) {
    List<int> list1;
    list1.push_back(1);
    List<int> list2;
    list2 = list1; // Assignment
    ASSERT_EQUAL(list2.size(), 1);
    ASSERT_EQUAL(*list2.begin(), 1);
}
TEST(list_test_iterator_equality) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    auto it1 = list.begin();
    auto it2 = list.begin();
    ASSERT_TRUE(it1 == it2); // Iterator equality
    ++it2;
    ASSERT_FALSE(it1 == it2); // Iterator inequality after increment
}
TEST(list_test_copy_ctor) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    List<int> list2 = list1; // Copy construction
    ASSERT_EQUAL(list2.size(), 2);
    auto it = list2.begin();
    ASSERT_EQUAL(*it, 1); // Check copied values
    ++it;
    ASSERT_EQUAL(*it, 2);
}
TEST(list_test_iterate_backwards_from_end) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    auto it = list.end();
    --it; // Assuming pre-decrement is implemented
    ASSERT_EQUAL(*it, 2);
    --it;
    ASSERT_EQUAL(*it, 1);
}
TEST(list_test_postfix_iterator_operators) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    auto it = list.begin();
    it++; // Postfix increment
    ASSERT_EQUAL(*it, 2);
    it--; // Postfix decrement
    ASSERT_EQUAL(*it, 1);
}
TEST(list_test_default_iterators) {
    List<int> list;
    ASSERT_TRUE(list.begin() == list.end()); // Empty list check
    list.push_back(1);
    ASSERT_FALSE(list.begin() == list.end()); // Non-empty list check
}
TEST(list_test_insert_and_erase_4) {
    List<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.push_back(i);
    }
    // Insert at the third position
    auto it = list.begin();
    ++it; ++it;
    list.insert(it, 10);
    // Erase the fourth position (which now is 3 due to the previous insert)
    ++it;
    list.erase(it);
    ASSERT_EQUAL(list.size(), 5); // One insert and one erase = net zero change
    // Verify order
    it = list.begin();
    ASSERT_EQUAL(*it, 1); ++it;
    ASSERT_EQUAL(*it, 2); ++it;
    ASSERT_EQUAL(*it, 10); ++it; // 10 is inserted before 3
    ASSERT_EQUAL(*it, 4); // 3 is erased
}
TEST(list_edge_test_push_front_empty) {
    List<int> list;
    list.push_front(1);
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(*list.begin(), 1);
}
TEST(list_edge_test_push_back_empty) {
    List<int> list;
    list.push_back(1);
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(*list.begin(), 1);
}
TEST(list_edge_test_pop_front_single_element) {
    List<int> list;
    list.push_front(1);
    list.pop_front();
    ASSERT_TRUE(list.empty());
}
TEST(list_edge_test_pop_back_single_element) {
    List<int> list;
    list.push_back(1);
    list.pop_back();
    ASSERT_TRUE(list.empty());
}
TEST(list_edge_test_insert_at_beginning) {
    List<int> list;
    list.push_back(2); // Ensuring list is not empty for insert
    list.insert(list.begin(), 1); // Insert at the beginning
    ASSERT_EQUAL(*list.begin(), 1);
}
TEST(list_edge_test_insert_at_end) {
    List<int> list;
    list.push_back(1);
    list.insert(list.end(), 2); // Insert at the end, assuming List's insert matches std::list behavior
    auto it = list.begin();
    ++it;
    ASSERT_EQUAL(*it, 2);
}
TEST(list_edge_test_erase_at_beginning) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.erase(list.begin());
    ASSERT_EQUAL(*list.begin(), 2);
}
TEST(list_edge_test_erase_at_end_invalid) {
    List<int> list;
    list.push_back(1);
    // Intentionally not erasing at end since it should be an invalid operation
    // This test might compile but should be considered for documentation or static analysis
}
TEST(list_edge_test_iterator_increment_beyond_end) {
    List<int> list;
    list.push_back(1);
    auto it = list.begin();
    ++it;
    // Assuming reaching end() is expected, beyond that is edge
    ASSERT_TRUE(it == list.end());
    // Intentional lack of further increment to avoid undefined behavior
}
TEST(list_edge_test_empty_list_iterator_equality) {
    List<int> list;
    ASSERT_TRUE(list.begin() == list.end());
}

TEST_MAIN()

// TEST(test_begin_and_end){

// }



