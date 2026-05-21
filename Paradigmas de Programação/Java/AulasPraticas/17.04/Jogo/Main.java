import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        TreeSet<Personagem> personagens = new TreeSet<Personagem>();
        Scanner sc = new Scanner(System.in);
        String nome;
        double nivel, forca;

        for(int i = 0; i < 3; i++)
        {
            nome = sc.next();
            nivel = sc.nextDouble();
            forca = sc.nextDouble();

            if(i % 3 == 0)
                personagens.add(new Guerreiro(nome, nivel, forca));
            else if(i % 3 == 1)
                personagens.add(new Mago(nome, nivel, forca));
            else
                personagens.add(new Arqueiro(nome, nivel, forca));
        }

        sc.close();

        for(Personagem p : personagens)
            System.out.printf("Nome:  %s | Dano: %.2f\n", p.getNome(), p.calcularDano());
    }
}