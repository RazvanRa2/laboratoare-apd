package multipleProducersMultipleConsumers;
/**
 * @author cristian.chilipirea
 *
 */
 public class Buffer {
 	int[] a;
 	int indx;
 	Buffer() {
 		a = new int[5];
 		indx = 0;
 	}

 	void put(int value) {
 		synchronized(this) {
 			while (this.isFull()) {
 				try {this.wait();}catch(Exception ex) {}
 			}
 			a[indx] = value;
 			indx++;
 			this.notifyAll();
 		}
 	}

 	int get() {
 		synchronized(this) {
 			while (this.isEmpty()) {
 				try {this.wait();}catch(Exception ex) {}
 			}
			indx--;
			int var = a[indx];
 			this.notifyAll();
			return var;
 		}
 	}

 	boolean isEmpty() {
 		return indx == 0;
 	}

 	boolean isFull() {
 		return indx == 5;
 	}
 }
