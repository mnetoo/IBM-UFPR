import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        ArrayList<AlunoMonitor> alunos = new ArrayList<AlunoMonitor>();
        Scanner sc = new Scanner(System.in);
        String nome, codigo;
        int matricula;

        for(int i = 0; i < 3; i++)
        {
            nome = sc.next();
            matricula = sc.nextInt();
            codigo = sc.next();

            alunos.add(new AlunoMonitor(nome, matricula, codigo));
        }

        for(AlunoMonitor a : alunos)
            System.out.println(a);

        sc.close();
    }
}