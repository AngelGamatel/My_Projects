#include "RedBlackTree.h"

RedBlackTree::Conections_::Conections_(
	std::shared_ptr<Conections_> new_left,
	std::shared_ptr<Conections_> new_right,
	std::shared_ptr<Conections_> new_parent,
	Color new_color
) :
	left(new_left),
	right(new_right),
	parent(new_parent),
	color(new_color)
{}

RedBlackTree::Node_::Node_(
	std::shared_ptr<Conections_> new_left,
	std::shared_ptr<Conections_> new_right,
	std::shared_ptr<Conections_> new_parent,
	Color new_color,
	const std::string& new_data
) : 
	Conections_(new_left, new_right, new_parent, new_color),
	data(new_data)
{}

std::shared_ptr<RedBlackTree::Conections_> RedBlackTree::Find(std::shared_ptr<Conections_> node, const std::string& str) {
	if (node == nullptr) {
		return nullptr;
	}
	if (dynamic_cast<Node_*>(node.get())->data < str) {
		return Find(node->right, str);
	}
	if (dynamic_cast<Node_*>(node.get())->data > str) {
		return Find(node->left, str);
	}
	return node;
}

void RedBlackTree::Connect(std::shared_ptr<Conections_> child, std::shared_ptr<Conections_> parent) {
	if (child != nullptr) {
		child->parent = parent;
	}
}

std::shared_ptr<RedBlackTree::Conections_> RedBlackTree::LeftTurn(std::shared_ptr<Conections_> node) {
	std::shared_ptr<Conections_> right = node->right;
	node->right = right->left;
	right->left = node;
	Connect(right->left, right);
	Connect(node->right, node);
	return right;
}

std::shared_ptr<RedBlackTree::Conections_> RedBlackTree::RightTurn(std::shared_ptr<Conections_> node) {
	std::shared_ptr<Conections_> left = node->left;
	node->left = left->right;
	left->right = node;
	Connect(left->right, left);
	Connect(node->left, node);
	return left;
}

RedBlackTree::Color RedBlackTree::GetColor(Conections_* node) {
	if (node == nullptr) {
		return Color::BLACK;
	}
	return node->color;
}

std::shared_ptr<RedBlackTree::Conections_> RedBlackTree::GetParent(std::shared_ptr<RedBlackTree::Conections_> node) {
	return static_cast<std::shared_ptr<Conections_>>(node->parent);
}

std::shared_ptr<RedBlackTree::Conections_> RedBlackTree::GetGrandfather(std::shared_ptr<RedBlackTree::Conections_> node) {
	return GetParent(GetParent(node));
}

std::shared_ptr<RedBlackTree::Conections_> RedBlackTree::GetUncle(std::shared_ptr<RedBlackTree::Conections_> node) {
	Conections_* grandfather = GetGrandfather(node).get();
	if (GetParent(node) == grandfather->left) {
		return grandfather->right;
	}
	return grandfather->left;
}

void RedBlackTree::Insert(std::shared_ptr<Conections_> node, const std::string& data) {
	auto current = node;
	while (true) {
		if (dynamic_cast<Node_*>(node.get())->data < data) {
			if (node->right == nullptr) {
				node->right = std::make_shared<Node_>(nullptr, nullptr, node, Color::RED, data);
				current = node->right;
				++size_;
				break;
			}
			node = node->right;
			continue;
		}
		if (dynamic_cast<Node_*>(node.get())->data > data) {
			if (node->left == nullptr) {
				node->left = std::make_shared<Node_>(nullptr, nullptr, node, Color::RED, data);
				current = node->left;
				++size_;
				break;
			}
			node = node->left;
			continue;
		}
		return;
	}
	while (root_ != current) {
		auto parent = GetParent(current);
		if (GetColor(parent.get()) == Color::BLACK) {
			return;
		}
		auto uncle = GetUncle(current);
		auto grandfather = GetGrandfather(current);

		if (GetColor(uncle.get()) == Color::RED) {
			uncle->color = Color::BLACK;
			parent->color = Color::BLACK;
			grandfather->color = Color::RED;
			current = grandfather;
			continue;
		}

		if (grandfather->left == parent) {
			if (parent->right == current) {
				grandfather->left = LeftTurn(grandfather->left);
				Connect(grandfather->left, grandfather);
				std::swap(current, parent);
			}
			grandfather->color = Color::RED;
			parent->color = Color::BLACK;
			auto above = GetParent(grandfather);
			current = RightTurn(grandfather);

			if (above != end_) {
				if (above->left == grandfather) {
					above->left = current;
				}
				else {
					above->right = current;
				}
				Connect(current, above);
			}
			else {
				root_ = current;
				current->color = Color::BLACK;
				end_->left = root_;
				Connect(end_->left, end_);
			}
			break;
		}
		if (parent->left == current) {
			grandfather->right = RightTurn(grandfather->right);
			Connect(grandfather->right, grandfather);
			std::swap(current, parent);
		}
		grandfather->color = Color::RED;
		parent->color = Color::BLACK;
		auto above = GetParent(grandfather);
		current = LeftTurn(grandfather);

		if (above != end_) {
			if (above->left == grandfather) {
				above->left = current;
			}
			else {
				above->right = current;
			}
			Connect(current, above);
		}
		else {
			root_ = current;
			current->color = Color::BLACK;
			end_->left = root_;
			Connect(end_->left, end_);
		}
		break;
	}
	current->color = Color::BLACK;
}

