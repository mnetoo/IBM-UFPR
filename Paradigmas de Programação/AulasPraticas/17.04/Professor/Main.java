import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        LinkedList<Professor> professores = new LinkedList<Professor>();
        Scanner sc = new Scanner(System.in);
        String nome;
        int matricula;

        for(int i = 0; i < 5; i++)
        {
            nome = sc.next();
            matricula = sc.nextInt();
            professores.add(new Professor(nome, matricula));
        }

        for(Professor p : professores)
            System.out.println(p);

        System.out.println("Buscando professor indíce 1...");
        System.out.println(professores.get(1));

        System.out.println("Removendo professor indíce 1...");
        professores.remove(1);

        for(Professor p : professores)
            System.out.println(p);

        sc.close();
    }
}