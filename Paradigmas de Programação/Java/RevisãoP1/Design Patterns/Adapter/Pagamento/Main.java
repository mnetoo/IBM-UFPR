public class Main
{
    public static void main(String[] args)
    {
        ProcessarPagamento credito = new MeuPagamentoCredito();
        credito.creditar(240);
        credito.debitar(240);
    }
}