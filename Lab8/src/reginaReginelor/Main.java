package reginaReginelor;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.*;

/**
 * @author cristian.chilipirea
 * 
 */
class MyRunnable implements Runnable {
	ExecutorService tpe;
	ArrayList<Integer> positions;
	boolean[] used;
	int step;

	public MyRunnable(ExecutorService tpe, ArrayList<Integer> positions, boolean[] used, int step) {
		this.tpe = tpe;
		this.positions = positions;
		this.used = used;
		this.step = step;
	}

	@Override
	public void run() {
		if (step == Main.N) {
			System.out.println(positions);
			tpe.shutdown();
		}

		for (int i = 0; i < Main.N; i ++) {
			if (positions.contains(i))
				continue;
			if (!verify(i))
				continue;
			boolean[] newUsed = (boolean[]) used;
			newUsed[step] = true;

			ArrayList<Integer> newPositions = (ArrayList<Integer>) positions.clone();
			newPositions.add(i);

			tpe.submit(new MyRunnable(tpe, newPositions, newUsed, step + 1));
		}
	}

	boolean verify(int pos) {
		for (int i = 0; i < step; i ++) {
			if (Math.abs(i - step) == Math.abs(pos - positions.get(i)))
				return false;
		}
		return true;
	}
}



public class Main {
	static int N = 4;
	public static void main(String[] args) {
		ArrayList<Integer> positions = new ArrayList<Integer>();
		boolean[] used = new boolean[N];
		// Get Path from 0 to 3. The path does not have to be shortest, but it
		// must not contain cycles.
		//getPath(partialPath, 3);


		ExecutorService tpe = Executors.newFixedThreadPool(4);

		tpe.submit(new MyRunnable(tpe, positions, used, 0));

	}
}
