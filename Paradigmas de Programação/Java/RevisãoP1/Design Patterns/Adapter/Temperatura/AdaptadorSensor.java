public class AdaptadorSensor implements Termometro 
{
    private double temperaturaFahrenheit;
    private SensorAmericano sensorAmericano;

    public AdaptadorSensor(double temperaturaFahrenheit) 
    {
        this.temperaturaFahrenheit = temperaturaFahrenheit;
        this.sensorAmericano = new SensorAmericano(temperaturaFahrenheit);
    }

    public double getTemperaturaCelcius() 
    {
        double temperaturaFahrenheit = this.sensorAmericano.readFahrenheit();
        return (temperaturaFahrenheit - 32) * 5.0 / 9.0;
    }
}