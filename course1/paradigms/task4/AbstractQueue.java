import java.util.function.Function;
import java.util.function.Predicate;

public abstract class AbstractQueue implements Queue {
    public final void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    public final boolean isEmpty() {
        return size() == 0;
    }

    public final Object[] toArray() {
        Object[] array = new Object[size()];
        for (int i = 0; i < size(); i++) {
            array[i] = dequeue();
            enqueue(array[i]);
        }
        return array;
    }

    protected abstract Queue sameTypeQueue();

    public Queue filter(Predicate<Object> predicate) {
        Object[] array = toArray();
        Queue queue = sameTypeQueue();
        for (int i = 0; i < size(); i++) {
            if (predicate.test(array[i])) {
                queue.enqueue(array[i]);
            }
        }
        return queue;
    }

    public Queue map(Function<Object, Object> function) {
        Object[] array = toArray();
        Queue queue = sameTypeQueue();
        for (int i = 0; i < size(); i++) {
            queue.enqueue(function.apply(array[i]));
        }
        return queue;
    }

    // PRE:
    // POST: newQueue[i] = queue[i]
    //       R = newQueue
    public Queue makeCopy() {
        return map(x -> x);
    }
}
