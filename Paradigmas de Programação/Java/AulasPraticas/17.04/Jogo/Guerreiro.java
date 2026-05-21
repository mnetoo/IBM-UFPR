public class Guerreiro extends Personagem
{
    public Guerreiro(String nome, double nivel, double forca)   { super(nome, nivel, forca); }

    public double calcularDano()
    {
        return getNivel() * getForca() * 1.2;
    }
}