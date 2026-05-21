public class Main 
{
    public static void main(String[] args) 
    {
        double temperaturaFahrenheit = 100.0;

        Termometro termometro = new AdaptadorSensor(temperaturaFahrenheit);

        double temperaturaCelcius = termometro.getTemperaturaCelcius();
        
        System.out.println("Temperatura em Celsius: " + temperaturaCelcius);
    }
}