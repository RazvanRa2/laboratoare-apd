package synchronizationProblem;

/**
 * @author cristian.chilipirea
 * 
 */
import java.util.concurrent.atomic.AtomicInteger;

public class MyThread implements Runnable {
	int id;
	static AtomicInteger value = new AtomicInteger(0);

	MyThread(int id) {
		this.id = id;
	}

	@Override
	public void run() {
		if (id == 0) {
			for (int i = 0; i < Main.N; i++)
				value.addAndGet(3);
		} else {
			for (int i = 0; i < Main.N; i++)
				value.addAndGet(3);
		}
	}
}
