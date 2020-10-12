import java.util.Scanner;
import java.math.BigInteger;

public class JAVA{
  public static void main(String[] args){
    Scanner cin = new Scanner(System.in);
    String a, b, c;
    while(cin.hasNext()){
      a = cin.next();
      b = cin.next();
      c = cin.next();
      BigInteger ia = new BigInteger(a);
      BigInteger ic = new BigInteger(c);
      if(b.charAt(0) == '+')
        System.out.printf("%s\n", ia.add(ic));
      if(b.charAt(0) == '-')
        System.out.printf("%s\n", ia.subtract(ic));
      if(b.charAt(0) == '*')
        System.out.printf("%s\n", ia.multiply(ic));
      if(b.charAt(0) == '/')
        System.out.printf("%s\n", ia.divide(ic));
    }
  }
}
