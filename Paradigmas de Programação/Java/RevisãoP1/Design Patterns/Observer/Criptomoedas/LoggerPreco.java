public class LoggerPreco implements PrecoObserver 
{
    @Override
    public void atualizar(double preco) 
    {
        System.out.println("[LOG] Variação de mercado detectada. Preço atual: $" + preco);
    }
}