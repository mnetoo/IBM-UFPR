public class CompraAutomaticaBot implements PrecoObserver 
{
    private double saldoEmDolar = 1000.00;

    @Override
    public void atualizar(double preco) 
    {
        if (preco < 45000 && saldoEmDolar > 0) 
        {
            System.out.println("[BOT] Executando ORDEM DE COMPRA a $" + preco + ". Saldo utilizado: $" + saldoEmDolar);
            saldoEmDolar = 0; // Gastou tudo
        }
    }
}