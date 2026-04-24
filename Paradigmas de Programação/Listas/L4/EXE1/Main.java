import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);;
        String nome = sc.nextLine();

        CartaoWeb[] cartoes = new CartaoWeb[3];
        cartoes[0] = new CartaoDiaDosNamorados("Anna");
        cartoes[1] = new CartaoNatal("Claudia");
        cartoes[2] = new CartaoAniversario("Frankly");

        for(CartaoWeb c : cartoes)
            System.out.println(c.retornarMensagem(nome));
    }
}