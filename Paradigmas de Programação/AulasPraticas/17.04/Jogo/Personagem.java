public abstract class Personagem implements Comparable<Personagem>
{
    protected String nome;
    protected double nivel;
    protected double forca;

    public Personagem(String nome, double nivel, double forca)
    {
        setNome(nome);
        setNivel(nivel);
        setForca(forca);
    }

    public String getNome() { return this.nome; }
    public double getNivel()    { return this.nivel; }
    public double getForca()    { return this.forca; }

    public void setNome(String nome)    { if(nome != null) this.nome = nome; }
    public void setNivel(double nivel)  { if(nivel > 0.0) this.nivel = nivel; }
    public void setForca(double forca)  {  if(forca > 0.0) this.forca = forca; }

    public abstract double calcularDano();

    @Override
    public int compareTo(Personagem outro)  { return Double.compare(outro.calcularDano(), this.calcularDano()); }
}