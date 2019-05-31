package general_data_structure.list;

import static java.lang.reflect.Array.newInstance;
import java.util.Arrays;

public class ArrayList<T> {
    private T[] values;
    private int size;

    public ArrayList(Class type, int size) {
        if (size < 0)
            throw new IllegalArgumentException();
        this.values = (T[]) newInstance(type, size);
        this.size = 0;
    }

    private void ensureCapacity() {
        if (this.size == values.length) {
            values = Arrays.copyOf(values, values.length * 2);
        }
    }

    public int size() {
        return this.size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public boolean contains(T o) {
        for (int i = 0; i < this.size; i++) {
            if (o.equals(values[i])) {
                return true;
            }
        }
        return false;
    }

    public boolean add(T e) {
        ensureCapacity();
        values[this.size++] = e;
        return true;
    }

    public boolean remove(T o) {
        boolean hasDeleted = false;
        for (int i = 0; i < size; i++) {
            if (o.equals(values[i])) {
                for (int j = i; j < size - 1; j++) {
                    values[j] = values[j + 1];
                }
                size -= 1;
                hasDeleted = true;
                break;
            }
        }
        return hasDeleted;
    }

    public void clear() {
        size = 0;
    }

    public Object get(int index) {
        if (index < 0 || index > size - 1) {
            throw new IllegalArgumentException(String.format("size=%d, index=%d", size, index));
        }
        return values[index];
    }

    public T set(int index, T element) {
        if (index < 0 || index > size - 1) {
            throw new IllegalArgumentException(String.format("size=%d, index=%d", size, index));
        }
        T rev = values[index];
        values[index] = element;
        return rev;
    }

    public void add(int index, T element) {
        if (index < 0 || index > size) {
            throw new IllegalArgumentException(String.format("size=%d, index=%d", size, index));
        }
        ensureCapacity();
        for (int i = size; i > index; i--) {
            values[i] = values[i - 1];
        }
        values[index] = element;
        size += 1;
    }

    public T remove(int index) {
        if (index < 0 || index > size - 1) {
            throw new IllegalArgumentException(String.format("size=%d, index=%d", size, index));
        }
        T rev = values[index];
        for (int i = index; i < size - 1; i++) {
            values[i] = values[i + 1];
        }
        size -= 1;
        return rev;
    }

    public int indexOf(T o) {
        int res = -1;
        for (int i = 0; i < size; i++) {
            if (o.equals(values[i])) {
                res = i;
                break;
            }
        }
        return res;
    }

    public int lastIndexOf(T o) {
        int rev = -1;
        for (int i = size - 1; i >= 0; i--) {
            if (o.equals(values[i])) {
                rev = i;
                break;
            }
        }
        return rev;
    }
}