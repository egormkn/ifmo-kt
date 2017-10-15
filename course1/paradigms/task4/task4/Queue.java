import java.util.function.Function;
import java.util.function.Predicate;

// INV: FIFO (First in - first out)
public interface Queue extends Copiable {

    // PRE:  None
    // POST: last element of queue = element,
    //       previous elements are immutable
    //       size++
    void enqueue(Object element);

    // PRE:  !isEmpty
    // POST: queue - immutable
    //       R = first element of queue
    Object element();

    // PRE:  !isEmpty
    // POST: R = first element of queue
    //       first element of queue = next element
    //       other elements are immutable
    Object dequeue();

    // PRE:  None
    // POST: queue - immutable
    //       R = size of queue
    int size();

    // PRE:  None
    // POST: queue - immutable
    //       R = (size() == 0)
    boolean isEmpty();

    // PRE:  None
    // POST: isEmpty
    void clear();

    // PRE:  None
    // POST: R = array of queue elements
    //       from first to last element
    //       queue - immutable
    Object[] toArray();

    // PRE:  None
    // POST: first element of queue = element
    //       other elements are immutable
    void push(Object element);

    // PRE:  !isEmpty
    // POST: R = last element of queue
    //       queue - immutable
    Object peek();

    // PRE:  !isEmpty
    // POST: R = last element of queue
    //       last element of queue = previous element
    //       other elements are immutable
    Object remove();

    // PRE:  predicate != null;
    // POST: queue - immutable
    //       R = new queue with elements filtered by predicate
    Queue filter(Predicate<Object> predicate);

    // PRE:  function != null;
    // POST: queue - immutable
    //       R = new queue of elements gotten by
    //       performing a function on elements of
    //       current queue
    Queue map(Function<Object, Object> function);
}
