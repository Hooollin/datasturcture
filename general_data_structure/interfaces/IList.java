package general_data_structure.interfaces;

public interface IList<T> {
    int size();

    boolean isEmpty();

    boolean contains(T o);

    boolean add(T e);

    void clear();

    T get(int index);

    T set(int index, T elem);

    T remove(int index);

    int indexOf(T o);
}