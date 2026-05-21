import java.util.ArrayList;
import java.util.List;

public class Turma
{
    // Atributos
    private int codigo;
    private String professor;
    private List<Aluno> alunos;
    
    //  Construtores
    public Turma(int codigo, String professor, List<Aluno> alunos) 
    {
        setCodigo(codigo);
        setProfessor(professor);
        setAlunos(alunos);
    }

    public Turma(int codigo, String professor)  { this(codigo, professor, new ArrayList<>()); }
    public Turma(int codigo)    { this(codigo, "", new ArrayList<>()); }
    public Turma(String professor)   { this(0, professor, new ArrayList<>()); }
    public Turma(String professor, List<Aluno> alunos)   { this(0, professor, alunos); }
    public Turma(List<Aluno> alunos)    { this(0, "", alunos); }
    
    // Getters
    public int getCodigo() { return this.codigo; }
    public String getProfessor() { return this.professor; }
    public List<Aluno> getAlunos() { return this.alunos; }
    
    // Setters
    public void setCodigo(int codigo) { if(codigo > 0) this.codigo = codigo; }
    public void setProfessor(String professor) { if(professor != null) this.professor = professor; }
    public void setAlunos(List<Aluno> alunos) { this.alunos = alunos; }
    
    // Métodos
    public void adicionar(Aluno aluno) { if(aluno != null) alunos.add(aluno); }
    
    public void listarAlunos()
    {
        System.out.println("Turma: " + getCodigo());
        System.out.println("Professor: " + getProfessor());
        System.out.println("Alunos: ");
        for(Aluno a : alunos) { System.out.println(a.toString()); }
    }
}
