#include "TextBuffer.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}
// Test empty buffer initialization
TEST(test_empty_buffer) {
    TextBuffer tb;
    ASSERT_TRUE(tb.is_at_end());
    ASSERT_EQUAL(tb.get_row(), 1);
    ASSERT_EQUAL(tb.get_column(), 0);
    ASSERT_EQUAL(tb.get_index(), 0);
    ASSERT_EQUAL(tb.size(), 0);
}

// Test insertion of characters
TEST(test_insertion) {
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('\n');
    tb.insert('c');
    ASSERT_EQUAL(tb.size(), 4);
    ASSERT_EQUAL(tb.stringify(), "ab\nc");
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_EQUAL(tb.get_column(), 1); // 'c' is at column 1 of the 2nd row
}

// Test forward movement
TEST(test_forward_movement) {
    TextBuffer tb;
    std::string text = "ab\ncd";
    for (char ch : text) {
        tb.insert(ch);
    }
    tb.move_to_row_start(); // Move to start to test forward movement
    ASSERT_TRUE(tb.forward()); // Move to 'a'
    ASSERT_TRUE(tb.forward()); // Move to 'b'
    ASSERT_TRUE(tb.forward()); // Move to '\n', should transition to next row
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_EQUAL(tb.get_column(), 0); // Newline, so column resets
}

// Test backward movement
TEST(test_backward_movement) {
    TextBuffer tb;
    std::string text = "ab\ncd";
    for (char ch : text) {
        tb.insert(ch);
    }
    ASSERT_TRUE(tb.backward()); // Move back from end, should be at 'd'
    ASSERT_TRUE(tb.backward()); // Move to 'c'
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_EQUAL(tb.get_column(), 0); // 'c' is at the start of the 2nd row
}

// Test removal of characters
TEST(test_removal) {
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('\n');
    tb.insert('c');
    tb.backward(); // Move cursor back to '\n'
    ASSERT_TRUE(tb.remove()); // Remove '\n'
    ASSERT_EQUAL(tb.size(), 3);
    ASSERT_EQUAL(tb.stringify(), "abc");
    ASSERT_EQUAL(tb.get_row(), 1); // Back to row 1 after removing '\n'
}

// Test move to row and column
TEST(test_move_to_row_column) {
    TextBuffer tb;
    std::string text = "hello\nworld";
    for (char ch : text) {
        tb.insert(ch);
    }
    tb.move_to_row_start();
    tb.move_to_column(3); // Move to 'l' in "hello"
    ASSERT_EQUAL(tb.get_column(), 3);
    ASSERT_EQUAL(tb.data_at_cursor(), 'l');
    tb.move_to_row_end(); // Move to '\n' after "hello"
    ASSERT_TRUE(tb.is_at_end() || tb.data_at_cursor() == '\n');
}

// Test moving up and down between lines
TEST(test_up_down_movement) {
    TextBuffer tb;
    std::string text = "line1\nline2\nline3";
    for (char ch : text) {
        tb.insert(ch);
    }
    tb.move_to_row_start(); // Move to start of "line3"
    tb.up();
    ASSERT_EQUAL(tb.get_row(), 2); // Should be at "line2" now
    tb.down();
    ASSERT_EQUAL(tb.get_row(), 3); // Should be back at "line3"
}

TEST_MAIN()
