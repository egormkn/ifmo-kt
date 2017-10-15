import java.util.function.Function;
import java.util.function.Predicate;

public abstract class AbstractQueue implements Queue {
    private int size = 0;

    protected abstract void doEnqueue(Object element);

    protected abstract Object doDequeue();

    protected abstract void doPush(Object element);

    protected abstract Object doRemove();

    protected abstract Queue sameTypeQueue();

    public void enqueue(Object element) {
        doEnqueue(element);
        size++;
    }

    public Object element() {
        assert size > 0;
        Object r = dequeue();
        push(r);
        return r;
    }

    public Object dequeue() {
        assert size > 0;
        Object r = doDequeue();
        size--;
        return r;
    }

    public int size() {
        return size;
    }

    public void clear() {
        while (size > 0) {
            dequeue();
        }
    }

    public final boolean isEmpty() {
        return size == 0;
    }

    public void push(Object element) {
        doPush(element);
        size++;
    }

    public Object peek() {
        assert size > 0;
        Object r = remove();
        enqueue(r);
        return r;
    }

    public Object remove() {
        assert size > 0;
        Object r = doRemove();
        size--;
        return r;
    }

    public Object[] toArray() {
        Object[] array = new Object[size];
        for (int i = 0; i < size; i++) {
            array[i] = dequeue();
            enqueue(array[i]);
        }
        return array;
    }

    public Queue filter(Predicate<Object> predicate) {
        Object[] array = toArray();
        Queue queue = sameTypeQueue();
        for (int i = 0; i < size; i++) {
            if (predicate.test(array[i])) {
                queue.enqueue(array[i]);
            }
        }
        return queue;
    }

    public Queue map(Function<Object, Object> function) {
        Object[] array = toArray();
        Queue queue = sameTypeQueue();
        for (int i = 0; i < size; i++) {
            queue.enqueue(function.apply(array[i]));
        }
        return queue;
    }
}
