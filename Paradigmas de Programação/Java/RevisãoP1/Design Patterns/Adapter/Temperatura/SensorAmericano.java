public class SensorAmericano 
{
    private double temperaturaFahrenheit;

    public SensorAmericano(double temperaturaFahrenheit) 
    {
        this.temperaturaFahrenheit = temperaturaFahrenheit;
    }

    public double readFahrenheit() 
    {
        return this.temperaturaFahrenheit;
    }
}