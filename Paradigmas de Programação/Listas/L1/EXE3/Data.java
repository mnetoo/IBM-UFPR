public class Data
{
    private int dia;
    private int mes;
    private int ano;

    //  construtor
    public Data(int dia, int mes, int ano)
    {
        this.dia = dia;
        this.mes = mes;
        this.ano = ano;
    }
    
    //  getters
    public int getDia()     { return this.dia; }
    public int getMes()     { return this.mes; }
    public int getAno()     { return this.ano; }
    
    //  setters
    public void setDia(int dia)     { if(dia > 0) this.dia = dia; }
    public void setMes(int mes)     { if(mes > 0) this.mes = mes; }
    public void setAno(int ano)     { if(ano > 0) this.ano = ano; }
    
    //  métodos
    public boolean anterior(int dia, int mes, int ano)
    {
        if(this.ano != ano)
            return this.ano < ano;
        
        if(this.mes != mes)
            return this.mes < mes;
        
        return this.dia < dia;
    }

    public boolean posterior(int dia, int mes, int ano)
    {
        if(this.ano != ano)
            return this.ano > ano;
        
        if(this.mes != mes)
            return this.mes > mes;
        
        return this.dia > dia;
    }
    
    public boolean equals(int dia, int mes, int ano)
    {
        if(this.dia == dia && this.mes == mes && this.ano == ano)
            return true;
        
        return false;
    }
    
    public String toString()
    {
        return dia + "/" + mes + "/" + ano;
        
    }
    
    public boolean checaDiaMes(int dia, int mes)
    {
        if (mes < 1 || mes > 12) 
            return false;
    
        int diasNoMes;
    
        switch(mes)
        {
            case 2:
                diasNoMes = 28;
                break;
            case 4: case 6: case 9: case 11:
                diasNoMes = 30;
                break;
            default:
                diasNoMes = 31;
        }
    
        if(dia >= 1 && dia <= diasNoMes)
            return true;
        else
            return false;
    }
    
    public Data maiorData(Data d[])
    {
        Data maior = d[0];
    
        for(int i = 1; i < d.length; i++)
        {
            if(d[i].posterior(maior.getDia(), maior.getMes(), maior.getAno()))
                maior = d[i];
        }
    
        return maior;
    }
    
    public Data menorData(Data d[])
    {
        Data menor = d[0];
    
        for(int i = 1; i < d.length; i++)
        {
            if(d[i].anterior(menor.getDia(), menor.getMes(), menor.getAno()))
                menor = d[i];
        }
    
        return menor;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}