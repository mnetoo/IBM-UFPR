import java.util.Scanner;

public class Main
{
    public static void main(String[] args) 
    {
        Scanner sc = new Scanner(System.in);

        Data[] datas = new Data[3];

        for(int i = 0; i < 3; i++)
        {
            System.out.println("Digite a " + (i + 1) + "º data:");

            int dia = sc.nextInt();
            int mes = sc.nextInt();
            int ano = sc.nextInt();

            Data d = new Data(dia, mes, ano);

            if(!d.checaDiaMes(dia, mes))
            {
                System.out.println("Data inválida!");
                i--;
                continue;
            }

            datas[i] = d;
        }


        for(int i = 0; i < 3; i++)
            System.out.println("Data: " + datas[i]);
            
            
        Data ref = datas[0];
        System.out.println("\nMaior data: " + ref.maiorData(datas));
        System.out.println("Menor data: " + ref.menorData(datas));

        sc.close();
    }
}