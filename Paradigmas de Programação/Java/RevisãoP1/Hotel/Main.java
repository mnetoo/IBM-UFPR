public class Main
{
    public static void main(String[] args)
    {
        int[] diarias = {500, 750, 1000};

        HotelCincoEstrelas hotel = new HotelCincoEstrelas(
            "Hotel Luxo Curitiba", diarias, true, true
        );

        System.out.println("Nome: " + hotel.getNome());

        System.out.print("Diárias: ");
        for(int d : hotel.getDiarias())
            System.out.print(d + " ");

        System.out.println("\nSpa: " + (hotel.isTemSpa() ? "SIM" : "NÃO"));
        System.out.println("Pet Friendly: " + (hotel.isPetFriendly() ? "SIM" : "NÃO"));

        hotel.registrarReserva();
        hotel.registrarEstacionamento();
        hotel.reservarSpa();
    }
}