RedBlackTree::Iterator::Iterator(std::shared_ptr<RedBlackTree::Conections_> ptr) : ptr_(ptr) {}

void RedBlackTree::Iterator::Next() {
	if (ptr_->right != nullptr) {
		ptr_ = ptr_->right;
		while (ptr_->left != nullptr) {
			ptr_ = ptr_->left;
		}
		return;
	}
	while (GetParent(std::shared_ptr<Conections_>(ptr_))->right == ptr_) {
		ptr_ = GetParent(std::shared_ptr<Conections_>(ptr_));
	}
	ptr_ = GetParent(std::shared_ptr<Conections_>(ptr_));
}


void RedBlackTree::Iterator::Prev() {
	if (ptr_->left != nullptr) {
		ptr_ = ptr_->left;
		while (ptr_->right != nullptr) {
			ptr_ = ptr_->right;
		}
		return;
	}
	while (GetParent(std::shared_ptr<Conections_>(ptr_))->left == ptr_) {
		ptr_ = GetParent(std::shared_ptr<Conections_>(ptr_));
	}
	ptr_ = GetParent(std::shared_ptr<Conections_>(ptr_));
}

const std::string& RedBlackTree::Iterator::operator*() const {
	return dynamic_cast<Node_*>(ptr_.get())->data;
}

const std::string* RedBlackTree::Iterator::operator->() const {
	return &(dynamic_cast<Node_*>(ptr_.get())->data);
}

typename RedBlackTree::Iterator& RedBlackTree::Iterator::operator++() {
	Next();
	return *this;
}

typename RedBlackTree::Iterator RedBlackTree::Iterator::operator++(int) {
	Iterator copy(*this);
	Next();
	return *this;
}

typename RedBlackTree::Iterator& RedBlackTree::Iterator::operator--() {
	Prev();
	return *this;
}

typename RedBlackTree::Iterator RedBlackTree::Iterator::operator--(int) {
	Iterator copy(*this);
	Prev();
	return *this;
}

bool RedBlackTree::Iterator::operator==(Iterator other) const {
	return ptr_ == other.ptr_;
}

bool RedBlackTree::Iterator::operator!=(Iterator other) const {
	return ptr_ != other.ptr_;
}

RedBlackTree::RedBlackTree(): 
	size_(0), 
	root_(nullptr), 
	end_(std::make_shared<Conections_>(nullptr, nullptr, nullptr, Color::RED)) 
{}

void RedBlackTree::Insert(const std::string& data) {
	if (size_ == 0) {
		root_ = std::make_shared<Node_>(nullptr, nullptr, end_, Color::BLACK, data);
		end_->left = root_;
		Connect(root_, end_);
		++size_;
		return;
	}
	Insert(root_, data);
}

typename RedBlackTree::Iterator RedBlackTree::begin() const {
	auto current = end_;
	while (current->left != nullptr) {
		current = current->left;
	}
	return Iterator(current);
}

typename RedBlackTree::Iterator RedBlackTree::end() const {
	return Iterator(end_);
}

size_t RedBlackTree::Size() const {
	return size_;
}

typename RedBlackTree::Iterator RedBlackTree::Find(const std::string& data) const {
	auto find = Find(root_, data);
	if (find == nullptr) {
		return end();
	}
	return Iterator(find);
}

void RedBlackTree::Erase(std::shared_ptr<RedBlackTree::Conections_> node, const std::string& data) {
	while (node != nullptr) {
		if (dynamic_cast<Node_*>(node.get())->data < data) {
			node = node->right;
			continue;
		} 
		if (dynamic_cast<Node_*>(node.get())->data > data) {
			node = node->left;
			continue;
		}
		break;
	}
	if (node == nullptr) {
		return;
	}
	--size_;
	if (node->left == nullptr && node->right == nullptr) {
		if (GetColor(node.get()) == Color::RED) {
			auto parent = GetParent(node);
			if (parent->left == node) {
				parent->left = nullptr;
			}
			else if(parent->right == node) {
				parent->right = nullptr;
			}
			return;
		}
		EraseUp(node);
		return;
	}
	if (node->right.get() == nullptr) {
		auto parent = GetParent(node);
		node->left->color = node->color;
		if (parent->left == node) {
			parent->left = node->left;
		}
		else {
			parent->right = node->left;
		}
		if (node == root_) {
			root_ = node->left;
		}
		Connect(node->left, parent);
		return;
	}
	if (node->left.get() == nullptr) {
		auto parent = GetParent(node);
		node->right->color = node->color;
		if (parent->right == node) {
			parent->right = node->right;
		}
		else {
			parent->left = node->right;
		}
		if (node == root_) {
			root_ = node->right;
		}
		Connect(node->right, parent);
		return;
	}
	auto min = FindMin(node->right);
	dynamic_cast<Node_*>(node.get())->data = dynamic_cast<Node_*>(min.get())->data;
	Erase(min, dynamic_cast<Node_*>(min.get())->data);

}

