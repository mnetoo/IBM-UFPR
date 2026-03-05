import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Digite a razão social da empresa: ");
        String razao = sc.nextLine();

        System.out.print("Digite o faturamento: ");
        double faturamento = sc.nextDouble();

        System.out.print("Digite o ano de fundação: ");
        int anoFundacao = sc.nextInt();
        sc.nextLine();

        Empresa empresa = new Empresa(razao, faturamento, anoFundacao);

        int opcao;

        do {
            System.out.println("\n==== MENU ====");
            System.out.println("1 - Cadastrar funcionário");
            System.out.println("2 - Listar funcionários");
            System.out.println("3 - Buscar funcionário");
            System.out.println("4 - Remover funcionário");
            System.out.println("5 - Calcular folha salarial");
            System.out.println("0 - Sair");
            System.out.print("Escolha: ");

            opcao = sc.nextInt();
            sc.nextLine();

            switch (opcao) {

                case 1:
                    System.out.print("Nome: ");
                    String nome = sc.nextLine();

                    System.out.print("Ano de contratação: ");
                    int ano = sc.nextInt();

                    System.out.print("Salário: ");
                    double salario = sc.nextDouble();
                    sc.nextLine();

                    System.out.print("Cargo: ");
                    String cargo = sc.nextLine();

                    Funcionario f = new Funcionario(nome, ano, salario, cargo);

                    if (empresa.cadastrarFuncionario(f)) {
                        System.out.println("Funcionário cadastrado com sucesso.");
                    } else {
                        System.out.println("Erro ao cadastrar.");
                    }
                    break;

                case 2:
                    empresa.listarFuncionarios();
                    break;

                case 3:
                    System.out.print("Digite o nome para buscar: ");
                    String busca = sc.nextLine();

                    Funcionario encontrado = empresa.buscarFuncionario(busca);

                    if (encontrado != null) {
                        encontrado.exibirInformacoes();
                    } else {
                        System.out.println("Funcionário não encontrado.");
                    }
                    break;

                case 4:
                    System.out.print("Digite o nome para remover: ");
                    String remover = sc.nextLine();

                    if (empresa.removerFuncionario(remover)) {
                        System.out.println("Funcionário removido.");
                    } else {
                        System.out.println("Funcionário não encontrado.");
                    }
                    break;

                case 5:
                    double folha = empresa.calcularFolhaSalarial();
                    System.out.println("Folha salarial total: R$ " + folha);
                    break;

                case 0:
                    System.out.println("Encerrando sistema...");
                    break;

                default:
                    System.out.println("Opção inválida.");
            }

        } while (opcao != 0);

        sc.close();
    }
}
