public class AlunoMonitor
{
    private String nome;
    private int matricula;
    private String codigo;

    public AlunoMonitor(String nome, int matricula, String codigo)
    {
        setNome(nome);
        setMatricula(matricula);
        setCodigo(codigo);
    }

    public String getNome() { return this.nome; }
    public int getMatricula()   { return this.matricula; }
    public String getCodigo()   { return this.codigo; }

    public void setNome(String nome)   { if(nome != null) this.nome = nome; }
    public void setMatricula(int matricula)  { if(matricula > 0) this.matricula = matricula; }
    public void setCodigo(String codigo) { if(codigo != null) this.codigo = codigo; }

    @Override
    public String toString()
    {
        return String.format("Nome: %s | Matrícula: %d | Código: %s", getNome(), getMatricula(), getCodigo());
    }
}