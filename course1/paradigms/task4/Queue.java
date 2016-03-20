import java.util.function.Function;
import java.util.function.Predicate;

// INV: FIFO (First in - first out)
//      queue[head]..queue[tail] - queue
public interface Queue extends Copiable {

    // PRE:  None
    // POST: queue[tail] = element,
    //       queue[head]..queue[tail-1] - immutable
    //       size' = size + 1
    void enqueue(Object element);

    // PRE:  !isEmpty
    // POST: queue - immutable
    //       R = queue[head]
    Object element();

    // PRE:  !isEmpty
    // POST: R = queue[head]
    //       queue[head] = queue[head+1]
    //       size' = size - 1
    //       queue[head+1]..queue[tail] - immutable
    Object dequeue();

    // PRE:  None
    // POST: queue - immutable
    //       R = size
    int size();

    // PRE:  None
    // POST: queue - immutable
    //       R = (size == 0)
    boolean isEmpty();

    // PRE:  None
    // POST: size == 0
    void clear();

    // PRE:  None
    // POST: Array[size]
    //       0 <= i < size: Array[i] = queue[head + i]
    //       R = Array
    //       queue - immutable
    Object[] toArray();

    // PRE:  None
    // POST: queue[head] = element
    //       queue[head + 1]..queue[tail] - immutable
    void push(Object element);

    // PRE:  size != 0
    // POST: R = queue[tail]
    //       queue - immutable
    Object peek();

    // PRE:  size != 0
    // POST: queue[tail] = queue[tail - 1]
    //       queue[head]..queue[tail - 1] - immutable
    //       R = queue[tail]
    Object remove();

    // PRE:  predicate != null
    // POST: queue - immutable
    //       newQueue = queue:
    //           head <= i <= tail: predicate(queue[i]) == true
    //       R = newQueue
    Queue filter(Predicate<Object> predicate);

    // PRE:  function != null
    // POST: queue - immutable
    //       newQueue = queue:
    //           head <= i <= tail: newQueue[i] = function(queue[i])
    //       R = newQueue
    Queue map(Function<Object, Object> function);
}
