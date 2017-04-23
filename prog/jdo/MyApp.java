import java.util.Iterator;
import java.util.List;
import javax.jdo.JDOHelper;
import javax.jdo.PersistenceManager;
import javax.jdo.PersistenceManagerFactory;
import javax.jdo.Query;
import javax.jdo.Transaction;
public class MyApp {
public static void main(String[] args)
{//TEST is the persistent unit name
PersistenceManagerFactory pmf =
JDOHelper.getPersistenceManagerFactory("TEST");
PersistenceManager pm = pmf.getPersistenceManager();
Transaction tx=pm.currentTransaction();
try
{
tx.begin();
Inventory inv = new Inventory("My Inventory");
Product product = new Product("Sony Discman", "A standard discman from Sony", 49.99);
Product product1 = new Product("Sony xperia z1", "A smart phone", 149.99);
inv.getProducts().add(product);
inv.getProducts().add(product1);
pm.makePersistent(inv);
Query q = pm.newQuery("SELECT FROM " + Product.class.getName() +" WHERE price < 150.00 ORDER BY price ASC");
// add some more JDOQL queries here
List<Product> products = (List<Product>)q.execute();
Iterator<Product> iter = products.iterator();
while (iter.hasNext())
{
Product p = iter.next();
System.out.println("Name: "+p.name+"\t Description: "+p.description+"\tPrice: "+p.price);
}
tx.commit();
} finally
{
if (tx.isActive())
{
tx.rollback();
}
pm.close();
}
}
}
