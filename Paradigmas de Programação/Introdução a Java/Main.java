import java.util.Scanner;

public class Main {

    public static void main(String[] args) 
    {
        Pessoa p = new Pessoa();

        Scanner sc = new Scanner(System.in);
        System.out.print("Digite seu nome: ");
        String n = sc.nextLine();
        System.out.print("Digite sua idade: ");
        int x = sc.nextInt();

        p.nome = n;
        p.idade = x;
        p.Saudacao();

        sc.close();
    }
}