public interface ProcessarPagamento
{
    void debitar(int valor);
    void creditar(int valor);
}