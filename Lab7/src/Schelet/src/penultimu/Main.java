/**
 * @author cristian.chilipirea
 *
 */

import java.util.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.concurrent.*;


public class Main {

	public static void main(String[] args) {
		LinkedList<Integer> l = new LinkedList();
		Semaphore semPut = new Semaphore(1);
		Semaphore semSort = new Semaphore(-2);

		Thread threads[] = new Thread[4];
		threads[0] = new Thread(new MyThreadRead(l, "../../elemente1.txt", semPut, semSort));
		threads[1] = new Thread(new MyThreadRead(l, "../../elemente2.txt", semPut, semSort));
		threads[2] = new Thread(new MyThreadRead(l, "../../elemente3.txt", semPut, semSort));
		threads[3] = new Thread(new MyThreadSort(l, semSort));


		for (int i = 0; i < 4; i++)
		threads[i].start();
		for (int i = 0; i < 4; i++) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		for (int i = 0; i < l.size(); i ++) {
			System.out.println(l.get(i) );
		}
		System.out.println("Correct");
	}



}

class MyThreadRead implements Runnable {
	LinkedList<Integer> l;
	String f_name;
	Scanner sc;

	Semaphore sem_put, sem_sort;
	MyThreadRead(LinkedList l, String f_name, Semaphore put, Semaphore sort) {
		this.l = l;
		this.f_name = f_name;
		try {
			sc = new Scanner(new File(f_name));
		} catch (Exception e) {
			e.printStackTrace();
		}

		this.sem_put = put;
		this.sem_sort = sort;
	}
	@Override
	public void run() {
		while (sc.hasNextInt()) {
            int i = sc.nextInt();
            //System.out.println(i);

            try {
            	sem_put.acquire();
            } catch (Exception e) {
            	e.printStackTrace();
            }

            l.add(i);
            
            sem_put.release();
        }
        sc.close();

		sem_sort.release();
	}
}


class MyThreadSort implements Runnable {
	LinkedList<Integer> l;

	Semaphore sem_sort;
	MyThreadSort(LinkedList l, Semaphore sort) {
		this.l = l;
		this.sem_sort = sort;
	}
	@Override
	public void run() {
		try {
			sem_sort.acquire();
		} catch (Exception e) {
			e.printStackTrace();
		}

		Collections.sort(l);

		sem_sort.release();
	}

	//sort

}
