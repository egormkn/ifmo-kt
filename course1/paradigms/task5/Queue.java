public interface Queue extends Copiable {

    // PRE: None
    // POST: elements[tail-1] = element     (last element of queue = element)
    //       tail = (tail + 1) % elements.length;
    void enqueue(Object element);

    // PRE: !isEmpty
    // POST: queue - immutable
    //       R = elements[head]  (first element of queue)
    Object element();

    // PRE:  !isEmpty
    // POST: R = elements[head]     (first element of queue)
    //       head = (head + 1) % elements.length;
    Object dequeue();

    // PRE: None
    // POST: queue - immutable
    //       R = size
    int size();

    // PRE: None
    // POST: queue - immutable
    //       R = (head == tail)
    boolean isEmpty();

    // PRE: None
    // POST: isEmpty
    void clear();

    // PRE: None
    // POST: R = queue
    // Object[] toArray();

    // PRE:  None
    // POST: elements[head] = element (first element of queue = element)
    // void push(Object element);

    // PRE:  !isEmpty
    // POST: R = elements[tail - 1] (last element of queue)
    // Object peek();

    // PRE:  !isEmpty
    // POST: R = elements[tail] (last element of queue)
    // Object remove();
}
