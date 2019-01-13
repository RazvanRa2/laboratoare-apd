package parallelTree;

/**
 * @author cristian.chilipirea
 *
 */
import java.util.concurrent.*;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;


public class Main {
	static int N_ITERATIONS = 1;
	public static CyclicBarrier newBarrier = new CyclicBarrier(2);

	static AtomicInteger number_nodes = new AtomicInteger(0);
	static AtomicInteger nodes_printed = new AtomicInteger(0);

	public static void main(String[] args) {


		Thread threads[] = new Thread[3];
		System.out.println("Parallel tree problem");
			TreeNode tree = new TreeNode(1);
		
		for (int j = 0; j < N_ITERATIONS; j++) {
			threads[0] = new Thread(new ReadTreePart(tree, "../treePart1.txt", number_nodes));
			threads[1] = new Thread(new ReadTreePart(tree, "../treePart2.txt", number_nodes));
			//threads[2] = new Thread(new VerifyTree(tree));
			for (int i = 0; i < 2; i++)
				threads[i].start();
			for (int i = 0; i < 2; i++) {
				try {
					threads[i].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}



		ExecutorService tpe = Executors.newFixedThreadPool(1);


		tpe.submit(new MyRunnable(tpe, tree, number_nodes, nodes_printed));
	}
}