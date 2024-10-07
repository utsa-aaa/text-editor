#include "TextBuffer.hpp"

#include "TextBuffer.hpp"

// Constructor
TextBuffer::TextBuffer() : row(0), column(0), index(0) {
    cursor = data.end(); // Initialize cursor to the end of data
}

// Move cursor forward
bool TextBuffer::forward() {
    if (cursor != data.end()) { // Check if cursor is not at the end
        if (*cursor == '\n') { // If character at cursor is newline
            ++row; // Move to next row
            column = 0; // Reset column to 0
        } else {
            ++column; // Move to next column
        }
        ++index; // Move to next character index
        ++cursor; // Move cursor to next character
        return true;
    }
    return false; // Return false if cursor is at the end
}

// Move cursor backward
bool TextBuffer::backward() {
    // Check if cursor is not at the beginning
    if (cursor != data.begin()) { 
        --cursor; // Move cursor backward
        --index; // Move to previous character index
        if (*cursor == '\n') { // If character at cursor is newline
            --row; // Move to previous row
            column = compute_column(); // Recompute column position
        } else {
            --column; // Move to previous column
        }
        return true;
    }
    return false; // Return false if cursor is at the beginning
}

// Insert character at cursor position
void TextBuffer::insert(char c) {
    if (cursor == data.end()) { // If cursor is at the end
        data.push_back(c); // Insert character at the end
        if (c == '\n') { // If character is newline
            ++row; // Move to next row
            column = 0; // Reset column to 0
        } 
        else {
            ++column; // Move to next column
        }
        ++index; // Move to next character index
    } 
    else {
        if (c == '\n') { // If character is newline
            data.insert(cursor, c); // Insert character at cursor position
            ++row; // Move to next row
            column = 0; // Reset column to 0
        } 
        
            data.insert(cursor, c); // Insert character at cursor position
            ++column; // Move to next column
        
    }
}
//deals with /n
// Remove character at cursor position
bool TextBuffer::remove() {
if (is_at_end()) return false; // If already at the end
    cursor = data.erase(cursor); // Erase character at cursor position
    // If not at the end and current character is newline
    if (!is_at_end() && data_at_cursor() == '\n') { 
        ++row; // Move to the next row
        column = compute_column(); // Recompute column position
    }
    return true; // Successfully removed character
}


// Move cursor to the start of the current row
void TextBuffer::move_to_row_start() {
    // Move cursor to the beginning of the row
    while (cursor != data.begin() && *(--cursor) != '\n') { 
        --index; // Move to previous character index
    }
    if (*cursor == '\n') { // If cursor is at newline
        ++index; // Move to next character index
        ++cursor; // Move cursor to correct position
    }
    column = 0; // Reset column to 0
}

// Move cursor to the end of the current row
void TextBuffer::move_to_row_end() {
    // Move cursor to the end of the row
    while (cursor != data.end() && *cursor != '\n') { 
        ++cursor; // Move cursor to next character
        ++index; // Move to next character index
    }
    column = compute_column(); // Recompute column position
}

// Move cursor to a specific column
void TextBuffer::move_to_column(int new_column) {
    if (new_column >= 0) { // Check if new column is valid
        int diff = new_column - column; // Calculate column difference
        if (diff > 0) { // If moving to the right
            while (diff > 0 && cursor != data.end()) { // Move cursor to the right
                if (*cursor == '\n') { // If newline encountered
                    break; // Stop moving
                }
                ++cursor; // Move cursor to next character
                ++index; // Move to next character index
                --diff; // Decrease difference
            }
        } else if (diff < 0) { // If moving to the left
            while (diff < 0 && cursor != data.begin()) { // Move cursor to the left
                --cursor; // Move cursor to previous character
                --index; // Move to previous character index
                if (*cursor == '\n') { // If newline encountered
                    break; // Stop moving
                }
                ++diff; // Increase difference
            }
            if (*cursor == '\n') { // If cursor is at newline
                column = compute_column(); // Recompute column position
            }
        }
        column = new_column; // Update column position
    }
}

// Move cursor up one row
bool TextBuffer::up() {
    if (row == 0) return false; // If already at the first row
    int targetColumn = column; // Save current column
    move_to_row_start(); // Move cursor to the beginning of the row
    backward(); // Move to the end of the previous row
    //if (!is_at_end() && data_at_cursor() != '\n') 
    // If cursor is not at the beginning and not at a newline
        move_to_column(targetColumn); // Move to the desired column
        column = compute_column();
    return true; // Successfully moved up
}

// Move cursor down one row
bool TextBuffer::down() {
    int targetColumn = column; // Save current column
    move_to_row_end(); // Move cursor to the end of the row
    if(is_at_end()){
        return false;
    }
    forward(); // Move to the end of the previous row
    //if (!is_at_end() && data_at_cursor() != '\n') 
    // If cursor is not at the beginning and not at a newline
        move_to_column(targetColumn); // Move to the desired column
        column = compute_column();
    return true; // Successfully moved down
}

// Check if cursor is at the end of the text
bool TextBuffer::is_at_end() const {
    return cursor == data.end(); // Return true if cursor is at the end
}

// Get character at cursor position
char TextBuffer::data_at_cursor() const {
    if (cursor != data.end()) { // If cursor is not at the end
        return *cursor; // Return character at cursor
    }
    return '\0'; // Return null character if cursor is at the end
}

// Get current row
int TextBuffer::get_row() const {
    return row; // Return current row
}

// Get current column
int TextBuffer::get_column() const {
    return column; // Return current column
}

// Get current index
int TextBuffer::get_index() const {
    if (cursor != data.end()) { // If cursor is not at the end
        return index; // Return current index
    }
    return size(); // Return size if cursor is at the end
}

// Get size of the text
int TextBuffer::size() const {
    return data.size(); // Return size of the text
}

// Convert text data to string
std::string TextBuffer::stringify() const {
    // Convert text data to string
    return std::string(data.begin(), data.end()); 
}

// Compute current column position
int TextBuffer::compute_column() const {
    int count = 0; // Initialize count
    auto it = cursor; // Initialize iterator
    // Count characters until newline or beginning
    while (it != data.begin() && *(--it) != '\n') { 
        ++count; // Increment count
    }
    return count; // Return computed column position
}
