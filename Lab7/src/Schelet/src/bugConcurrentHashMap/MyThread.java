package bugConcurrentHashMap;

import java.util.concurrent.ConcurrentHashMap;

/**
 * @author cristian.chilipirea
 * 
 */

public class MyThread implements Runnable {
	public static ConcurrentHashMap<Integer, Integer> hashMap = new ConcurrentHashMap<Integer, Integer>();
	int id;

	MyThread(int id) {
		this.id = id;
	}

	void addValue(int key, int value) {
		//if(hashMap.containsKey(key))
		Integer ceva = hashMap.putIfAbsent(key, value);
		if (ceva != null)
			hashMap.replace(key, ceva + value);
		//else
		//	hashMap.putIfAbsent(key, value);
	}
	
	@Override
	public void run() {
		if (id == 0) {
			for (int i = 0; i < Main.N; i++) {
				addValue(i, 2*i);
			}
		} else {
			for (int i = 0; i < Main.N; i++) {
				addValue(i, 3*i);
			}
		}
	}
}
