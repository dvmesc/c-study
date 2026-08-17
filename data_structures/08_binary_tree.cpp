#include <iostream>

using namespace std;

// 普通二叉树节点，不要求满足搜索树性质。
struct Node {
    char data;
    Node* left;
    Node* right;

    explicit Node(char value) : data(value), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    Node* root;

    // 手工构造一棵示例二叉树，便于统一演示。
    Node* buildSampleTree() {
        // 构造如下二叉树：
        //        A
        //      /   \
        //     B     C
        //    / \     \
        //   D   E     F
        Node* a = new Node('A');
        Node* b = new Node('B');
        Node* c = new Node('C');
        Node* d = new Node('D');
        Node* e = new Node('E');
        Node* f = new Node('F');

        a->left = b;
        a->right = c;
        b->left = d;
        b->right = e;
        c->right = f;
        return a;
    }

    // 先序递归遍历。
    void preorder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        cout << node->data << ' ';
        preorder(node->left);
        preorder(node->right);
    }

    // 中序递归遍历。
    void inorder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->data << ' ';
        inorder(node->right);
    }

    // 后序递归遍历。
    void postorder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        postorder(node->left);
        postorder(node->right);
        cout << node->data << ' ';
    }

    // 统计总结点个数。
    int countNodes(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        return countNodes(node->left) + countNodes(node->right) + 1;
    }

    // 统计叶子结点个数。
    int countLeaves(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }
        return countLeaves(node->left) + countLeaves(node->right);
    }

    // 计算二叉树高度。
    int height(Node* node) const {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    // 层序遍历，本质上是队列的应用。
    void levelOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }

        Node* queue[50];
        int front = 0;
        int rear = 0;
        queue[rear++] = node;

        while (front < rear) {
            Node* current = queue[front++];
            cout << current->data << ' ';

            if (current->left != nullptr) {
                queue[rear++] = current->left;
            }
            if (current->right != nullptr) {
                queue[rear++] = current->right;
            }
        }
    }

    // 后序释放整棵树，避免内存泄漏。
    void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    // 初始化为空树。
    BinaryTree() : root(nullptr) {}

    // 析构时释放整棵树。
    ~BinaryTree() {
        destroy(root);
    }

    // 构造演示用样例树。
    void buildSample() {
        root = buildSampleTree();
    }

    // 输出先序递归遍历结果。
    void printPreorder() const {
        preorder(root);
        cout << '\n';
    }

    // 输出中序递归遍历结果。
    void printInorder() const {
        inorder(root);
        cout << '\n';
    }

    // 输出后序递归遍历结果。
    void printPostorder() const {
        postorder(root);
        cout << '\n';
    }

    // 输出层序遍历结果。
    void printLevelOrder() const {
        levelOrder(root);
        cout << '\n';
    }

    // 输出先序非递归遍历结果。
    void printPreorderNonRecursive() const {
        if (root == nullptr) {
            return;
        }

        Node* stack[50];
        int top = -1;
        stack[++top] = root;

        while (top >= 0) {
            Node* current = stack[top--];
            cout << current->data << ' ';

            if (current->right != nullptr) {
                stack[++top] = current->right;
            }
            if (current->left != nullptr) {
                stack[++top] = current->left;
            }
        }
        cout << '\n';
    }

    // 输出中序非递归遍历结果。
    void printInorderNonRecursive() const {
        Node* stack[50];
        int top = -1;
        Node* current = root;

        while (current != nullptr || top >= 0) {
            while (current != nullptr) {
                stack[++top] = current;
                current = current->left;
            }

            current = stack[top--];
            cout << current->data << ' ';
            current = current->right;
        }
        cout << '\n';
    }

    // 输出后序非递归遍历结果。
    void printPostorderNonRecursive() const {
        if (root == nullptr) {
            return;
        }

        Node* stack1[50];
        Node* stack2[50];
        int top1 = -1;
        int top2 = -1;
        stack1[++top1] = root;

        while (top1 >= 0) {
            Node* current = stack1[top1--];
            stack2[++top2] = current;

            if (current->left != nullptr) {
                stack1[++top1] = current->left;
            }
            if (current->right != nullptr) {
                stack1[++top1] = current->right;
            }
        }

        while (top2 >= 0) {
            cout << stack2[top2--]->data << ' ';
        }
        cout << '\n';
    }

    // 对外返回结点总数。
    int nodeCount() const {
        return countNodes(root);
    }

    // 对外返回叶子结点数。
    int leafCount() const {
        return countLeaves(root);
    }

    // 对外返回树高。
    int treeHeight() const {
        return height(root);
    }
};

int main() {
    // 演示：递归遍历、层序遍历、非递归遍历和统计信息。
    BinaryTree tree;
    tree.buildSample();

    cout << "preorder: ";
    tree.printPreorder();

    cout << "inorder: ";
    tree.printInorder();

    cout << "postorder: ";
    tree.printPostorder();

    cout << "level order: ";
    tree.printLevelOrder();

    cout << "preorder non-recursive: ";
    tree.printPreorderNonRecursive();

    cout << "inorder non-recursive: ";
    tree.printInorderNonRecursive();

    cout << "postorder non-recursive: ";
    tree.printPostorderNonRecursive();

    cout << "node count: " << tree.nodeCount() << '\n';
    cout << "leaf count: " << tree.leafCount() << '\n';
    cout << "height: " << tree.treeHeight() << '\n';

    return 0;
}
