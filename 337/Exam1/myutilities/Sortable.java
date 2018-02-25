/*
 * Sortable.java
 *
 * Created on March 2, 2004, 11:45 AM
 *
 * @author  David Haltinner
 */

package myutilities;

public interface Sortable {
    public int compare (Sortable b) throws MyException;
}

