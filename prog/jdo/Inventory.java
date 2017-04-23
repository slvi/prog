import java.util.HashSet;
import java.util.Set;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.PrimaryKey;
@PersistenceCapable
public class Inventory
{ @PrimaryKey
String name = null;
@SuppressWarnings({ "rawtypes", "unchecked" })
Set<Product> products = new HashSet();
public Inventory(String name)
{
this.name = name;
}
public Set<Product> getProducts() {return products;}
}