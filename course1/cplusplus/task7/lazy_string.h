#ifndef LAZY_STRING_H
#define LAZY_STRING_H

/*
 *
 *
 *
 *
 *
 *
 * MinGW 4.9.3 has no mutex library :(
 *
 *
 *
 *
 *
 *
 *
 */
 
#include <memory>
#include <string>
#include <istream>
#include <ostream>
#include <mutex>

/**
 * @class lazy_string
 * 
 * @implements copy-on-write optimization strategy
 * 
 * @details Whenever a task attempts to make a change to the string,
 * it should first create a separate (private) copy of string
 * to prevent its changes from becoming visible to all the other tasks
 */

class lazy_string {
    struct lazy_char {
        friend class lazy_string;
        operator char() const;
        lazy_char& operator=(char c);

    private:
        size_t index;
        lazy_string *ls;
        lazy_char(lazy_string *ls, size_t index);
    };

private:
    size_t start, width;
    std::shared_ptr<std::string> ref;
    lazy_string(size_t s, size_t w, std::shared_ptr<std::string> r);
    std::mutex mtx;

public:
    /**
     * Constructor of lazy_string from std::string
     *
     * @param str
     * The std::string, which is used to initialize lazy_string
     * If `str` is empty, an empty lazy_string is constructed
     */
    lazy_string(const std::string &str = "");

    /**
     * Creates a std::string with a value of the current lazy_string
     *
     * @return The std::string with a value of lazy_string
     */
    operator std::string() const;

    /**
     * Returns the number of characters in the string
     *
     * @return The number of characters in the string
     */
    size_t size() const;

    /**
     * Returns the number of characters in the string
     *
     * @return The number of characters in the string
     */
    size_t length() const;

    /**
     * Returns a substring of lazy_string
     * Does not copy the buffer of the lazy_string
     *
     * @details The substring is the portion of the object that
     * starts at character position `pos` and spans `len` characters
     * (or until the end of the string, whichever comes first)
     *
     * @param pos Position of the first character to include
     * @param len Length of the substring
     *
     * @note The first character is denoted by a value of 0 (not 1)
     *
     * @return Substring of lazy_string
     *
     * @throws std::out_of_range If pos is greater than
     * the lazy_string length
     */
    lazy_string substr(size_t pos = 0, size_t len = std::string::npos);

    /**
     * Returns a reference to the character at specified position.
     *
     * @details The function automatically checks whether `pos`
     * is the valid position of a character in the string
     * (i.e., whether `pos` is less than the string length)
     *
     * @param pos Position of the character
     *
     * @return Reference to the character at position `pos`
     *
     * @throws std::out_of_range If `pos` is greater than or equals
     * lazy_string length
     */
    lazy_char at(size_t pos);
    const char& at(size_t pos) const;

    /**
     * Returns a reference to the character at specified location pos.
     * No bounds check is performed.
     *
     * @details If `pos` == lazy_string length, a reference to the null
     * character is returned. For the non-const version, the behavior
     * is undefined if this character is modified.
     *
     * @param pos Position of the character
     *
     * @return Reference to the character at position `pos`
     */
    lazy_char operator[](size_t pos);
    const char& operator[](size_t pos) const;

    /**
     * Extracts a string from the input stream `is`, storing the
     * sequence in `ls`, which is overwritten
     * (the previous value of lazy_string is replaced).
     *
     * @details This function overloads operator>> to behave
     * as described in istream::operator>> for c-strings, but applied
     * to lazy_string objects.
     * 
     * @param is std::istream object from which characters are extracted
     * @param ls lazy_string object where the extracted content is stored
     *
     * @return The same as parameter `is`.
     */
    friend std::istream& operator>>(std::istream &is, lazy_string &ls);

    /**
     * Inserts the sequence of characters that conforms value
     * of `str` into `os`.
     *
     * @details This function overloads operator<< to behave
     * as described in ostream::operator<< for c-strings, but applied
     * to lazy_string objects.
     * 
     * @param os std::ostream object where characters are inserted.
     * @param ls lazy_string object with the content to insert.
     *
     * @return The same as parameter `os`.
     */
    friend std::ostream& operator<<(std::ostream &os, lazy_string &ls);
};

#endif // LAZY_STRING_H
