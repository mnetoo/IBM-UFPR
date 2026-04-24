public class SdkPagamentoCredito
{
    public void autorizar(int valor)
    {
        System.out.printf("Pagamento Autorizado. R$ %d%n", valor);
    }

    public void capturar(int valor)
    {
        System.out.printf("Pagamento Capturado. R$ %d%n", valor);
    }

    public void creditar(int valor)
    {
        System.out.printf("Pagamento Creditado. R$ %d%n", valor);
    }
}