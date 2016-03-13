public abstract class AbstractQueue implements Queue {

    /* final */
    public void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    public boolean isEmpty() {
        return size() == 0;
    }


    public Queue makeCopy() {
        return new LinkedQueue();
    }
}
