#include<iostream>
#include<queue>
#include<stack>
using namespace std;
template<class T>
class BinaryTreeNode {
private:
	T element;
	BinaryTreeNode<T>* leftChild;
	BinaryTreeNode<T>* rightChild;
	BinaryTreeNode<T>* parent;
public:
	BinaryTreeNode() {
		element = 0;
		leftChild = rightChild = parent = NULL;
	}
	BinaryTreeNode(const T& ele) {
		element = ele;
		leftChild = rightChild = parent = NULL;
	}
	BinaryTreeNode(const T&ele, BinaryTreeNode* l, BinaryTreeNode* r) {
		element = ele;
		parent = NULL;
		leftChild = l;
		rightChild = r;
	}
	BinaryTreeNode(const T&ele, BinaryTreeNode* l, BinaryTreeNode* r, BinaryTreeNode* p) {
		element = ele;
		parent = p;
		leftChild = l;
		rightChild = r;
	}
	BinaryTreeNode<T>* getLeftChild() const {
		return leftChild;
	}
	BinaryTreeNode<T>* getRightChild() const {
		return rightChild;
	}
	BinaryTreeNode<T>* getParent() const {
		return parent;
	}
	void setLeftChild(BinaryTreeNode<T>* l) {
		leftChild = l;
	}
	void setRightChild(BinaryTreeNode<T>* r) {
		rightChild = r;
	}
	T getValue() const {
		return element;
	}
	void setValue(const T& val) {
		element = val;
	}
	bool isLeaf() const {
		if (leftChild == NULL&&rightChild == NULL) {
			return 1;
		}
		else {
			return 0;
		}
	}
};
template<class T>
class BinaryTree {
private:
	BinaryTreeNode<T>* root;
	int height;
	int width;
	int du0;
	int du1;
	int du2;
	int max;
public:
	BinaryTree(BinaryTreeNode<T>* root) {
		this->root = root;
		du0 = du1 = du2 = 0;
		height = width = 0;
		max = root->getValue();
	}
	~BinaryTree() {}
	bool isEmpty() const {
		if (root == NULL)
			return 1;
		else
			return 0;
	}
	BinaryTreeNode<T>* getRoot() const {
		return root;
	}
	BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* current)const {
		return current->getParent();
	}
	BinaryTreeNode<T>* getLeftSibling(BinaryTreeNode<T>* current)const {
		BinaryTreeNode<T>* pre = getParent(current);
		return pre->getLeftChild();
	}
	BinaryTreeNode<T>* getRightSibling(BinaryTreeNode<T>* current)const {
		BinaryTreeNode<T>* pre = getParent(current);
		return pre->getRightChild();
	}
	void breadthFirstOrder(BinaryTreeNode<T>* root);
	void preOrder(BinaryTreeNode<T>* root) {
		if (root != NULL) {
			visit(root);
			preOrder(root->getLeftChild());
			preOrder(root->getRightChild());
		}
	}
	void preOrderForJudge(BinaryTreeNode<T>* root, int i, int *arr) {
		if (root != NULL) {
			visit(root);
			preOrder(root->getLeftChild());
			preOrder(root->getRightChild());
		}
	}
	void preOrderForShow(BinaryTreeNode<T>* root) {
		if (root != NULL) {
			cout << root->getValue();
			preOrderForShow(root->getLeftChild());
			preOrderForShow(root->getRightChild());
		}
	}
	void preOrderDel(BinaryTreeNode<T>* root) {
		if (root != NULL) {
			if ((root->getLeftChild()) != NULL && (root->getLeftChild())->isLeaf()) {
				root->setLeftChild(NULL);
			}
			if ((root->getRightChild()) != NULL && (root->getRightChild())->isLeaf()) {
				root->setRightChild(NULL);
			}

			preOrderDel(root->getLeftChild());
			preOrderDel(root->getRightChild());
		}
	}
	void inOrder(BinaryTreeNode<T>* root, int i, int *arr) {
		int temp = i + 1;
		if (root != NULL) {
			inOrder(root->getLeftChild(), temp, arr);
			arr[i]++;
			inOrder(root->getRightChild(), temp, arr);
		}
	}
	void postOrder(BinaryTreeNode<T>* root) {
		if (root != NULL) {
			postOrder(root->getLeftChild());
			postOrder(root->getRightChild());
			change(root);
		}
	}
	void change(BinaryTreeNode<T>* root) {
		BinaryTreeNode<T>* temp;
		temp = root->getLeftChild();
		root->setLeftChild(root->getRightChild());
		root->setRightChild(temp);
	}
	void visit(BinaryTreeNode<T>* current) {
		if (current->getValue() > max)
			max = current->getValue();
		if (current->getLeftChild() == NULL&&current->getRightChild() == NULL) {
			du0++;
		}
		else if ((current->getLeftChild() == NULL)^(current->getRightChild() == NULL)) {
			du1++;
		}
		else {
			du2++;
		}
	}
	void levelOrder(BinaryTreeNode<T>* root) {
		int flag = 0;
		queue<BinaryTreeNode<T>*> nodeQueue;
		BinaryTreeNode<T>* pointer = root;
		if (pointer) {
			nodeQueue.push(pointer);
		}
		while (!nodeQueue.empty()) {
			pointer = nodeQueue.front();
			visit(pointer);
			nodeQueue.pop();
			if (pointer->getLeftChild()) {
				nodeQueue.push(pointer->getLeftChild());
			}
			if (pointer->getRightChild()) {
				nodeQueue.push(pointer->getRightChild());
			}
		}
	}
	void PostOrderWithoutRecusion(BinaryTreeNode<T>* root, int* arr) {
		int i = 0;
		stack<BinaryTreeNode<T>*> nodeStack;
		BinaryTreeNode<T>* pointer = root;
		BinaryTreeNode<T>*pre = root;
		a[i] = 0;
		while (pointer) {
			for (; pointer->getLeftChild() != NULL; pointer = pointer->getLeftChild()) {
				nodeStack.push(pointer);
				a[i]++;
			}
			while (pointer != NULL && (pointer->getRightChild == NULL || pointer->getRightChild == pre)) {
				a[i]++;
				pre = pointer;
				if (nodeStack.empty())
					return;
				pointer = nodeStack.top();
				nodeStack.pop();
			}
			nodeStack.push(pointer);
			i++;
			a[i] = a[i - 1] - 1;
			pointer = pointer->getRightChild();
		}

	}
	bool isBinaryTree(BinaryTreeNode<T>* root) {
		queue<BinaryTreeNode<T>*> tA;
		queue<BinaryTreeNode<T>*> tB;
		queue<BinaryTreeNode<T>*>* point;
		int warnning1 = 0, warnning2 = 0;
		int aleadySet = 0;
		point = &tA;
		int presize = 0;
		int times = 0;
		int length = 1;
		if (root != NULL) {
			tA.push(root);
			while (!*point->empty()) {
				if ((*point->front())->getLeftChild() == NULL || (*point->front())->getRightChild() == NULL) {
					warnning1 = 1;
					if (aleadySet == 0)
					{
						presize = *point->size();
						aleadySet = 1;
					}

				}
				if ((*point->front())->getLeftChild() != NULL) {
					tB.push((*point->front())->getLeftChild());

				}


			}
		}
		}
	void deleteBinaryTree(BinaryTreeNode<T>* root) {

			}
			void showDu() {
				cout << "Du 0: " << du0 << endl;
				cout << "Du 1: " << du1 << endl;
				cout << "Du 2: " << du2 << endl;
			}
			int getLeafNum() {
				return du0;
			}
			int getMax() {
				return max;
			}
		};
		template<class T>
		int hight(BinaryTreeNode<T>* root) {
			if (root == NULL)
				return 0;
			else
				return max(hight(root->getLeftChild()), hight(root->getRightChild())) + 1;
		}
		template<class T>
		void width(BinaryTreeNode<T>* root, int * arr)
		{
			if (root == NULL)
				return 0;
			else
				return width(root->getLeftChild()) + width(root->getRightChild()) + 1;
		}
		template<class T>
		bool ComplateTree(BinaryTreeNode<T>* bt)
		{
			BinaryTreeNode<T>* p = bt;
			queue<BinaryTreeNode<T>*> q;
			int tag = 0;
			if (p == NULL) 
			return true;
			q.push(p);
			while (!q.empty())
			{
				p = q.front();
				q.pop();
				if (p->getLeftChild() && !tag)
					q.push(p->getLeftChild());
				else if (p->getLeftChild())
					return 0;
				else tag = 1;
				if (p->getRightChild() && !tag)
					q.push(p->getRightChild());
				else if (p->getRightChild())
					return 0;
				else tag = 1;
			}
			return 1;
		}
		template<class T>
		bool ComplateTree2(BinaryTreeNode<T>* root)
		{
			int flag = 0;
			if (!root)
				return true;
			else {
				queue<BinaryTreeNode<T>*> qe;
				qe.push(root);
				while (!qe.empty()) {
					BinaryTreeNode<T>* pointer = qe.front();
					qe.pop();
					if (flag == 1) {
						if (pointer->getLeftChild() != NULL)
							return false;
						if (pointer->getRightChild() != NULL)
							return false;
					}
					if (flag == 0) {
						if (pointer->getLeftChild() != NULL)
							qe.push(pointer->getLeftChild());
						else
							flag = 1;
						
					}
					if (flag == 1) {
						if (pointer->getRightChild() != NULL)
							return false;
					}
					if (flag == 0) {
						if (pointer->getRightChild() != NULL)
							qe.push(pointer->getRightChild());
						else
							flag = 1;
					}
				}
				return true;
			}
		}
		int main() {
			//建立一个树。
			BinaryTreeNode<int> *GrandPa = new BinaryTreeNode<int>;
			GrandPa->setValue(1);
			BinaryTreeNode<int> *Father = new BinaryTreeNode<int>;
			Father->setValue(2);
			BinaryTreeNode<int> *Son = new BinaryTreeNode<int>;
			Son->setValue(4);
			BinaryTreeNode<int> *Sonson = new BinaryTreeNode<int>;
			Sonson->setValue(8);
			BinaryTreeNode<int> *Daughter = new BinaryTreeNode<int>;
			Daughter->setValue(5);
			BinaryTreeNode<int> *Mother = new BinaryTreeNode<int>;
			Mother->setValue(3);
			BinaryTreeNode<int> *Moson = new BinaryTreeNode<int>;
			Moson->setValue(6);
			BinaryTreeNode<int> *Moghter = new BinaryTreeNode<int>;
			Moghter->setValue(7);
			GrandPa->setLeftChild(Father);
			GrandPa->setRightChild(Mother);
			Father->setLeftChild(Son);
			Father->setRightChild(Daughter);
			Mother->setLeftChild(Moson);
			Mother->setRightChild(Moghter);
			Son->setLeftChild(Sonson);
			BinaryTree<int> tree(GrandPa);
			tree.preOrder(GrandPa);
			cout << "show tree in pre order." << endl;
			tree.preOrderForShow(GrandPa);
			cout << endl;
			//pan duan wan quan
			cout << "Is it a complete tree?" << endl;
			if (ComplateTree2(GrandPa)) {
				cout << "Yes" << endl;
			}
			else
				cout << "No" << endl;
			//统计度数
			tree.showDu();
			//计算高度
			int i = hight(GrandPa);
			cout << "hight is " << i << endl;
			int *arr = new int[i];
			for (int a = 0; a < i; a++) {
				arr[a] = 0;
			}
			tree.inOrder(GrandPa, 0, arr);
			int max = arr[0];
			for (int a = 0; a < i; a++) {
				if (max < arr[a]) {
					max = arr[a];
				}
			}
			cout << "width is " << max << endl;
			for (int a = 0; a < i; a++) {
				cout << arr[a] << endl;
			}
			cout << "the max is " << tree.getMax() << endl;
			
			cout << "After change direction" << endl;
			tree.postOrder(GrandPa);
			tree.preOrderForShow(GrandPa);
			cout << endl;
			cout << "After delete leaf." << endl;
			tree.preOrderDel(GrandPa);
			tree.preOrderForShow(GrandPa);
			cout << endl;
			//pan duan wan quan
			cout << "Is it a complete tree?" << endl;
			if (ComplateTree2(GrandPa)) {
				cout << "Yes" << endl;
			}
			else
				cout << "No" << endl;
		}

	

