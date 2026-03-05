public class Empresa
{
	String razaoSocial;
	int quantidadeFuncionarios;
	double faturamento;
	int anoFundacao;
	Funcionario[] funcionarios;


	public Empresa(String razaoSocial, double faturamento, int anoFundacao)
	{
		this.razaoSocial = razaoSocial;
		this.quantidadeFuncionarios = 0;
		this.faturamento = faturamento;
		this.anoFundacao = anoFundacao;
		this.funcionarios = new Funcionario[10];
	}

	//Métodos Getters
	public String getRazaoSocial()		{ return razaoSocial; }
	public int getQuantidadeFuncionarios()	{ return quantidadeFuncionarios; }
	public double getFaturamento()		{ return faturamento; }
	public int getAnoFundacao()		{ return anoFundacao; }

	public boolean cadastrarFuncionario(Funcionario funcionario)
	{
		if(quantidadeFuncionarios > funcionarios.length)
		{
			System.out.println("Limite de funcionários atingido!");
			return false;
		}

	
		funcionarios[quantidadeFuncionarios] = funcionario;
		quantidadeFuncionarios++;
		System.out.println("Funcionário <" + funcionario.getNome() + "> cadastrado");
	
		return true;
	}

	public void listarFuncionarios()
	{
		if(quantidadeFuncionarios <= 0)
		{
			System.out.println("Não existem funcionários cadastrados!");
			return;
		}

		for(int i = 0; i < quantidadeFuncionarios; i++)
		{
			System.out.println("---------- FUNCIONÁRIO " + (i + 1) + "----------");
			funcionarios[i].exibirInformacoes();
		}
	}

	public Funcionario buscarFuncionario(String nome)
	{
		for(int i = 0; i < quantidadeFuncionarios; i++)
		{
			if(funcionarios[i].getNome().equalsIgnoreCase(nome))
				return funcionarios[i];
		}

		return null;
	}

	public boolean removerFuncionario(String nome) 
	{

        	for (int i = 0; i < quantidadeFuncionarios; i++) 
		{

            		if (funcionarios[i].getNome().equalsIgnoreCase(nome)) 
			{

                		// desloca array para esquerda
                		for (int j = i; j < quantidadeFuncionarios - 1; j++) 
                    			funcionarios[j] = funcionarios[j + 1];

                	funcionarios[quantidadeFuncionarios - 1] = null;
                	quantidadeFuncionarios--;
                	return true;
            		}
        	}

       		return false;
    	}    

	public double calcularFolhaSalarial() 
	{

        	double total = 0;

        	for (int i = 0; i < quantidadeFuncionarios; i++)
            		total += funcionarios[i].getSalario();

        	return total;
    	}
}
