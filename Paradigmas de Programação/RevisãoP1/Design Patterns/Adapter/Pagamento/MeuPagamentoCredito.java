public class MeuPagamentoCredito implements ProcessarPagamento
{
    private SdkPagamentoCredito sdk;

    public MeuPagamentoCredito()    { sdk = new SdkPagamentoCredito(); }

    public void debitar(int valor)  
    { 
        sdk.autorizar(valor);
        sdk.capturar(valor);
    }

    public void creditar(int valor)     { sdk.creditar(valor); }
}