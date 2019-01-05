package doubleVectorElements;
/**
 * @author cristian.chilipirea
 *
 */

import java.util.*;

class MultiplyThread extends Thread{

	int start;
	int end;
	int v[];

	public MultiplyThread(int N, int P, int thread_id, int vector[]) {
		start  = (int) Math.ceil((float) N / P * thread_id);
		end = (int) Math.min(Math.ceil((float)N/P * (thread_id + 1)), N);
		v = vector;
		System.out.println(thread_id + " " + start + " " + end);
	}

	public void run() {
		for (int i = start; i < end; i++) {
			v[i] = 2 * v[i];
		}
	}
}
public class Main {

	public static void main(String[] args) {
		int N = 100000013;
		int v[] = new int[N];

		for(int i=0;i<N;i++)
			v[i]=i;

		// Parallelize me
		int p = 10;
		List<MultiplyThread> list = new LinkedList<MultiplyThread>();

		for (int i = 0; i < p; i++) {
			list.add(new MultiplyThread(N, p, i, v));
		}

		for (int i = 0; i < p; i++) {
				list.get(i).start();
		}


		for (int i = 0; i < p; i++) {
			try {
				list.get(i).join();
			} catch (Exception ex) {

			}
		}

		for (int i = 0; i < N; i++) {
			if(v[i]!= i*2) {
				System.out.println("Wrong answer");
				System.exit(1);
			}
		}
		System.out.println("Correct");
	}

}
