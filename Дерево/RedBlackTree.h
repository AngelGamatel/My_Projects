#pragma once

#include<memory>
#include<string>
#include<iostream>

class RedBlackTree {
friend int main();
private:
	enum class Color{
		RED,
		BLACK
	};

	struct Conections_ {
		std::shared_ptr<Conections_> left;
		std::shared_ptr<Conections_> right;
		std::weak_ptr<Conections_> parent;
		Color color;

		Conections_(
			std::shared_ptr<Conections_> new_left, 
			std::shared_ptr<Conections_> new_right, 
			std::shared_ptr<Conections_> new_parent, 
			Color new_color
		);
		virtual ~Conections_() = default;
	};

	struct Node_ : Conections_ {
		std::string data;
		Node_(
			std::shared_ptr<Conections_> new_left,
			std::shared_ptr<Conections_> new_right,
			std::shared_ptr<Conections_> new_parent,
			Color new_color,
			const std::string& new_data
		);
	};
private:
	static Color GetColor(Conections_* node);
	
	static std::shared_ptr<Conections_> GetParent(std::shared_ptr<Conections_> node);
	static std::shared_ptr<Conections_> GetGrandfather(std::shared_ptr<Conections_> node);
	static std::shared_ptr<Conections_> GetUncle(std::shared_ptr<Conections_> node);

	static void Connect(std::shared_ptr<Conections_> child, std::shared_ptr<Conections_> parent);
	
	static std::shared_ptr<Conections_> LeftTurn(std::shared_ptr<Conections_> node);
	static std::shared_ptr<Conections_> RightTurn(std::shared_ptr<Conections_> node);

	static std::shared_ptr<Conections_> Find(std::shared_ptr<Conections_> node, const std::string& str);

	void Insert(std::shared_ptr<Conections_> node, const std::string& data);
	void Erase(std::shared_ptr<Conections_> node, const std::string& data);
	void EraseUp(std::shared_ptr<Conections_> node);
	std::shared_ptr<Conections_> FindMin(std::shared_ptr<Conections_> node) const;
	void Print(std::ostream& stream, size_t level, std::shared_ptr<Conections_> node) const;
private:
	size_t size_;
	std::shared_ptr<Conections_> root_;
	std::shared_ptr<Conections_> end_;
public:
	class Iterator {
		friend class RedBlackTree;
	private:
		std::shared_ptr<RedBlackTree::Conections_> ptr_;
	private:
		Iterator(std::shared_ptr<RedBlackTree::Conections_> ptr);
		void Next();
		void Prev();
	public:
		const std::string& operator*() const;
		const std::string* operator->() const;
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);
		bool operator==(Iterator other) const;
		bool operator!=(Iterator other) const;
	};
public:
	RedBlackTree();
	void Insert(const std::string& data);
	Iterator begin() const;
	Iterator end() const;
	size_t Size() const;
	Iterator Find(const std::string& data) const;
	void Erase(const std::string& data);
	void Print(std::ostream& stream, size_t level) const;
	~RedBlackTree() = default;
};
