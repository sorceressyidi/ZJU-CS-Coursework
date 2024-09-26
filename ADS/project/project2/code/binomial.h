#ifndef _BINOMIAL_HEADER
#define _BINOMIAL_HEADER
typedef struct BinomialNode *BinNode;
struct BinomialNode {
    int value;
    int vertex;
    int degree;
    BinNode parent; // parent node
    BinNode child;  // child node
    BinNode sibling; // sibling node
};
BinNode newBinNode(int value, int vertex); // create a new binomial node
BinNode BinomialLink(BinNode node, BinNode child); // link two binomial nodes
BinNode BinomialMerge(BinNode node1, BinNode node2); // merge two binomial nodes
BinNode* BinGetMin2(BinNode node); // get the minimum node in the binomial heap
BinNode BinDeleteMin(BinNode node); // delete the minimum node in the binomial heap
BinNode BinInsert(BinNode node, BinNode binnode); // insert a new node into the binomial heap
void BinDecrease(BinNode binnode, int value, BinNode* NodeArray); // decrease the value of a node in the binomial heap
int IsBinEmpty(BinNode node);// check if the binomial heap is empty
#endif