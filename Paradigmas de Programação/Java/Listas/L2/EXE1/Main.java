import java.util.*;

public class Main
{
	public static void main(String[] args) 
	{
		Autor A1 = new Autor("Marcus", "Brasileiro");
		Livro L1 = new Livro("POO", 2026, A1);
		
		System.out.println(A1.toString());
		System.out.println(L1.toString());
	}
}