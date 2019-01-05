class BinarySearch
{
    int binarySearch(int arr[], int lowerBound, int upperBound, int x)
    {
        while (lowerBound <= upperBound) {
            int middle = (lowerBound + upperBound) / 2;

            if (arr[middle] == x) {
                return middle;
            } else {
                if (x > arr[middle]) {
                    lowerBound = middle + 1;
                } else {
                    upperBound = middle - 1;
                }
            }
        }
        return -1;
    }

    public static void main(String args[])
    {
        BinarySearch ob = new BinarySearch();
        int arr[] = {2,3,4,10,40};
        int n = arr.length;
        int elemToBeFound = 10;
        int result = ob.binarySearch(arr,0,n-1,elemToBeFound);
        if (result == -1)
            System.out.println("Element not present");
        else
            System.out.println("Element found at index " + result);
    }
}
