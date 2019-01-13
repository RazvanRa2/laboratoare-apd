package parallelTree;

/**
 * @author cristian.chilipirea
 *
 */

import java.util.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.concurrent.*;

public class ReadTreePart implements Runnable {
	TreeNode tree;
	String fileName;

	Scanner sc;

	public ReadTreePart(TreeNode tree, String fileName) {
		this.tree = tree;
		this.fileName = fileName;
	}

	@Override
	public void run() {
		try {
			sc = new Scanner(new File(fileName));
		} catch (Exception e) {
			e.printStackTrace();
		}

		while (sc.hasNextInt()) {
			int n = sc.nextInt();
			int p = sc.nextInt();
			while (tree.getNode(p) == null) {

			}
			TreeNode nod = tree.getNode(p);
			try {
				nod.s.acquire();
			} catch(Exception e) {
				e.printStackTrace();
			}
			nod.addChild(new TreeNode(n));
			nod.s.release();
		}
		try {
		Main.newBarrier.await();	
	} catch (Exception e) {
		e.printStackTrace();
	}
	}
}
