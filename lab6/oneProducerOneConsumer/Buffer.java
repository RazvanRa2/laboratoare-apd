package oneProducerOneConsumer;
/**
 * @author cristian.chilipirea
 *
 */
 import java.util.LinkedList;

public class Buffer {
	LinkedList<Integer> a;
	int indx;
	Buffer() {
		a = new LinkedList<Integer>();
		indx = 0;
	}

	void put(int value) {
		synchronized(this) {
			while (this.isFull()) {
				try {this.wait();}catch(Exception ex) {}
			}
			a.add(value);
			this.notifyAll();
		}
	}

	int get() {
		synchronized(this) {
			while (this.isEmpty()) {
				try {this.wait();}catch(Exception ex) {}
			}
			this.notifyAll();
			return a.poll();
		}
	}

	boolean isEmpty() {
		return a.isEmpty();
	}

	boolean isFull() {
		return a.size() == 5;
	}
}
