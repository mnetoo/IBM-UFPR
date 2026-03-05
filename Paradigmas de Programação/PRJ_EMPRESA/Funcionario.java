public class Funcionario
{
	String nome;
	int anoContratacao;
	double salario;
	String cargo;

	public Funcionario(String nome, int anoContratacao, double salario, String cargo)
	{
		this.nome = nome;
		this.anoContratacao = anoContratacao;
		this.salario = salario;
		this.cargo = cargo;
	}

	//Métodos Getters
	public String getNome()		{ return nome; }
	public int getAnoContratacao()	{ return anoContratacao; }
	public double getSalario()	{ return salario; }
	public String getCargo()	{ return cargo; }

	//Métodos Setters
	public void setNome(String nome)	{ this.nome = nome; }
	public void setAnoContratacao(int anoContratacao)	{ this.anoContratacao = anoContratacao; }
	public void setSalario(double salario)	{ this.salario = salario; }
	public void setCargo(String Cargo)	{ this.cargo = cargo; }

	public void exibirInformacoes()
	{
		System.out.println("Nome: " + getNome());
		System.out.println("Ano de Contratação: " + getAnoContratacao());
		System.out.println("Salário: " + getSalario());
		System.out.println("Cargo: " + getCargo());
	}

	public void aumentoSalario(double aumento)	{ this.salario += aumento; }
	public void promocaoCargo(String novoCargo)	{ this.cargo = novoCargo; }
}
