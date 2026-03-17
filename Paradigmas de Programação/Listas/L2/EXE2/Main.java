import java.util.*;

public class Main
{
	public static void main(String[] args) 
	{
		Autor A1 = new Autor("Marcus", "BRA");
		Autor A2 = new Autor("Neto", "EUA");
		
		Livro L1 = new Livro("POO", 2026, A1);
		Livro L2 = new Livro("Paradigmas", 2026, A2);
		
		System.out.println(A1.toString());
		System.out.println(A2.toString());
	    
	    L1.exibir();
	    L2.exibir();
	}
}