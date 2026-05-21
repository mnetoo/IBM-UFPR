import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        Imovel[] imoveis = new Imovel[200];
        String rua = sc.nextLine();
        double preco = sc.nextDouble();

        Endereco endereco = new Endereco(rua, 10, "Capão Raso", "Curitiba", "PR");

        for(int i = 0; i < imoveis.length; i++)
        {
            if(i % 2 == 0)
                imoveis[i] = new ImovelNovo(endereco, preco);
            else
                imoveis[i] = new ImovelVelho(endereco, preco);
        }

        for(int i = 0; i < imoveis.length; i++)
        {
            double valor = imoveis[i].calcularValorImovel();
            String status = (imoveis[i] instanceof ImovelNovo ? "NOVO" : "VELHO");
            System.out.printf("Index: %d - Status: %s - Endereço: %s - Valor: R$%.2f\n", i, status, imoveis[i].getEndereco().toString(), valor);
        }

        sc.close();
    }
}