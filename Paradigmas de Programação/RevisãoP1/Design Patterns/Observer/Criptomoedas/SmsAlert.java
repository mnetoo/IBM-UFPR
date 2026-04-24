public class SmsAlert implements PrecoObserver 
{
    @Override
    public void atualizar(double preco) 
    {
        if (preco < 50000)
            System.out.println("[SMS] ALERTA: O preço caiu drasticamente para $" + preco + "! Hora de comprar?");
    }
}