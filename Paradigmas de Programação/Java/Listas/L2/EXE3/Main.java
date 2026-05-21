import java.util.*;

public class Main
{
	public static void main(String[] args) 
	{
        Aluno A1 = new Aluno("Marcus", 0123);
        Aluno A2 = new Aluno("Adriano", 4567);
        Aluno A3 = new Aluno("Neto", 8910);
	
	    Turma IBM = new Turma(1215, "Prof. Dr.a Rachel Reis");
	    IBM.adicionar(A1);
	    IBM.adicionar(A2);
	    IBM.adicionar(A3);
	    
	    IBM.listarAlunos();
	}
}