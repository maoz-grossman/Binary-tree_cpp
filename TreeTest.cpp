/**
 * Examples of automatic tests for the exercise on binary trees.
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 */

#include <iostream>
using std::cout, std::endl;
#include "badkan.hpp"
#include "Tree.hpp"

int main() {
//init tree objects
ariel::Tree emptytree;
ariel::Tree threetree; 
ariel::Tree fivetree;
ariel::Tree sixtree;
ariel::Tree tentree;
ariel::Tree diagtree;
ariel::Tree mytree; 

  //creating a tree  size 3
  threetree.insert(5);
  threetree.insert(7);
  threetree.insert(3);

  badkan::TestCase tc("Binary tree");
  tc
  //some empty tree tests
  .CHECK_EQUAL (emptytree.size(), 0)
  .CHECK_OK    (emptytree.insert(5))
  .CHECK_EQUAL (emptytree.size(), 1)
  .CHECK_EQUAL (emptytree.contains(5), true)
  .CHECK_OK  (emptytree.remove(5))
  .CHECK_EQUAL (emptytree.contains(5), false)
  .CHECK_THROWS(emptytree.remove(5))
  .CHECK_EQUAL (emptytree.size() ,0)
  
  //tree size 3 tests
  .CHECK_THROWS (threetree.parent(5))
  .CHECK_EQUAL (threetree.parent(7), 5)
  .CHECK_EQUAL (threetree.size(), 3)
  .CHECK_EQUAL (threetree.root(), 5)
  .CHECK_EQUAL (threetree.parent(3), 5)
  .CHECK_EQUAL (threetree.parent(7), 5)
  .CHECK_EQUAL (threetree.left(5), 3)
  .CHECK_EQUAL (threetree.right(5), 7)
  .CHECK_THROWS(threetree.insert(3))
  .CHECK_THROWS(threetree.left(6))
  .CHECK_OK    (threetree.print())
  
  //creating a tree  size 5
  .CHECK_OK(fivetree.insert(10))
  .CHECK_OK(fivetree.insert(13))
  .CHECK_OK(fivetree.insert(8))
  .CHECK_OK(fivetree.insert(22))
  .CHECK_OK(fivetree.insert(12))
  .CHECK_EQUAL(fivetree.size(),5)
  .CHECK_OK(fivetree.remove(8))
  //check contains function after remove function
  .CHECK_EQUAL(fivetree.contains(8),false)
  //check remove node that already removed
  .CHECK_THROWS(fivetree.remove(8))
  .CHECK_EQUAL (fivetree.root(), 10)
  .CHECK_OK    (fivetree.print())
  
  //creating a tree  size 6
  .CHECK_OK(sixtree.insert(60))
  .CHECK_OK(sixtree.insert(49))
  .CHECK_OK(sixtree.insert(2))
  .CHECK_OK(sixtree.insert(70))
  .CHECK_OK(sixtree.insert(1))
  .CHECK_OK(sixtree.insert(10))
  .CHECK_EQUAL(sixtree.size(),6)
  .CHECK_OK(sixtree.remove(60))
  .CHECK_EQUAL(sixtree.root(),70)
  .CHECK_EQUAL(sixtree.size(),5)
  .CHECK_EQUAL(sixtree.left(70),49)
  .CHECK_OK    (sixtree.print())

  //creating a tree  size 10
  .CHECK_OK(tentree.insert(42))
  .CHECK_OK(tentree.insert(4))
  .CHECK_OK(tentree.insert(100))
  .CHECK_OK(tentree.insert(34))
  .CHECK_OK(tentree.insert(12))
  .CHECK_THROWS(tentree.insert(12))
  .CHECK_OK(tentree.insert(11))
  .CHECK_OK(tentree.insert(-5))
  .CHECK_OK(tentree.insert(7))
  .CHECK_OK(tentree.insert(85))
  .CHECK_OK(tentree.insert(53))
  .CHECK_OK(tentree.remove(4))
  //test correctness for binary tree
  .CHECK_EQUAL(tentree.right(7),34)
  .CHECK_OK(tentree.remove(42))
  .CHECK_EQUAL (tentree.parent(12),34)
  .CHECK_EQUAL(tentree.root(),53)
  //check size function after to delete function calls
  .CHECK_EQUAL(tentree.size(),8)
  .CHECK_OK    (tentree.print())
  
  //creating a diagonal shape
  .CHECK_OK(diagtree.insert(0))
  .CHECK_OK(diagtree.insert(-1))
  .CHECK_OK(diagtree.insert(-2))
  .CHECK_OK(diagtree.insert(-4))
  //check correctness for diagonal shape
  .CHECK_THROWS (diagtree.right(0)) 
  .CHECK_THROWS (diagtree.right(-1)) 
  .CHECK_THROWS (diagtree.right(-2)) 
  .CHECK_THROWS (diagtree.right(-4))
  .CHECK_EQUAL(diagtree.left(0),-1)
  .CHECK_EQUAL(diagtree.left(-1),-2)
  .CHECK_EQUAL(diagtree.left(-2),-4)
  .CHECK_THROWS(diagtree.left(-4))
  //print diagonal shape
  .CHECK_OK    (diagtree.print())
  //empty the tree and check size
  .CHECK_OK(diagtree.remove(-4))
  .CHECK_OK(diagtree.remove(-2))
  .CHECK_OK(diagtree.remove(-1))
  .CHECK_OK(diagtree.remove(0))
  .CHECK_EQUAL(diagtree.size(),0);

  
//some automatic tests for tree size 100
  for(int i = 1; i<=100; i++){
  tc
  .CHECK_EQUAL (mytree.contains(i),false)
  .CHECK_OK (mytree.insert(i))
  .CHECK_EQUAL(mytree.size(),i)
  .CHECK_EQUAL (mytree.contains(i),true)
  .CHECK_OK (mytree.remove(i))
  .CHECK_EQUAL(mytree.size(),i-1)
 .CHECK_EQUAL (mytree.contains(i),false)
  .CHECK_OK (mytree.insert(i));
  
  }
  tc.print();

  cout << "You have " << tc.right() << " right answers and " << tc.wrong() << " wrong answers so your grade is " << tc.grade() << ". Great!" << endl;
}