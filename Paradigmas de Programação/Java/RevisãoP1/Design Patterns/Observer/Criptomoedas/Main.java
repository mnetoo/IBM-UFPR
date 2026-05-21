public class Main 
{
    public static void main(String[] args) 
    {
        // 1. Criamos o nosso "Assunto" (Subject)
        TickerCripto btcTicker = new TickerCripto("Bitcoin");

        // 2. Criamos os observadores
        LoggerPreco logger = new LoggerPreco();
        SmsAlert sms = new SmsAlert();
        CompraAutomaticaBot bot = new CompraAutomaticaBot();

        // 3. Registro (Inscrição na Newsletter)
        btcTicker.registrarObserver(logger);
        btcTicker.registrarObserver(sms);
        btcTicker.registrarObserver(bot);

        // 4. Simulando mudanças de preço no mercado
        btcTicker.setPreco(60000.00); // Apenas o Log deve aparecer
        btcTicker.setPreco(49000.00); // Log e SMS devem reagir
        btcTicker.setPreco(44000.00); // Todos devem reagir, inclusive o Bot comprando
    }
}