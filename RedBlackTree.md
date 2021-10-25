Rules That Every Red-Black Tree Follows: 
1. BST
2. Every node has a colour either red or black.
3. The root of the tree is always black.
4. There are no two adjacent red nodes (A red node cannot have a red parent or red child).
5. Every path from a node (including root) to any of its descendants NULL nodes has the same number of black nodes.

1.	Search	O(log n)
2.	Insert	O(log n)
3.	Delete	O(log n)


Insertion Algorithm:
Let x be the newly inserted node.

1. Perform standard BST insertion and make the colour of newly inserted nodes as RED.
2. If x is the root, change the colour of x as BLACK (Black height of complete tree increases by 1).
3. Do the following if the color of x’s parent is not BLACK and x is not the root.   
  a) If x’s uncle is RED (Grandparent must have been black from property 4)  
     (i) Change the colour of parent and uncle as BLACK.  
     (ii) Colour of a grandparent as RED.  
     (iii) Change x = x’s grandparent, repeat steps 2 and 3 for new x.  
  b) If x’s uncle is BLACK, then there can be four configurations for x, x’s parent (p) and x’s grandparent (g) (This is similar to AVL Tree)  
     (i) Left Left Case (p is left child of g and x is left child of p)  
     (ii) Left Right Case (p is left child of g and x is the right child of p)  
     (iii) Right Right Case (Mirror of case i)  
     (iv) Right Left Case (Mirror of case ii)  
