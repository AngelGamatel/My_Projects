#include "Test.h"
#include "RedBlackTree.h"

#include<algorithm>
#include<vector>
#include<cassert>
#include<set>
#include<random>

const size_t DATA_SIZE = 1000;
const size_t TEST_STRING_SIZE = 5;
const size_t LETTERS_FOR_TEST = 10;

void InsertCorrectnessTest(std::ostream& stream) {
	stream << "InsertCorrectnessTest: ";
	std::random_device rd;
	std::vector<std::string> data(DATA_SIZE);
	for (auto& elem : data) {
		std::string str;
		for (size_t i = 0; i < TEST_STRING_SIZE; ++i) {
			str += rd() % LETTERS_FOR_TEST + 'a';
		}
		elem = str;
	}
	RedBlackTree tree;
	std::set<std::string> set;
	int i = 0;
	for (const auto& elem : data) {
		tree.Insert(elem);
		set.insert(elem);
	}

	auto it = tree.begin();
	auto set_it = set.begin();
	for (size_t i = 0; i < set.size(); ++i) {
		assert(*it == *set_it);
		++it;
		++set_it;
	}
	stream << "DONE\n";
}

void EraseCorrectnessTest(std::ostream& stream) {
	stream << "EraseCorrectnessTest: ";
	std::random_device rd;
	std::vector<std::string> data(DATA_SIZE);
	for (auto& elem : data) {
		std::string str;
		for (size_t i = 0; i < TEST_STRING_SIZE; ++i) {
			str += rd() % LETTERS_FOR_TEST + 'a';
		}
		elem = str;
	}
	RedBlackTree tree;
	std::set<std::string> set;
	for (const auto& elem : data) {
		tree.Insert(elem);
		set.insert(elem);
	}
	for (size_t i = 0; i < DATA_SIZE; i += 10) {
		tree.Erase(data[i]);
		set.erase(data[i]);
	}
	auto it = tree.begin();
	auto set_it = set.begin();
	for (size_t i = 0; i < set.size(); ++i) {
		assert(*it == *set_it);
		++it;
		++set_it;
	}
	stream << "DONE\n";
}

void SizeTest(std::ostream& stream) {
	std::random_device rd;
	stream << "SizeTest: ";
	std::vector<std::string> data(DATA_SIZE);
	for (auto& elem : data) {
		std::string str;
		for (size_t i = 0; i < TEST_STRING_SIZE; ++i) {
			str += rd() % LETTERS_FOR_TEST + 'a';
		}
		elem = str;
	}
	RedBlackTree tree;
	size_t i = 0;
	for (const auto& elem : data) {
		if (tree.Find(elem) == tree.end()) {
			++i;
		}
		tree.Insert(elem);
		assert(i == tree.Size());
	}
	stream << "DONE\n";
}
