
package oneProducerOneConsumer;
/**
 * @author cristian.chilipirea
 *
 */

import java.util.*;
import java.util.concurrent.*;

public class Buffer{
	Queue<Integer> a = new LinkedList();
	volatile int current = 0;
	static Semaphore semPut = new Semaphore(5); 
	static Semaphore semGet = new Semaphore(0);

	static Semaphore semWork = new Semaphore(1);

	/*static {
		for (int i = 0; i < 5; i ++)
			try {
				semPut.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}

	}*/


	void put(int value) {
		

		try {
				semPut.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		try {
				semWork.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		a.add(value);
		current ++;
		semWork.release();

		semGet.release();


	}

	int get() {
		

		int ret = 0;
		try {
				semGet.acquire();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		//System.out.println("CUrrent is " + current + " with left permits " + semPut.availablePermits());
		try {
				semWork.acquire();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		ret =  a.remove();
		current --;
 		semWork.release();

 		semPut.release();


		return ret;

	}
}
