#include <iostream>
#include <string>
#include "Test.h"
#include "RedBlackTree.h"
int main()
{
    InsertCorrectnessTest(std::cout);
    EraseCorrectnessTest(std::cout);
    SizeTest(std::cout);
    std::string str = "1";
    RedBlackTree tree;
    for (int i = 0; i < 5; i++)
    {
        if (RedBlackTree::GetColor(tree.root_.get()) == RedBlackTree::Color::BLACK) {
            std::cout << "BLACK\n";
        }
        else {
            std::cout << "RED\n";
        }
        tree.Insert(str);
        str = str + "1";
    }

    tree.Print(std::cout, 0);

    return 0;
}
