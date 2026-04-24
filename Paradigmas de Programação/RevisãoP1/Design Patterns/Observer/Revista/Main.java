public class Main
{
    public static void main(String[] args)
    {
        int novaEdicao = 3;

        RevistaInformatica revista = new RevistaInformatica(1);
        Assinante assinante = new Assinante(revista);

        revista.setEdicao(novaEdicao);
    }
}