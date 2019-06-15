package general_data_structure.tree;

import java.util.LinkedList;
import java.util.NoSuchElementException;

import com.sun.corba.se.impl.orbutil.graph.Node;

public class BinarySearchTree<T extends Comparable<T>> {
    private static class Node<T> {
        private T value;
        private Node<T> left;
        private Node<T> right;

        public Node(T value) {
            this.value = value;
        }
    }

    private Node<T> root;
    private int size;

    public boolean isEmpty() {
        return size == 0;
    }

    public boolean size() {
        return size;
    }

    public void add(T e) {
        root = add(root, e);
    }

    private Node<T> add(Node<T> node, T e) {
        if (node == null) {
            size += 1;
            return new Node<>(e);
        }
        if (e.compareTo(node.value) < 0) {
            root.left = add(node.left, e);
        } else if (e.compareTo(node.value) > 0) {
            node.right = add(node.right, e);
        }
        return node;
    }

    public boolean contains(T e) {
        return contains(root, e);
    }

    private boolean contains(Node<T> node, T e) {
        if (node == null) {
            return false;
        }
        if (e.compareTo(node.value) > 0) {
            return contains(node.right, e);
        } else if (e.compareTo(node.value) < 0) {
            return contains(node.left, e);
        }
        return true;
    }

    public void preorder() {
        preorder(root);
    }

    private void preorder(Node<T> node) {
        if (node == null) {
            return;
        }
        System.out.println(node.value);
        preorder(node.left);
        preorder(node.right);
    }

    public void inorder() {
        inorder(root);
    }

    private void inorder(Node<T> root) {
        if (root == null) {
            return;
        }
        inorder(root.left);
        System.out.println(root.value);
        inorder(root.right);
    }

    public void postorder() {
        postorder(root);
    }

    private void postorder(Node<T> node) {
        if (node == null) {
            return;
        }
        postorder(node.left);
        postorder(node.right);
        System.out.println(node.value);
    }

    public void levelorder() {
        if (root == null) {
            return;
        }
        LinkedList<Node<T>> q = new LinkedList<>();
        Node<T> curr = root;
        q.offer(curr);
        while (!q.isEmpty()) {
            int size = q.size();
            while (size-- > 0) {
                Node<T> top = q.poll();
                System.out.println(top.value);
                if (top.left != null) {
                    q.offer(top.left);
                }
                if (top.right != null) {
                    q.offer(top.right);
                }
            }
        }
    }

    public T getMax() {
        if (root == null) {
            throw new NoSuchElementException();
        }
        return getMax(root).value;
    }

    private Node<T> getMax(Node<T> root) {
        if (root.right == null) {
            return root;
        }
        return getMax(root.right);
    }

    public T getMin() {
        if (root == null) {
            throw new NoSuchElementException();
        }
        return getMin(root).value;
    }

    private Node<T> getMin(Node<T> node) {
        if (node.left == null) {
            return node;
        }
        return getMin(node.left);
    }

    public T removeMin() {
        T delete = getMin();
        root = removeMin(root);
        return delete;
    }

    public Node<T> removeMin(Node<T> node) {
        if (node.left == null) {
            Node<T> rightNode = node.right;
            node.right = null;
            size--;
            return rightNode;
        }
        node.left = removeMin(node.left);
        return node;
    }

    public T removeMax() {
        T delete = getMax();
        root = removeMax(root);
        return delete;
    }

    public Node<T> removeMax(Node<T> node) {
        if (node.right == null) {
            Node<T> leftNode = node.left;
            node.left = null;
            size--;
            return leftNode;
        }
        node.left = removeMax(node.left);
        return node;
    }

    public void remove(T e) {
        root = remove(root, e);
    }

    private Node<T> remove(Node<T> node, T e) {
        if (e.compareTo(node.value) > 0) {
            node.left = remove(node.right, e);
            return node;
        }
        if (e.compareTo(node.value) < 0) {
            node.right = remove(node.left, e);
            return node;
        }

        if (node.left == null) {
            Node<T> rightNode = node.right;
            node.right = null;
            size--;
            return rightNode;
        }

        if (node.right == null) {
            Node<T> leftNode = node.left;
            node.left = null;
            size--;
            return leftNode;
        }

        Node<T> successor = getMin(node.right);
        successor.right = removeMin(node.right);
        successor.left = node.left;
        node.left = node.right = null;
        return successor;
    }
}
