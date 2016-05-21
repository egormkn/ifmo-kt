#include "lazy_string.h"

lazy_string::lazy_char::lazy_char(lazy_string *ls, size_t index):
    index(index), ls(ls) {}

lazy_string::lazy_char::operator char() const  {
	return (*ls->ref)[ls->start + index];
}
    
lazy_string::lazy_char& lazy_string::lazy_char::operator=(char c) {
	if (ls->ref.use_count() > 1) {
		ls->start = 0;
		ls->ref = std::make_shared<std::string>(ls->ref->substr(ls->start, ls->width));
	}
	(*ls->ref)[ls->start + index] = c;
	return *this;
}

lazy_string::lazy_string(size_t s, size_t w, std::shared_ptr<std::string> r):
    start(s), width(w), ref(r) {}

lazy_string::lazy_string(const std::string &str) {
	mtx.lock();
	ref = std::make_shared<std::string>(str);
	start = 0;
	width = str.size();
	mtx.unlock();
}

lazy_string::operator std::string() const {
	return ref->substr(start, width);
}

size_t lazy_string::size() const {
	return width;
}

size_t lazy_string::length() const {
	return width;
}

lazy_string lazy_string::substr(size_t pos, size_t len) {
	if (pos > width) {
		throw std::out_of_range("pos > lazy_string length in substr");
	}
	return lazy_string(
		start + pos,
		pos + len > width ? (width - pos) : len,
		ref
	);
}

lazy_string::lazy_char lazy_string::at(size_t pos) {
	if (pos >= width) {
		throw std::out_of_range("pos >= lazy_string length in at");
	}
	return lazy_char(const_cast<lazy_string*>(this), pos);
}

const char& lazy_string::at(size_t pos) const {
	if (pos >= width) {
		throw std::out_of_range("pos >= lazy_string length in at");
	}
	return (*ref)[start + pos];
}

lazy_string::lazy_char lazy_string::operator[](size_t pos) {
	return lazy_char(const_cast<lazy_string *>(this), pos);
}

const char& lazy_string::operator[](size_t pos) const {
	return (*ref)[start + pos];
}

std::istream& operator>>(std::istream &is, lazy_string &ls) {
	auto ref = std::make_shared<std::string>();
	is >> *ref;
	ls.ref = ref;
	ls.start = 0;
	ls.width = ref->size();
	return is;
}

std::ostream& operator<<(std::ostream &os, lazy_string &ls) {
	for (size_t i = 0; i < ls.width; i++) {
		os << ls[i];
	}
	return os;
}
