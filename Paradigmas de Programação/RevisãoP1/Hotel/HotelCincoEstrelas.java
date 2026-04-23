public class HotelCincoEstrelas implements ServicoHotelPremium
{
    //  Atributos
    private String nome;
    private int[] diarias;
    private boolean temSpa;
    private boolean petFriendly;

    //  Construtor
    public HotelCincoEstrelas(String nome, int[] diarias, boolean temSpa, boolean petFriendly)
    {
        setNome(nome);
        setDiarias(diarias);
        setTemSpa(temSpa);
        setPetFriendly(petFriendly);
    }

    //  Getters
    public String getNome() { return this.nome; }
    public int[] getDiarias() { return this.diarias; }
    public boolean isTemSpa() { return this.temSpa; }
    public boolean isPetFriendly() { return this.petFriendly; }

    //  Setters
    public void setNome(String nome)
    {
        if(nome != null)
            this.nome = nome;
    }

    public void setDiarias(int[] diarias)
    {
        if(diarias != null)
            this.diarias = diarias;
    }

    public void setTemSpa(boolean temSpa)
    {
        this.temSpa = temSpa;
    }

    public void setPetFriendly(boolean petFriendly)
    {
        this.petFriendly = petFriendly;
    }

    //  Métodos
    public void registrarReserva()  { System.out.println("Reserva registrada!"); }
    public void registrarEstacionamento()   { System.out.println("Vaga registrada!"); }
    public void reservarSpa()   { System.out.println("Spa reservado!"); }
}