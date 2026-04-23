import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        // Exemplo: Tratando todos como Modalidade
        ModalidadeEsportiva m1 = new Boxe("BOXE", "Competição/Autodefesa", "Respeito/Segurança", "Luvas", "Bermuda", "Agressivo");
        ModalidadeEsportiva m5 = new MuayThai("MUAY THAI", "Competição/Autodefesa", "Respeito/Segurança", "Luvas/Caneleiras", "Bermuda", "Agressivo");
        ModalidadeEsportiva m2 = new Musculacao("MUSCULAÇÃO", "Melhora do Condicionamento", "Progressão");
        ModalidadeEsportiva m3 = new Spinning("SPINNING", "Melhora do Condicionamento", "Progressão");
        ModalidadeEsportiva m4 = new Spinning("NATAÇÃO", "Melhora do Condicionamento", "Progressão");

        List<ModalidadeEsportiva> lista = new ArrayList<>();
        lista.add(m1);
        lista.add(m5);
        lista.add(m2);
        lista.add(m3);
        lista.add(m4);

        // O método executarRegra() se comporta de forma diferente para cada um
        for (ModalidadeEsportiva m : lista) 
            System.out.println(m.toString());
    }
}