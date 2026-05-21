public class Mago extends Personagem
{
    public Mago(String nome, double nivel, double forca)   { super(nome, nivel, forca); }

    public double calcularDano()
    {
        return (getNivel() * getForca() * 1.2) - 10;
    }
}