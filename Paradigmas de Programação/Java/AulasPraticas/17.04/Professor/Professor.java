public class Professor
{
    private String nome;
    private int matricula;

    public Professor(String nome, int matricula)
    {
        setNome(nome);
        setMatricula(matricula);
    }

    public String getNome() { return this.nome; }
    public int getMatricula()   { return this.matricula; }

    public void setNome(String nome)   { if(nome != null) this.nome = nome; }
    public void setMatricula(int matricula)  { if(matricula > 0) this.matricula = matricula; }

    @Override
    public String toString()
    {
        return String.format("Professor: %s | Matrícula: %d", getNome(), getMatricula());
    }
}