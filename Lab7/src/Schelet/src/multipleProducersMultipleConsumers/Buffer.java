package multipleProducersMultipleConsumers;
/**
 * @author cristian.chilipirea
 *
 */

import java.util.concurrent.*;

public class Buffer {
	//int a;
	ArrayBlockingQueue<Integer> a = new ArrayBlockingQueue(5);

	void put(int value) {
		try {
		a.put(value);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	int get() {
		try {
			return a.take();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return 0;

	}
}