std::shared_ptr<RedBlackTree::Conections_> RedBlackTree::FindMin(std::shared_ptr<RedBlackTree::Conections_> node) const {
	while (node->left != nullptr) {
		node = node->left;
	}
	return node;
}

void RedBlackTree::EraseUp(std::shared_ptr<RedBlackTree::Conections_> node) {
	bool from_left;
	auto parent = GetParent(node);
	if (parent->left == node) {
		from_left = true;
		parent->left = nullptr;
	}
	else {
		from_left = false;
		parent->right = nullptr;
	}
	if (root_ == node) {
		root_ = nullptr;
		end_->left = nullptr;
		return;
	}
	while (parent != end_) {
		if (from_left) {
			if (GetColor(parent->right.get()) == Color::RED) {
				auto above = GetParent(parent);
				auto current = LeftTurn(parent);
				current->color = Color::BLACK;
				current->left->color = Color::RED;
				if (above->left == parent) {
					above->left = current;
				}
				else {
					above->right = current;
				}
				Connect(current, above);
				parent = current->left;
			}
			if (GetColor(parent->right->left.get()) == Color::BLACK &&
				GetColor(parent->right->right.get()) == Color::BLACK) {
				parent->color = Color::BLACK;
				parent->right->color = Color::RED;
				auto above = GetParent(parent);
				if (above == end_ || above->color == Color::RED) {
					return;
				}
				if (above->left == parent) {
					from_left = true;
				}
				else {
					from_left = false;
				}
				parent = above;
				continue;
			}
			if (GetColor(parent->right->right.get()) == Color::BLACK) {
				parent->right->left->color = Color::BLACK;
				parent->right->color = Color::RED;
				parent->right = RightTurn(parent->right);
				Connect(parent->right, parent);
			}
			parent->right->color = parent->color;
			parent->right->right->color = Color::BLACK;
			parent->color = Color::BLACK;
			auto above = GetParent(parent);
			auto current = LeftTurn(parent);
			if (above->left == parent) {
				above->left = current;
			}
			else {
				above->right = current;
			}
			Connect(current, above);
			root_ = end_->left;
			return;
		}
		if (GetColor(parent->left.get()) == Color::RED) {
			auto above = GetParent(parent);
			auto current = RightTurn(parent);
			current->color = Color::BLACK;
			current->right->color = Color::RED;
			if (above->left == parent) {
				above->left = current;
			}
			else {
				above->right = current;
			}
			parent = current->right;
			Connect(current, above);
		}
		if (GetColor(parent->left->right.get()) == Color::BLACK &&
			GetColor(parent->left->left.get()) == Color::BLACK) {
			parent->color = Color::BLACK;
			parent->left->color = Color::RED;
			auto above = GetParent(parent);
			if (above == end_ || above->color == Color::RED) {
				return;
			}
			if (above->left == parent) {
				from_left = true;
			}
			else {
				from_left = false;
			}
			parent = above;
			continue;
		}
		if (GetColor(parent->left->left.get()) == Color::BLACK) {
			parent->left->right->color = Color::BLACK;
			parent->left->color = Color::RED;
			parent->left = LeftTurn(parent->left);
			Connect(parent->left, parent);
		}
		parent->left->color = parent->color;
		parent->left->left->color = Color::BLACK;
		parent->color = Color::BLACK;
		auto above = GetParent(parent);
		auto current = RightTurn(parent);
		if (above->left == parent) {
			above->left = current;
		}
		else {
			above->right = current;
		}
		Connect(current, above);
		if (parent == root_) {
			root_ = current;
		}
		return;
	}
}

void RedBlackTree::Erase(const std::string& data) {
	Erase(root_, data);
}

void RedBlackTree::Print(std::ostream& stream, size_t level, std::shared_ptr<Conections_> node) const {
	if (node == nullptr) {
		return;
	}
	if (level == 0) {
		stream << dynamic_cast<Node_*>(node.get())->data << std::endl;
		return;
	}
	Print(stream, level - 1, node->right);
	Print(stream, level - 1, node->left);
}

void RedBlackTree::Print(std::ostream& stream, size_t level) const
{
  Print(stream, level, root_);
}
