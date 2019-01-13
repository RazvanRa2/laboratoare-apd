package parallelTree;

/**
 * @author cristian.chilipirea
 *
 */
import java.util.concurrent.*;

public class TreeNode {
	int name;
	Semaphore s;
	public TreeNode left = null;
	public TreeNode right = null;

	TreeNode(int name) {
		this.name = name;
		s = new Semaphore(1);
	}

	void addChild(TreeNode child) {
		if (left == null) {
			left = child;
			return;
		}
		right = child;
	}

	TreeNode getNode(int name) {
		TreeNode aux = null;
		if (this.name == name)
			return this;
		if (left != null)
			aux = left.getNode(name);
		if (aux != null)
			return aux;
		if (right != null)
			aux = right.getNode(name);
		if (aux != null)
			return aux;
		return null;
	}

	int getName() {
		return name;
	}
}
