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

        int matBusca = 1001;
        professores.removeIf(p -> p.getMatricula() == matBusca);
        
        for(Professor p : professores)
            System.out.println(p);

        sc.close();
    }
}
