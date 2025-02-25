program recursao;

type
    vetor = array [1..200] of integer;

var
    v: vetor;
    n, elemento: integer;

procedure leVetor (n: integer; var v: vetor);
var
    i: integer;
begin
    for i := 1 to n do
        read(v[i]);
end;

function PesqBinRec (elemento: integer; var v: vetor; inicio, fim: integer): integer;
var
    meio: integer;
begin
    if (inicio > fim) then
        PesqBinRec := 0
    else
    begin
        meio := (inicio + fim) div 2;
        if (elemento = v[meio]) then
            PesqBinRec := meio
        else if (elemento < v[meio]) then
            PesqBinRec := PesqBinRec(elemento, v, inicio, meio - 1)
        else
            PesqBinRec := PesqBinRec(elemento, v, meio + 1, fim);
    end;
end;

begin
    read(n, elemento);
    leVetor(n, v);
    if (PesqBinRec(elemento, v, 1, n) <> 0) then
        writeln(PesqBinRec(elemento, v, 1, n))
    else
        writeln('Elemento não encontrado');
end.