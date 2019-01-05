package shortestPathsFloyd_Warshall;
/**
 * @author cristian.chilipirea
 *
 */

 import java.util.*;
public class Main {
	public static int M = 9;
	public static int graph[][] = { { 0, 1, M, M, M },
					  { 1, 0, 1, M, M },
					  { M, 1, 0, 1, 1 },
					  { M, M, 1, 0, M },
					  { M, M, 1, M, 0 } };

	static class MyThread extends Thread {
		private int tid;
		int start;
		int end;

		public MyThread(int i, int N, int P) {
			tid = i;
			start  = (int) Math.ceil((float) N / P * tid);
			end = (int) Math.min(Math.ceil((float)N/P * (tid + 1)), N);
		}

		public void run() {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					graph[i][j] = Math.min(graph[i][tid] + graph[tid][j], graph[i][j]);
				}
			}
		}
	}


	public static void main(String[] args) {


		// Parallelize me (You might want to keep the original code in order to compare)
		List<MyThread> list = new LinkedList<MyThread>();

		for (int i = 0; i < 5; i++) {
			list.add(new MyThread(i, 5, 5));
		}

		for (int i = 0; i < 5; i++) {
			list.get(i).start();
		}

		for (int i = 0; i < 5; i++) {
			try {
				list.get(i).join();
			} catch(Exception ex) {


			}
		}

		for (int k = 0; k < 5; k++) {
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(graph[i][j] + " ");
			}
			System.out.println();
		}
	}
}
