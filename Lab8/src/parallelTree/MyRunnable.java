package parallelTree;

import java.util.concurrent.ExecutorService;

import java.util.concurrent.atomic.AtomicInteger;

/**
 * @author cristian.chilipirea
 * 
 */

public class MyRunnable implements Runnable {
	TreeNode tree;
	ExecutorService tpe;
	AtomicInteger number_nodes, nodes_printed;

	public MyRunnable(ExecutorService tpe, TreeNode tree, AtomicInteger no, AtomicInteger print) {
		this.tree = tree;
		this.tpe = tpe;
		this.number_nodes = no;
		this.nodes_printed = print;
	}

	@Override
	public void run() {
		System.out.println(tree.getName());
		nodes_printed.addAndGet(1);
		if (tree.left != null)
			tpe.submit(new MyRunnable(tpe, tree.left, number_nodes, nodes_printed));
		if (tree.right != null)
			tpe.submit(new MyRunnable(tpe, tree.right, number_nodes, nodes_printed));

		if (nodes_printed.get() == number_nodes.get())
			tpe.shutdown();
	}

}
