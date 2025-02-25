program buscabinaria;

type
    vetor = array [1..200] of integer;

var
    v : vetor;
    n, elemento: integer;

procedure lerVetor (n : integer; var v: vetor);
var
    i: integer;
begin

    for i:= 1 to n do
    begin
        read(v[i]);
    end;

end;

function PesqBin (n: integer; elemento: integer; var v: vetor):integer;
var
    meio, inicio, fim: integer;
begin
    inicio:= 1;
    fim:= n;
    repeat
        meio:= (inicio + fim) div 2;
        if(elemento > v[meio]) then
            inicio:= meio + 1
        else
            fim:= meio - 1;
    until (elemento = v[meio]) or (inicio > fim);
    if(elemento = v[meio]) then
        PesqBin:= meio
    else
        PesqBin:= 0;
end;

begin
    read(n);
    lerVetor(n, v);
    read(elemento);
    PesqBin(n, elemento, v);
    if(PesqBin(n, elemento, v) <> 0) then
        writeln(PesqBin(n, elemento, v))
    else
        writeln(PesqBin(n, elemento, v));
end.