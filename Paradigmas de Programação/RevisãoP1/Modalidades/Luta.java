public abstract class Luta extends ModalidadeEsportiva
{
    protected String equipamento;
    protected String vestuario;
    protected String estrategia;

    // Construtor Completo
    public Luta(String nome, String objetivo, String regras,
                String equipamento, String vestuario, String estrategia)
    {   
        super(nome, objetivo, regras);
        setEquipamento(equipamento);
        setVestuario(vestuario);
        setEstrategia(estrategia);
    }

    // Sobrecarga útil (menos parâmetros)
    public Luta(String nome, String objetivo, String regras)
    {
        this(nome, objetivo, regras, "", "", "");
    }

    // Getters
    public String getEquipamento() { return equipamento; }
    public String getVestuario()   { return vestuario; }
    public String getEstrategia()  { return estrategia; }

    // Setters
    public void setEquipamento(String equipamento)
    { 
        if (equipamento != null) 
            this.equipamento = equipamento; 
    }

    public void setVestuario(String vestuario)
    { 
        if (vestuario != null) 
            this.vestuario = vestuario; 
    }

    public void setEstrategia(String estrategia)
    { 
        if (estrategia != null) 
            this.estrategia = estrategia; 
    }

    // Métodos
    @Override
    public String toString()
    {   
        return String.format(
            "Modalidade: %s - Objetivo: %s - Regras: %s - Equipamento: %s - Vestuario: %s - Estrategia: %s",
            getNome(), getObjetivo(), getRegras(),
            getEquipamento(), getVestuario(), getEstrategia()
        );
    }
}