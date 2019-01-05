class ParalelSearch implements Runnable
{
    int[] array = {1, 2, 3, 5, 5, 5, 7, 8, 9, 10,
                    11, 12, 13, 14, 15, 16, 17};

    int x = 5;
    int start;
    int end;
    int id;
    ParalelSearch(int id) {
        this.id = id;
    }

    public void run() {
        int start = (int) Math.ceil(17 / N) * id;
        int end = Math.min((int) Math.ceil(17 / N) * (id + 1), 17);

        if (x == array[start]) {

        }

        if (x == array[end]) {

        }

        if (array[start] <= x && x <= array[end]) {
            
        }
    }
    public static final int N = 6;
    public static void main(String args[])
    {
        Thread threads[] = new Thread[N];

        for (int i = 0; i < N; i++) {
            threads[i] = new Thread(new ParalelSearch(i));
        }
        for (int i = 0; i < N; i++)
            threads[i].start();

        for (int i = 0; i < N; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
