public interface Stack extends Copiable {
    /*public*/ void push(Object element);
    /*public*/ Object pop();
    /*public*/ Object peek();
    /*public*/ int size();
    /*public*/ boolean isEmpty();
    Stack makeCopy();
}
