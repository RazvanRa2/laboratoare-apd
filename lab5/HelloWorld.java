public class HelloWorld extends Thread{
    private int threadNo;
    HelloWorld(int no) {
        this.threadNo = no;
    }
    public void run() {
        System.out.println("Hello World from thread " + threadNo);
    }
    public static void main(String[] args) {

        int threadsNo = 4;
        for (int i = 0; i < threadsNo; i++) {
            (new HelloWorld(i)).start();
        }
    }
}
