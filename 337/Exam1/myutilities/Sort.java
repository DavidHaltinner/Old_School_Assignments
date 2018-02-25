/*
 * Sort.java
 *
 * Created on March 2, 2004, 12:10 PM
 *
 * @author  David Haltinner
 */

package myutilities;


public class Sort {
    
    /** Creates a new instance of Sort */
    public Sort() {
    }
    public static void shellSort(Sortable [] a, int n) throws MyException{
        for (int incr = n / 2; incr > 0; incr /= 2) {
            for(int i = incr; i < n; i++) {
                int j = i - incr;
                while(j >= 0) {
                    if (a[j].compare(a[j+incr])>0) {
                        Sortable T = a[j];
                        a[j] = a[j+incr];
                        a[j+incr] = T;
                        j -= incr;
                    }
                    else {
                        j = -1;
                    }
                }
            }
        }
    }
}
