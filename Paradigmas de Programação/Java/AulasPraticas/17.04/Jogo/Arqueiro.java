public class Arqueiro extends Personagem
{
    public Arqueiro(String nome, double nivel, double forca)   { super(nome, nivel, forca); }

    public double calcularDano()
    {
        return (getNivel() * getForca()) + 15;
    }
}